#pragma once
#include "FileManager.h"

class Analyser : public FileManager {
public:
	Analyser();
	~Analyser();
	void GeneratePasswordFile();
	void StrengthTest();
private:
	int ChooseRandomLetter();
	int ChooseRandomASCII();
	string GeneratePassword(int length,char* letters);
	string GeneratePassword(int length, bool analysing);
	string GeneratePassword(int length);
};