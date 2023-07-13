# 5x5-distributed-word-finder

![Screenshot 2023-07-09 5x5 Distributed Letter Set Finder](https://github.com/4lClover/5x5-distributed-word-finder/assets/61360844/02021b63-789c-451e-926b-0592e6201225)

This program searches word lists to find five words with five letters without repeating any letters.

This program is very lightweight using minimal resources.

* First all of the possible words are loaded into a vector of strings
* A search is performed on the words capable of producing a set of distributed letter words
* Upon completion of every possible combination a report is produced
* A Sets.txt file is written to the programs directory

Two filters are implemented, a set with any repeating words is skipped and variations of sets with the exacts same words are omitted from the list of distributed letter word sets.

It is important to note that your word list must be named WordList.txt and must be a plain text file with one word on each line. I have provided an example word list file and two test files plus a word list provided by MIT of 10,000 words. When opening each file there is a copy of the file's name or purpose on the first line. Simply change the file names to run each file. The first line of each file will remind you what that file is for so that it is easy to keep track of all files (renaming each file to execute the program and name it back after the program has run).

Secondly read the notes in main.cpp, to create a release build you must uncomment // continues(); // Uncomment for release build. on line 54 in main(). 
