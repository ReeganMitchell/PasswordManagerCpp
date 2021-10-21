#include "Analyser.h"
#include <sstream>
#include <iostream>
#include <chrono>
using namespace std;

Analyser::Analyser():FileManager()
{
	fileName = "passwordtest.txt";
}

Analyser::~Analyser()
{
}

void Analyser::GeneratePasswordFile()
{
	const int noOfLetters = 10;
	file->open(fileName, ios::out | ios::app);

	for (int i = 0; i < 100; i++) {//first 10000
		for (int j = 0; j < 100; j++) {
			char letters[noOfLetters];
			for (int k = 0; k < noOfLetters; k++) {
				letters[k] = (char)ChooseRandomLetter();
			}
			char* lettersToSend = letters;
			string password = GeneratePassword(i + 1, lettersToSend);
			string encryptedPass = EncryptPassword(password);
			*file << encryptedPass << endl;
		}
	}
	for (int x = 0; x < 100; x++) {//second 10000
		for (int y = 0; y < 100; y++) {
			string encryptedPass = GeneratePassword(x + 1);
			*file << encryptedPass << endl;
		}
	}
	file->close();
}

void Analyser::StrengthTest()
{
	ifstream infile;
	infile.open(fileName, ios::in);

	string password;
	string testPass;
	const int noOfPasswords = 100;
	int noCorrect = 0;
	double times[noOfPasswords];

	for (int i = 0; i < noOfPasswords; i++) {//first 10000
		cout << "Checking for lowercase passwords of length " << i + 1 << ". \n";
		for (int j = 0; j < noOfPasswords; j++) {
			infile >> password;

			auto startTime = chrono::system_clock::now();
			auto endTime = chrono::system_clock::now();
			std::chrono::duration<double> diffTime = endTime - startTime;

			testPass = EncryptPassword(GeneratePassword(i+1, true));
			while (password != testPass) {
				endTime = chrono::system_clock::now();
				diffTime = endTime - startTime;
				double time = diffTime.count();
				diffTime = endTime - startTime;
				if (time > 0.001) {
					break;
				}

				testPass = EncryptPassword(GeneratePassword(i+1, true));
			}
			if (password == testPass) {
				noCorrect++;
			}
			endTime = chrono::system_clock::now();
			diffTime = endTime - startTime;
			times[j] = diffTime.count();
		}
		double totalTime = 0;
		for (int k = 0; k < noOfPasswords; k++) {
			totalTime += times[k];
		}
		double percent = ((double)noCorrect / (double)noOfPasswords) * 100;
		cout << "Percentage of passwords discovered: " << (int)percent << "% \n";
		if (percent > 0) {
			cout << "Average time taken to discover passwords: " << (totalTime / noOfPasswords) << " seconds \n";
		}
		noCorrect = 0;
	};
	noCorrect = 0;

	for (int x = 0; x < 100; x++) {//second 10000
		cout << "Checking for extended ASCII passwords of length " << x + 1 << ". \n";
		for (int y = 0; y < 100; y++) {
			infile >> password;

			auto startTime = chrono::system_clock::now();
			auto endTime = chrono::system_clock::now();
			std::chrono::duration<double> diffTime = endTime - startTime;

			testPass = EncryptPassword(GeneratePassword(x + 1));
			while (password != testPass) {
				endTime = chrono::system_clock::now();
				diffTime = endTime - startTime;
				double time = diffTime.count();
				diffTime = endTime - startTime;
				if (time > 1.0) {
					break;
				}

				testPass = EncryptPassword(GeneratePassword(x + 1));
			}
			if (password == testPass) {
				noCorrect++;
			}
			endTime = chrono::system_clock::now();
			diffTime = endTime - startTime;
			times[y] = diffTime.count();
		}
		double totalTime = 0;
		for (int z = 0; z < noOfPasswords; z++) {
			totalTime += times[z];
		}
		double percent = ((double)noCorrect / (double)noOfPasswords) * 100;
		cout << "Percentage of passwords discovered: " << (int)percent << "% \n";
		if (percent > 0) {
			cout << "Average time taken to discover passwords: " << (totalTime / noOfPasswords) << " seconds \n";
		}
		noCorrect = 0;
	}

	infile.close();
}

int Analyser::ChooseRandomLetter()
{
	return rand() % 25 + 97;
}

int Analyser::ChooseRandomASCII()
{
	return rand() % 255 + 1;
}

string Analyser::GeneratePassword(int length, char* letters)
{
	std::ostringstream pass;
	for (int i = 0; i < length; i++) {
		pass << letters[rand() % 10];
	}

	return pass.str();
}

string Analyser::GeneratePassword(int length, bool analysing)
{
	std::ostringstream pass;
	for (int i = 0; i < length; i++) {
		char letter = (char)ChooseRandomLetter();
		pass << letter;
	}

	return pass.str();
}

string Analyser::GeneratePassword(int length)
{
	int usedASCII[100] = { 0 };
	int offset = 0;
	int* asciiOffset = new int[length];
	int* results = new int[length];

	for (int i = 0; i < length; i++) {
		int ascii;
		bool used;
		GETASCII: ascii = ChooseRandomASCII();
		used = false;

		for (int j = 0; j < 100; j++) {
			if (ascii == usedASCII[j]) {
				used = true;
			}
		}
		if (used == true) {
			goto GETASCII;
		}

		asciiOffset[i] = ascii + offset;
		int result = collatz(asciiOffset[i]);
		results[i] = result;
		offset = result;
		usedASCII[i] = ascii;
	}

	std::ostringstream pass;
	for (int i = 0; i < length; i++) {
		pass << results[i];
	}
	delete[] results;
	results = NULL;
	delete[] asciiOffset;
	asciiOffset = NULL;
	return pass.str();
}
