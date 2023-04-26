
#include <iostream> // input output stream library
#include <string> // library for string manipulation
#include <cmath> // libary for math functions
#include <vector> // library for poitnters and vectors
#include <fstream> // library for file manipulation
#include <sstream>
#include <chrono> 
#include <thread>

// namespace standard
using namespace std;

// functions

void encryptFile(const string& inputFilename, const string& outputFilename, int encryptionKey) {

	// Open the input file
	ifstream inputFile(inputFilename);

	if (!inputFile) {

		cerr << "Error opening input file." << endl;

		return;
	}

	// Open the output file
	ofstream outputFile(outputFilename);

	if (!outputFile) {

		cerr << "Error opening output file." << endl;

		return;

	}

	// Encrypt the contents of the input file
	char c;
	while (inputFile.get(c)) {

		c += encryptionKey; // Add the encryption key to the ASCII code of each character

		outputFile.put(c); // Write the encrypted character to the output file

	}

	// Close the files
	inputFile.close();
	outputFile.close();

	cout << "File encrypted successfully." << endl;
}

void decryptFile(const string& inputFilename, const string& outputFilename, int encryptionKey) {

	// Open the input file
	ifstream inputFile(inputFilename);

	if (!inputFile) {

		cerr << "Error opening input file." << endl;

		return;

	}

	// Open the output file
	ofstream outputFile(outputFilename);

	if (!outputFile) {

		cerr << "Error opening output file." << endl;

		return;
	}

	// Decrypt the contents of the input file
	char c;

	while (inputFile.get(c)) {

		c -= encryptionKey; // Subtract the encryption key from the ASCII code of each character to decrypt it

		outputFile.put(c); // Write the decrypted character to the output file
	}

	// Close the files
	inputFile.close();
	outputFile.close();

	std::cout << "File decrypted successfully." << endl;

}

// Hash Function
unsigned int Hash(string& data) {

	unsigned int result(0);


	// for characters in data
	for (unsigned int ch : data) {

		result = ch + (result << 4) + (result << 10) - result;

	}

	return result;

}

// function for file creation
void createUserFile(string a) {

	unsigned int hashUser{ Hash(a) };

	// creates the User File
	ofstream MyFile("users.txt", fstream::app);

	// adds the user hash to the file
	MyFile << hashUser << endl;

	// if statements for User file creation
	if (MyFile.is_open()) {

		cout << "User Created Succesfully!" << endl;

	}
	else if (!MyFile.is_open()) {

		cout << "Failed to create User" << endl;

	}

	// closes the file
	MyFile.close();

}

void createHashFile(string a) {

	unsigned int hashCredentials{ Hash(a) };

	// creates the credentials file
	ofstream MyFile("credentials.txt", fstream::app);

	// write data to the file
	MyFile << hashCredentials << endl;

	// if statements for password hash file creation
	if (MyFile.is_open()) {

		cout << "Password saved Succesfully!" << endl;

	}
	else if (!MyFile.is_open()) {

		cout << "Failed to save password" << endl;

	}

	// close the file
	MyFile.close();

}

// Hash Validation 
bool checkHash(string a, string b) {

	return a == b;

}

void createBundle()
{

	bool BundleMenu = false;
	int counter = 0;
	string url, username, password;

	// user states the apps for the bundle (maximum 5)

	// Create Bundle File
	ofstream MyFile("bundle.txt", fstream::app);

	while(BundleMenu != true)
	{


		if (counter < 5)
		{
			
			cout << "Enter URL: ";
			cin >> url;

			cout << "Enter the username: ";
			cin >> username;

			cout << "Enter the password: ";
			cin >> password;


			// Save data to the file
			MyFile << url << "\n";
			MyFile << username << endl;
			MyFile << password << "\n\n";

			// if statements for User file creation
			if (MyFile.is_open()) {

				cout << "Data Saved Succesfully!" << endl;
				counter++;

			}
			else if (!MyFile.is_open()) {

				cout << "ERROR: Failed to save data..." << endl;

			}

		}
		else
		{
			// closes the file
			MyFile.close();
			BundleMenu = true;
		}
		



		// user states his passwords for each app (gives url as well) 

		// the tet file gets encrypted and the user is given an encryption key

		// info gets added to a text file for user to download 
	}

}

