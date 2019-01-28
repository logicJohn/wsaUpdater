// Basic helper functions for file handling
// Copyright(c) Bobby Hoggard

#include "FileHelper.h"

void openInputFile(ifstream& dataFile, const char FILENAME[])
{
	dataFile.open(FILENAME);
	if (dataFile.fail())
	{
		cerr << "Data file cannot be opened\n";
		exit(1);
	}
}

void openOutputFile(ofstream& dataFile, const char FILENAME[])
{
	dataFile.open(FILENAME);
	if (dataFile.fail())
	{
		cerr << "Data file cannot be opened\n";
		exit(1);
	}
}

int readInt(ifstream& dataFile)
{
	int value = 0;

	if (dataFile.is_open())
	{
		dataFile.read((char*)&value, sizeof(value));
	}

	return value;
}

void writeInt(ofstream& dataFile, int value)
{
	if (dataFile.is_open())
	{
		dataFile.write((char*)&value, sizeof(value));
	}
}