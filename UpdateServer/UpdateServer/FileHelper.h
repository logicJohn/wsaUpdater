// Basic helper functions for file handling
// Copyright(c) Bobby Hoggard

#pragma once

#include <fstream>
#include <iostream>
using namespace std;

// Used to open a file for reading.
// Declare an ifstream object and pass it as a parameter to this function, along with a filename.
// The function will attempt to open the named file.
// If the file cannot be opened, an error message will display, and the program will exit.
void openInputFile(ifstream& dataFile, const char FILENAME[]);


// Used to open a file for writing.
// Declare an ofstream object and pass it as a parameter to this function, along with a filename.
// The function will attempt to open the named file.
// If the file cannot be opened, an error message will display, and the program will exit.
void openOutputFile(ofstream& dataFile, const char FILENAME[]);


// Used to read a single integer from a file.
// Pass an opened ifstream file object to this function, and the function will attempt to
// read the next four bytes in the file as an integer.
// Returns the integer read from the file, or 0 if the file is not open.
int readInt(ifstream& dataFile);


// Used to write a single integer to a file.
// Pass an opened ofstream file object to this function, and an integer that you wish to write,
// and the function will attempt to write the integer into the file.  The integer will be
// written in it's raw binary form -- not written as a series of characters.
void writeInt(ofstream& dataFile, int value);