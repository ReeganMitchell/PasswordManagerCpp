#include "FileManager.h"
#include "Analyser.h"
#include <iostream>
#include <time.h>
using namespace std;

int menuInput();
void storeDetails();
void checkDetails();
void generateStrengthTest();
void analyseFile();

int main()
{
	srand(time(NULL));
    cout << "Hello World!\n";
	int c = menuInput();
	switch (c) {
	case 1:
		storeDetails();
		break;
	case 2:
		checkDetails();
		break;
	case 3:
		generateStrengthTest();
		break;
	case 4:
		analyseFile();
		break;
	default:
		std::cout << "Invalid input, Exiting. \n";
		break;
	}
}

int menuInput() {
	cout << "Please choose an option by entering a number: \n";
	cout << "1. Create Username/Password\n"; 
	cout << "2. Check username and password\n";
	cout << "3. Generate password strength analysis file\n";
	cout << "4. Analyse password strength analysis file\n";

	int choice;
	cin >> choice;
	return choice; 
}

void storeDetails() {
	cout << "Please Enter a username. \n";
	string username;
	cin >> username;

	cout << "Please enter a password. \n";
	string password;
	cin >> password;

	FileManager manager;
	manager.saveToFile(username, password);
}

void checkDetails() {
	cout << "Please Enter a username. \n";
	string username;
	cin >> username;

	cout << "Please enter a password. \n";
	string password;
	cin >> password;

	FileManager manager;
	int result = manager.authenticatePassword(username,password);
	switch (result) {
	case 0:
		cout << "failure! \n";//username not found
		break;
	case 1:
		cout << "Success! \n";
		break;
	case 2:
		cout << "failure! \n";//password wrong
		break;
	}
}

void generateStrengthTest()
{
	cout << "Generating Password Test File. \n";
	Analyser generator;
	generator.GeneratePasswordFile();
	cout << "Password Test File Complete. \n";
}

void analyseFile()
{
	cout << "Starting Strength Test. \n";
	Analyser tester;
	tester.StrengthTest();
	cout << "Strength Test Complete. \n";
}
