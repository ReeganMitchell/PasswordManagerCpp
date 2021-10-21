#pragma once
#include <fstream>
using namespace std;

class FileManager {
public:
	FileManager();
	~FileManager();
	void saveToFile(string username, string password);
	int authenticatePassword(string username, string password);
protected:
	std::string fileName; 
	fstream* file = NULL; 
	string EncryptPassword(string password);
	int collatz(int seed);
};