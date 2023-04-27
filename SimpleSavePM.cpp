
#include <iostream> // Library for input/output stream
#include <string> // Library for string manipulation
#include <vector> // Library for poitnters and vectors
#include <fstream> // Library for file manipulation
#include <chrono> // Library for time measurement and manipulation
#include <thread> // Library for multi-threading
#include <cstdio> // Library for data stream manipulation

using namespace std;

// Functions

// Exit screen
void exitScreen()
{
	system("cls");
	cout << R"(

       ____                 _ ____                  
      / ___| ___   ___   __| | __ ) _   _  ___      
     | |  _ / _ \ / _ \ / _` |  _ \| | | |/ _ \     
     | |_| | (_) | (_) | (_| | |_) | |_| |  __/     
      \____|\___/ \___/ \__,_|____/ \__, |\___|     
                                    |___/           

  
)";
}

//Function to decrypt the bundle
void decryptFile(const string& encryptedBundleFile)
{
	// Open the input file
	ifstream inputFile(encryptedBundleFile);

	if (!inputFile)
	{
		cerr << "Error opening input file." << endl;
		return;
	}

	// Open the output file
	ofstream outputFile("bundle.txt");

	if (!outputFile)
	{
		cerr << "Error opening output file." << endl;
		return;
	}

	// Decrypt the contents of the input file
	char c;

	while (inputFile.get(c))
	{
		c -= 5; // Subtract the encryption key from the ASCII code of each character to decrypt it

		outputFile.put(c); // Write the decrypted character to the output file
	}

	// Close the files
	inputFile.close();
	outputFile.close();

	const char* filename = "encrypted_bundle.txt";

	// Delete the old plain text file
	if (remove(filename) != 0) {

		cerr << "Error deleting file" << endl;

	}

	cout << "File decrypted successfully." << endl;

}


void encryptFile(const string& bundleFile) {

	// Open the input file
	ifstream inputFile(bundleFile);

	if (!inputFile)
	{
		cerr << "Error opening input file." << endl;

		return;
	}

	// Open the output file
	ofstream outputFile("encrypted_bundle.txt");

	if (!outputFile)
	{
		cerr << "Error opening output file." << endl;

		return;
	}

	// Encrypt the contents of the input file
	char c;
	while (inputFile.get(c))
	{
		c += 5; // Add the encryption key to the ASCII code of each character

		outputFile.put(c); // Write the encrypted character to the output file
	}

	// Close the files
	inputFile.close();
	outputFile.close();

	const char* filename = "bundle.txt";

	if (remove(filename) != 0) {

		cerr << "Error deleting file" << endl;

	}

	cout << "File encrypted successfully." << endl;
}

void decryptFileMenu() {

	string file;

	cout << R"(

     ____                             _   
    |  _ \  ___  ___ _ __ _   _ _ __ | |_ 
    | | | |/ _ \/ __| '__| | | | '_ \| __|
    | |_| |  __/ (__| |  | |_| | |_) | |_
    |____/ \___|\___|_|   \__, | .__/ \__|
                          |___/|_|


)";

	// The user has to enter the file name that he wants to decrypt (encrypted_bundle.txt)
	cout << "Enter file name: ";
	cin >> file;

	decryptFile(file);

}

// Hash Function
unsigned int Hash(string& data)
{

	unsigned int result(0);


	// for characters in data
	for (unsigned int ch : data)
	{

		result = ch + (result << 4) + (result << 10) - result;

	}

	return result;

}

// function for file creation
void createUserFile(string a)
{

	unsigned int hashUser{ Hash(a) };

	// creates the User File
	ofstream MyFile("users.txt", fstream::app);

	// adds the user hash to the file
	MyFile << hashUser << endl;

	// if statements for User file creation
	if (MyFile.is_open())
	{

		cout << "Username Selected\n\n" << endl;

	}
	else if (!MyFile.is_open())
	{

		cout << "Failed to create Username" << endl;

	}

	// closes the file
	MyFile.close();

}

void createHashFile(string a)
{

	unsigned int hashCredentials{ Hash(a) };

	// creates the credentials file
	ofstream MyFile("credentials.txt", fstream::app);

	// write data to the file
	MyFile << hashCredentials << endl;

	// if statements for password hash file creation
	if (MyFile.is_open())
	{

		cout << "Password saved Succesfully!" << endl;

	}
	else if (!MyFile.is_open())
	{

		cout << "Failed to save password" << endl;

	}

	// close the file
	MyFile.close();

	this_thread::sleep_for(chrono::milliseconds(3000));

	system("cls");
}

void createBundle()
{

	bool BundleMenu = false;
	int counter = 0;
	string url, username, password, addMore;

	// Lets the user store passwords for a maximum of 5 websites

	// Create Bundle File and appends any changes to it instead of overwriting it
	ofstream userBundle("bundle.txt", fstream::app);

	while (BundleMenu != true)
	{

		if (counter < 5)
		{

			cout << R"(

     ____                  _ _          
    | __ ) _   _ _ __   __| | | ___     
    |  _ \| | | | '_ \ / _` | |/ _ \    
    | |_) | |_| | | | | (_| | |  __/    
    |____/ \__,_|_| |_|\__,_|_|\___|    

 

)";

			cout << "Enter URL: ";
			cin >> url;

			cout << "Enter the username: ";
			cin >> username;

			cout << "Enter the password: ";
			cin >> password;


			// Saves input data provided by the user to the file
			userBundle << url << "\n";
			userBundle << username << endl;
			userBundle << password << "\n\n";

			// Checks if the data was saved and then it asks the user if they want to save more passwords
			if (userBundle.is_open()) {

				cout << "Data Saved Succesfully!\n\n" << endl;
				counter++;

				cout << "Do You wish to add another account? [Y]es/[N]o: ";
				cin >> addMore;
				if (addMore == "Y" || addMore == "y")
				{
					continue;
				}
				else if (addMore == "N" || addMore == "n")
				{
					counter = 5;
				}
				else
				{
					cout << "ERROR: Incorrect user input (Layer 8)...";
				}

			}
			else if (!userBundle.is_open()) {

				cout << "ERROR: Failed to save data..." << endl;

			}

		}
		else
		{

			// Closes the file
			userBundle.close();

			// Encrypts the bundle file
			encryptFile("bundle.txt");

			// Exit the loop
			BundleMenu = true;

		}
		system("cls");

		cout << R"(



				Thank Your for Trusting SimpleSave Password Manager




)";

		system("pause");

	}
}

