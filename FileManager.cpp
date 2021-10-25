#include "FileManager.h"
#include <iostream>
#include <sstream>

FileManager::FileManager()
{
	fileName = "password.txt";
	file = new fstream();
}

FileManager::~FileManager()
{
	if (file != NULL) {
		delete file; 
		file = NULL; 
	}
}

string FileManager::EncryptPassword(string password)
{
	int offset = 0;
	char* c = new char[password.size() + 1];
	int* asciiOffset = new int[password.size()];
	int* results = new int[password.size()];

	password.copy(c, password.size() + 1);
	c[password.size()] = '\0';

	for (int x = 0; x < password.size(); x++) {
		asciiOffset[x] = c[x] + offset;
		int result = collatz(asciiOffset[x]);
		results[x] = result;
		offset = result;
	}

	std::ostringstream os;
	for (int i = 0; i < password.size(); i++) {
		os << results[i];
	}

	delete[] results;
	results = NULL;
	delete[] asciiOffset;
	asciiOffset = NULL;
	delete[] c;
	c = NULL;
	return os.str();
}

void FileManager::saveToFile(string username, string password)
{
	file->open(fileName, ios::out | ios::app);
	string encryptedPass = EncryptPassword(password);
	*file << username << " " << encryptedPass << endl;
	file->close();
}

int FileManager::authenticatePassword(string username, string password)
{
	password = EncryptPassword(password);
	ifstream infile; 
	infile.open(fileName, ios::in);
	if (infile.peek() == EOF) {
		return 3;
	}

	string nameOnFile;
	string passOnFile;

	auto shortenString = [](string s, char delim) { //lambda expression
		return s.substr(0, s.find(delim));
	};

	while (nameOnFile != username) {
		infile >> nameOnFile; 
		infile >> passOnFile;
		nameOnFile = shortenString(nameOnFile, ' ');
		if (infile.peek() == EOF) {
			return 0;
		}
	}

	for (auto i = 0; i < 4; i++) {
		if (passOnFile == password) {
			return 1;
		}
		if (i != 3) {
			cout << "Password incorrect please try again, " << (3 - i) << " tries remaining. \n";
			cin >> password;
			password = EncryptPassword(password);
		}
	}

	return 2;
} // 0 = No username, 1 = correct, 2 = wrong password, 3 = file not found.

int FileManager::collatz(int seed)
{
	int count = 0;
	while (seed != 1) {
		count++;
		if (seed % 2 == 0) {
			seed = seed / 2;
		}
		else {
			seed = (seed * 3) + 1;
		}
	}
	return count;
}
