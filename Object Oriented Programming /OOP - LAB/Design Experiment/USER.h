#ifndef USER_H
#define USER_H

#include <string>
#include<fstream>
using namespace std;

class User {
protected:
    string username;
    string password;
    string role;

public:
    User(string username, string password,string r);
    virtual bool authenticate(string enteredPassword);
    void setPassword(string);
    string getUsername();
    void writeUserFile(User users[], int& numUsers);
    void readUserDetailsFromFile(User users[], int& numUsers);
};

#endif 