void loggedInMenu(string a) {

	int options;

	cout << a << " Select from the options below" << endl;

	cout << "1. Create Bundle" << endl;
	cout << "2. Decrypt File" << endl;

	cout << "Select: ";
	cin >> options;

	switch (options) {

	case 1:

		system("cls");

		createBundle();

		break;

	case 2:

		system("cls");

		break;

	}

}

// Exit screen
void exitScreen() {

	system("cls");

	cout << "Goodbye";

}

// Login menu
void loginMenu() {

	string user;
	string pass;
	string userFileLines;
	string credentialsFileLines;

	cout << "Username: ";
	cin >> user;

	// Turn the username login into a hash
	unsigned int userHash{ Hash(user) };

	// change username hash to string
	string userHashString = to_string(userHash);

	// Check if the username entered by the user exists in the file
	ifstream MyUsersFile("users.txt");

	if (MyUsersFile.is_open()) {

		while (getline(MyUsersFile, userFileLines)) {

			if (userFileLines.find(userHashString) != string::npos ) {

				cout << "User found in SimpleSave Database" << endl;

				break;

			}

		}
		MyUsersFile.close();
	}
	else {

		cout << "Unable to open file" << endl;

	}

	cout << "Password: ";
	cin >> pass;

	// Turn the Master Password login into a hash
	unsigned int passHash{ Hash(pass) };

	string credentialsHashString = to_string(passHash);

	ifstream MyCredentialsFile("credentials.txt");
	
	if (MyCredentialsFile.is_open()) {

		while (getline(MyCredentialsFile, credentialsFileLines)) {

			if (credentialsFileLines.find(credentialsHashString) != string::npos ) {

				cout << "Welcome " << user << endl;

				this_thread::sleep_for(chrono::milliseconds(3000));

				system("cls");

				loggedInMenu(user);

			}

		}
		MyCredentialsFile.close();
	}
	else if (getline(MyCredentialsFile, credentialsFileLines)) {

		cout << "Oh oh... " << endl;
		cout << "It seems you credentials do not match, try again." << endl;

		system("pause");

		loginMenu();
	}

}

//account creation menu
void registerMenu() {

	string user, pass;

	// username input
	cout << "Username: ";
	cin >> user;

	createUserFile(user);

	bool masterValid = false;

	while (masterValid == false) {

		cout << "Password: ";
		cin >> pass;

		if (pass.length() < 8) {

			system("cls");

			cout << "Passwords must be 8 characters or more" << "\n\n";

		}

		else if (pass.length() >= 8) {

			masterValid = true;

			createHashFile(pass);

		}

	}

	int select;

	cout << "1. Login" << endl;
	cout << "2. EXIT" << endl;
	cout << "\nSelect: ";
	cin >> select;

	switch (select) {

	case 1:

		system("cls");

		loginMenu();

		break;

	case 2:

		system("cls");

		exitScreen();

	}

}

void getOneTimePass() {

	int passLen;
	bool validLen = false;

	while (validLen == false) {

		cout << "Enter the length of the password: ";
		cin >> passLen;

		if (passLen < 8 || passLen > 16) {

			system("cls");

			cout << "Remember, the length should be above 8 characters but below 16." << "\n\n";

		}

		else if (passLen >= 8) {

			validLen = true;

		}

	}

	const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789#@";
	const int charsLength = chars.length();

	string randomPass = "";

	srand(time(nullptr));

	for (int i = 0; i <= passLen; i++) {

		randomPass += chars[rand() % charsLength];

	}

	system("cls");

	cout << "Your " << passLen << " character password is: " << randomPass;

}

void mainMenu() {

	int options;

	cout << "1. Login" << endl;
	cout << "2. New to SimpleSave?, create an account!" << endl;
	cout << "3. Get Strong one time Password" << endl;
	cout << "4. EXIT" << "\n\n";
	cout << "Select: ";

	cin >> options;

	switch (options) {

	case 1:

		system("cls");

		loginMenu();

		break;

	case 2:

		system("cls");

		registerMenu();

		break;

	case 3:

		system("cls");

		getOneTimePass();

		break;


	case 4:

		system("cls");

		exitScreen();

		break;

	}

}

// main function
int main() {

	mainMenu();

}