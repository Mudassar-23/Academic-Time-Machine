#include "user.h"
#include<iostream>
#include<fstream>

User::User(string username, string password, string r) : username(username), password(password),role(r) {}


bool User::authenticate(string enteredPassword) {
    return password == enteredPassword;
}

string User::getUsername() {
    return username;
}

void User::setPassword(string a) {
    password = a;
}

void User::writeUserFile(User users[], int & numUsers) {
    ofstream userFile("user_details.txt");
    if (userFile.is_open()) {
        for (int i = 0; i < numUsers; ++i) {
            userFile << "Username: " << users[i].username << endl;
            userFile << "Password: " << users[i].password << endl;
            userFile << "Role: " << users[i].role << endl;
            userFile << endl;
        }
        userFile.close();
        cout << "\nUser details written to user_details.txt File" << endl;
    }
    else {
        cout << "Unable to open user_details.txt for writing" << endl;
    }
}

void User::readUserDetailsFromFile(User users[], int& numUsers) {
    ifstream userFile("user.txt");
    if (userFile.is_open()) {
        numUsers = 0;
        string username, password, role, firstName;
        while (numUsers < 5 && userFile >> username >> password >> role) {
            users[numUsers].username = username;
            users[numUsers].password = password;
            users[numUsers].role = role;
            
            numUsers++;
        }
        userFile.close();
        cout << "\nUser details read from user_details.txt" << endl;
    }
    else {
        cout << "Unable to open user_details.txt for reading" << endl;
    }
}
