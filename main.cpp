/*
Program:5x5 Distributed Letter Set Finder
Author:Phillip McCullough
Date:12/28/2022
C/Cpp:11+ ANSI Standard
Last Updated:7/9/2023

This program addresses a problem scholars ponder every half a century or so
looking to find all possible five-word combinations using all but one letter
in the standard English alphabet.
-------10--------20--------30--------40--------50--------60--------70--------80
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

const string WORD_LIST = "WordList.txt";
const string SETS_FILE = "Sets.txt";
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
const string VOWELS = "aeiou";
const int SET_SIZE = 5;

void continues();
string makeSet(string set[SET_SIZE]);
bool validWord(string word);
void populateWords(vector<string>& words, int& word_count);
void findSets(vector<string>& words, vector<string>& sets);
bool testSet(string set[SET_SIZE]);
bool uniqueSet(string set[SET_SIZE], vector<string>& sets);
void displaySets(vector<string>& sets);
void writeSetsFile(vector<string>& sets);
void clearSetsFile();

int main()
{
	vector<string> words;
	vector<string> sets;
	int word_count = 0;

	populateWords(words, word_count);
	findSets(words, sets);

	cout << '\n' 
		<< "Total Words...: " << word_count << '\n'
		<< "Possible Words: " << words.size() << '\n'
		<< "Sets Found....: " << sets.size() << "\n\n"
		<< "Sets,\n";

	clearSetsFile();
	writeSetsFile(sets);
	// continues(); // Uncomment for release build.

	return 0;
}

// ----------------------------------------------------------------------------

void continues()
{
	cout << "\nPress the [enter/return] key to continue.";
	cin.get();
}

// ----------------------------------------------------------------------------

bool validWord(string word)
{
	string alphabet = ALPHABET;
	int vowel_count = 0;
	for (int i = 0; i < 5; i++)
	{
		if (alphabet.find(tolower(word[i])) == -1 || vowel_count > 2)
		{
			return false;
		}
		else
		{
			if (VOWELS.find(tolower(word[i])) != -1)
				vowel_count += 1;
			if (alphabet.find(tolower(word[i])) != -1)
				alphabet.erase(alphabet.find(tolower(word[i])), 1);
		}
	}
	return true;
}

// ----------------------------------------------------------------------------

void populateWords(vector<string>& words, int& word_count)
{
	// Filter Words: Five letters with two vowels max.
	ifstream words_list;
	words_list.open(WORD_LIST);
	if (words_list.is_open())
	{
		string test_word;
		while (!words_list.eof())
		{
			word_count += 1;
			getline(words_list, test_word);
			if (test_word.length() == 5 && validWord(test_word))
				words.push_back(test_word);
		}
		words_list.close();
	}
	else
	{
		cout << "Error, problem opening " << WORD_LIST << '\n';
		continues();
	}
}

// ----------------------------------------------------------------------------

string numCommaFormat(long double number)
{
	string number_str = to_string(number);
	int decimal = number_str.find('.'), precision = 0;

	if (decimal > 3)
		for (int i = decimal - 3; i > 0; i -= 3)
			number_str.insert(i, ",");

	decimal = number_str.find('.');

	if (precision > 0)
		precision += 1;

	return number_str.substr(0, decimal + precision);
}

// ----------------------------------------------------------------------------

void findSets(vector<string>& words, vector<string>& sets)
{

/*
I would like to improve the efficiency of this method,
any suggestions are welcome.
*/

	string alphabet = ALPHABET, possible_set[SET_SIZE], new_set;
	unsigned long long iterations = 0;
	for (int w1 = 0; w1 < words.size(); w1++)
		for (int w2 = 0; w2 < words.size(); w2++)
			for (int w3 = 0; w3 < words.size(); w3++)
				for (int w4 = 0; w4 < words.size(); w4++)
					for (int w5 = 0; w5 < words.size(); w5++)
					{// Still => just numbers <= eliminates duplicates.
						if (w1 == w2 || w1 == w3 || w1 == w4 || w1 == w5)
							continue;
						else if (w2 == w3 || w2 == w4 || w2 == w5)
							continue;
						else if (w3 == w4 || w3 == w5)
							continue;
						else if (w4 == w5)
							continue;

						iterations += 1; // Iteration counter.

						// Converted to words.
						possible_set[0] = words[w1];
						possible_set[1] = words[w2];
						possible_set[2] = words[w3];
						possible_set[3] = words[w4];
						possible_set[4] = words[w5];

						if (!testSet(possible_set))
							cout << "Searching: " << makeSet(possible_set) << ", sets found: " 
							<< sets.size() << '\n';
						else if (uniqueSet(possible_set, sets))
						{
							new_set = makeSet(possible_set);
							cout << "Set Found: " << new_set << '\n';
							sets.push_back(new_set);
						}
					}

	cout << "\nSearch Iterations: " << numCommaFormat(iterations) << '\n';
}

// ----------------------------------------------------------------------------

string makeSet(string set[SET_SIZE])
{
	string new_set;
	for (int i = 0; i < SET_SIZE - 1; i++)
		new_set += set[i] + ' ';
	new_set += set[SET_SIZE - 1];
	return new_set;
}

// ----------------------------------------------------------------------------

bool testSet(string set[SET_SIZE])
{
	string alphabet = ALPHABET, test;
	for (int i = 0; i < SET_SIZE; i++)
		test += set[i];
	for (int i = 0; i < test.length(); i++)
	{
		if (alphabet.find(tolower(test[i])) == -1)
			return false;
		if (alphabet.find(tolower(test[i])) != -1)
			alphabet.erase(alphabet.find(tolower(test[i])), 1);
	}
	return true;
}

// ----------------------------------------------------------------------------

bool uniqueSet(string set[SET_SIZE], vector<string>& sets)
{
	int match;
	for (int i = 0; i < sets.size(); i++)
	{
		match = 0;
		for (int s = 0; s < SET_SIZE; s++)
		{
			if (sets[i].find(set[s]) != -1)
				match += 1;
		}
		if (match == SET_SIZE)
			return false;
	}
	return true;
}

// ----------------------------------------------------------------------------

void displaySets(vector<string>& sets)
{
	if (sets.empty())
		cout << "\nNo valid distributed letter five word set was found\n";
	else
		for (string set : sets)
			cout << set << '\n';
}

// ----------------------------------------------------------------------------

void writeSetsFile(vector<string>& sets)
{
	ofstream sets_file;
	sets_file.open(SETS_FILE, ofstream::app);
	if (sets_file.is_open())
	{
		for (string set : sets)
		{
			sets_file << set << '\n';
			cout << set << '\n';
		}
		sets_file.close();
	}
	else
	{
		cout << "Error, problem opening " << SETS_FILE << '\n';
		continues();
	}
}

// ----------------------------------------------------------------------------

void clearSetsFile()
{
	ofstream sets_file;
	sets_file.open(SETS_FILE);
	if (sets_file.is_open())
	{
		sets_file << "";
		sets_file.close();
	}
	else
	{
		cout << "Error, problem opening " << SETS_FILE << '\n';
		continues();
	}
}