void loggedInMenu()
{
	string options;

	cout << R"(
			  ____       _           _   
			 / ___|  ___| | ___  ___| |_ 
			 \___ \ / _ \ |/ _ \/ __| __|
			  ___) |  __/ |  __/ (__| |_ 
			 |____/ \___|_|\___|\___|\__|
                       


)";

	printf("\t\t\t\x1B[31m[C]\033[0mreate Bundle");
	printf("\t\t\x1B[31m[D]\033[0mecrypt");
	printf("\t\t\x1B[31m[E]\033[0mxit\n\n");

	cout << "Select an option: ";
	cin >> options;

	if (options == "C" || options == "c")
	{
		system("cls");
		createBundle();

	}
	else if (options == "D" || options == "d")
	{
		system("cls");
		decryptFileMenu();

	}
	else if (options == "E" || options == "e") {

		system("cls");
		exitScreen();

	}


}

// Login menu
void loginMenu()
{

	string user;
	string pass;
	string userFileLines;
	string credentialsFileLines;

	cout << R"(

     _                _          
    | |    ___   __ _(_)_ __     
    | |   / _ \ / _` | | '_ \    
    | |__| (_) | (_| | | | | |   
    |_____\___/ \__, |_|_| |_|   
                |___/            


)";

	cout << "Username: ";
	cin >> user;

	// Turn the username login into a hash
	unsigned int userHash{ Hash(user) };

	// change username hash to string
	string userHashString = to_string(userHash);

	// Check if the username entered by the user exists in the file
	ifstream MyUsersFile("users.txt");

	if (MyUsersFile.is_open())
	{

		while (getline(MyUsersFile, userFileLines))
		{

			if (userFileLines.find(userHashString) != string::npos)
			{

				cout << "Username exists...\n\n" << endl;

				break;

			}

		}
		MyUsersFile.close();

	}
	else
	{

		cout << "Unable to open file" << endl;

	}

	cout << "Password: ";
	cin >> pass;

	// Turn the Master Password login into a hash
	unsigned int passHash{ Hash(pass) };

	string credentialsHashString = to_string(passHash);

	ifstream MyCredentialsFile("credentials.txt");

	if (MyCredentialsFile.is_open())
	{

		while (getline(MyCredentialsFile, credentialsFileLines))
		{

			if (credentialsFileLines.find(credentialsHashString) != string::npos)
			{
				cout << "Succesfully logged in as " << user << " !";

				this_thread::sleep_for(chrono::milliseconds(4000));

				system("cls");

				loggedInMenu();

			}

		}
		MyCredentialsFile.close();
	}
	else if (getline(MyCredentialsFile, credentialsFileLines))
	{

		cout << "Oh oh... " << endl;
		cout << "It seems you credentials do not match, try again." << endl;

		system("pause");

		loginMenu();
	}

}

//account creation menu
void registerMenu()
{

	cout << R"(

      ____            _     _              
     |  _ \ ___  __ _(_)___| |_ ___ _ __    
     | |_) / _ \/ _` | / __| __/ _ \ '__|   
     |  _ <  __/ (_| | \__ \ ||  __/ |      
     |_| \_\___|\__, |_|___/\__\___|_|      
                |___/                       

)";


	string user, pass;

	// username input
	cout << "Username: ";
	cin >> user;

	createUserFile(user);

	bool masterValid = false;

	while (masterValid == false)
	{

		cout << "Password: ";
		cin >> pass;

		if (pass.length() < 8)
		{

			system("cls");

			cout << "Passwords must be 8 characters or more" << "\n\n";

		}
		else if (pass.length() >= 8)
		{

			masterValid = true;

			createHashFile(pass);

			cout << R"(

			 _    _ _____ _     _____ ________  ___ _____ 
			| |  | |  ___| |   /  __ \  _  |  \/  ||  ___|
			| |  | | |__ | |   | /  \/ | | | .  . || |__  
			| |/\| |  __|| |   | |   | | | | |\/| ||  __| 
			\  /\  / |___| |___| \__/\ \_/ / |  | || |___ 
			 \/  \/\____/\_____/\____/\___/\_|  |_/\____/ 

)";

			cout << "                        Succesfully joined SimpleSave as " << user << " !";

			this_thread::sleep_for(chrono::milliseconds(4000));

			system("cls");

		}

	}

	string options;

	cout << R"(

			  ____  _                 _        ____                  
			 / ___|(_)_ __ ___  _ __ | | ___  / ___|  __ ___   _____ 
			 \___ \| | '_ ` _ \| '_ \| |/ _ \ \___ \ / _` \ \ / / _ \
			  ___) | | | | | | | |_) | |  __/  ___) | (_| |\ V /  __/
			 |____/|_|_| |_| |_| .__/|_|\___| |____/ \__,_| \_/ \___|
                                           |_|

)";

	printf("\t\t\t\t\t\x1B[31m[L]\033[0mogin");
	printf("\t\t\x1B[31m[E]\033[0mxit\n\n");

	cout << "Select an option: ";
	cin >> options;

	if (options == "L" || options == "l")
	{
		system("cls");
		loginMenu();

	}
	else if (options == "E" || options == "e")
	{
		system("cls");
		exitScreen();

	}

}

void getOneTimePass()
{

	int passLen;
	bool validLen = false;

	while (validLen == false)
	{

		cout << "Enter the length of the password: ";
		cin >> passLen;

		// Checks if the user's chosen password length is above 8 but below 64
		// THIS DOES NOT SAVE IT PERMANENTLY THE USER HAS TO COPY AND PASTE IT
		if (passLen < 8 || passLen > 64)
		{
			system("cls");

			cout << "Remember, the length should be above 8 characters but below 64." << "\n\n";
		}

		else if (passLen >= 8)
		{

			validLen = true;

		}

	}

	const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=/;,.\"\'\'\\";
	const int charsLength = chars.length();

	string randomPass = "";

	srand(time(nullptr));

	for (int i = 0; i <= passLen; i++)
	{

		randomPass += chars[rand() % charsLength];

	}

	system("cls");

	cout << "Your " << passLen << " length, One Time Password is: " << randomPass << "\n\n";

}

// Main Menu
void mainMenu()
{

	string options;

	cout << R"(

			  ____  _                 _        ____                  
			 / ___|(_)_ __ ___  _ __ | | ___  / ___|  __ ___   _____ 
			 \___ \| | '_ ` _ \| '_ \| |/ _ \ \___ \ / _` \ \ / / _ \
			  ___) | | | | | | | |_) | |  __/  ___) | (_| |\ V /  __/
			 |____/|_|_| |_| |_| .__/|_|\___| |____/ \__,_| \_/ \___|
                                           |_|

	Welcome to SimpleSave a simple way to save your passwords in a secure environment!

)";

	// Menu options with custom colors
	printf("\t\t\x1B[31m[L]\033[0mogin");
	printf("\t\t\x1B[31m[C]\033[0mreate Account");
	printf("\t\x1B[31m[G]\033[0menerate OTP");
	printf("\t\t\x1B[31m[E]\033[0mxit\n\n");

	cout << "Select an option: ";
	cin >> options;


	if (options == "L" || options == "l")
	{
		system("cls");

		loginMenu();

	}
	else if (options == "C" || options == "c")
	{
		system("cls");

		registerMenu();

	}
	else if (options == "G" || options == "g")
	{
		system("cls");

		getOneTimePass();

	}
	else if (options == "E" || options == "e")
	{
		system("cls");

		exitScreen();

	}

}

// Main function
int main()
{

	mainMenu();

}
