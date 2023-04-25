
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;
int qstate;

// functions

void createUserFile(int a) {

    // creates the User File
    ofstream file("users.txt");

    // adds the user hash to the file
    file << a;
    
    // if statements for User creation
    if (file.is_open()) {

        cout << "User Created Succesfully!" << endl;

    }
    else if (!file.is_open()) {

        cout << "Failed to create User" << endl;

    }

    // closes the file
    file.close();

}

void createHashFile(int a) {

    // create a files
    ofstream file("users.txt");

    // write data to the file
    file << a;

    // if statements for password hash file creation
    if (file.is_open()) {

        cout << "Password saved Succesfully!" << endl;

    }
    else if (!file.is_open()) {

        cout << "Failed to save password" << endl;

    }

    // close the file
    file.close();

}

// Hash Function
unsigned int Hash(string& data) {

    unsigned int result(0);

    for (unsigned int ch : data) {

        result = ch + (result << 4) + (result << 10) - result;

    }

    return result;

}

// encrypt function 
string encrypt(string a) {

    // encrypt: abc : jkl

    for (int i = 0; i < a.size(); i++) {

        a[i] = a[i] + 9;

    }

    return a;

}

// decrypt function
string decrypt(string a) {

    // decrypt: jkl : abc

    for (int i = 0; i < a.size(); i++) {

        a[i] = a[i] - 9;

    }

    return a;


}

// Hash Validation 
bool checkHash(int a, int b) {

    return a == b;

}

void exitScreen() {

    system("cls");

    cout << "Goodbye";

}


void loginMenu() {


}

void registerMenu() {

    string user, master;

    cout << "Username: ";
    cin >> user;

    unsigned int hashUser{ Hash(user) };

    createUserFile(hashUser);

    bool masterValid = false;

    while (masterValid == false) {

        cout << "Master password: ";
        cin >> master;

        if (master.length() < 8) {

            system("cls");

            cout << "Passwords must be 8 characters or more" << "\n\n";

        }

        else if (master.length() >= 8) {

            masterValid = true;

        }

    }

    unsigned int hashMaster{ Hash(master) };

    createHashFile(hashMaster);

    int select;

    cout << "Login" << endl;
    cout << "EXIT" << endl;
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

        if (passLen < 8) {

            system("cls");

            cout << "remember, the length should be above 8 characters." << "\n\n";

        }

        else if (passLen >= 8) {

            validLen = true;

        }

    }

    const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int charsLength = chars.length();

    string randomPass = "";

    srand(time(nullptr));

    for (int i = 0; i <= passLen; i++) {

        randomPass += chars[rand() % charsLength];

    }

    cout << "Your random password is: " << randomPass;

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