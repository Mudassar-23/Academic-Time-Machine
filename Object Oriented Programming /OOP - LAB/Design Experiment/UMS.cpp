#include "UMS.h"
#include"USER.h"
#include"STUDENT.h"
#include <iostream>
#include<fstream>
using namespace std;
// Constructor
UMS::UMS() : numUsers(0), numCourses(0) {
    for (int i = 0; i < MAX_USERS; ++i) {
        users[i] = nullptr;
    }
    for (int i = 0; i < MAX_COURSES; ++i) {
        courses[i] = nullptr;
    }
}
void UMS::addCourse(Course* course) {
    if (numCourses < MAX_COURSES) {
        courses[numCourses++] = course;
    }
    else {
        std::cout << "Maximum number of courses reached!" << std::endl;
    }
}



UMS::~UMS() {
    for (int i = 0; i < numUsers; ++i) {
        delete users[i];
    }
    for (int i = 0; i < numCourses; ++i) {
        delete courses[i];
    }
}


User* UMS::authenticateUser(string username, string password) {
    for (int i = 0; i < numUsers; ++i) {
        if (users[i]->getUsername() == username && users[i]->authenticate(password)) {
            return users[i];
        }
    }
    return nullptr;
}


void UMS::displayCourses() {
     cout << "Available Courses:" << endl;
    for (int i = 0; i < numCourses; ++i) {
        Course* course = courses[i];
        cout << course->getCourseCode() << " - " << course->getCourseName() << " (" << course->getCredits() << " credits)" << endl;
    }
}


void UMS::displayPrerequisites(string courseCode) {
    for (int i = 0; i < numCourses; ++i) {
        if (courses[i]->getCourseCode() == courseCode) {
            cout << "Prerequisites for course " << courseCode << ":" << endl;
            string* prereqs = courses[i]->getPrerequisites();
            int numPrereqs = courses[i]->getNumPrereqs();
            for (int j = 0; j < numPrereqs; ++j) {
                cout << prereqs[j] << std::endl;
            }
            return;
        }
    }
    cout << "Course not found!" << std::endl;
}

// Enroll a student in a course

void UMS::enrollStudent(Student* student, string courseCode) {
    Course* course = nullptr;
    // Find the course
    for (int i = 0; i < numCourses; ++i) {
        if (courses[i]->getCourseCode() == courseCode) {
            course = courses[i];
            break;
        }
    }

    if (!course) {
        cout << "Course " << courseCode << " does not exist!" << endl;
        return;
    }

    // Enroll the student in the course
    student->enroll(course);
    cout << "Student " << student->getUsername() << " enrolled in course " << courseCode << endl;


    string enrollmentInfo = "Enrolled in course: " + courseCode + "\n";
    writeToFile(student->getUsername() + "_enrolled.txt", enrollmentInfo);
}



void UMS::manageUserAccounts() {
    int choice;
    cout << "1. Create User\n";
    cout << "2. Update User\n";
    cout << "3. Delete User\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        createUser(); 
        break;
    case 2:
        updateUser();
        break;
    case 3:
        deleteUser();
        break;
    default:
        cout << "Invalid choice!\n";
        break;
    }
}


void UMS::createUser() {
    string username, password, role;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role: ";
    cin >> role;

    // Create user object based on role
    if (role == "student") {
        users[numUsers] = new Student(username, password);
    }
    else if (role == "faculty") {
        users[numUsers] = new Faculty(username, password);
    }
    else if (role == "admin") {
        users[numUsers] = new Admin(username, password);
    }
    else {
        cout << "Invalid role specified!\n";
        return;
    }
    numUsers++;

    // Write user information to output file
    string userData = "Username: " + username + ", Role: " + role + "\n";
    writeToFile("user_output.txt", userData);
}


void UMS::updateUser() {
    string username;
    cout << "Enter username of the user to update: ";
    cin >> username;

    // Find the user by username
    for (int i = 0; i < numUsers; ++i) {
        if (users[i]->getUsername() == username) {
           
            string newPassword;
            cout << "Enter new password: ";
            cin >> newPassword;
            users[i]->setPassword(newPassword);
            cout << "Password updated successfully!\n";

            // Write updated user information to output file
            string updatedUserData = "Username: " + username + ", New Password: " + newPassword + "\n";
            writeToFile("user_output.txt", updatedUserData);
            return;
        }
    }

    cout << "User not found!\n";
}
void UMS::writeToFile(string filename, string data) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << data << endl;
        outputFile.close();
    }
    else {
        cout << "Unable to open file: " << endl;
    }
}


void UMS::deleteUser() {
    string username;
    cout << "Enter username of the user to delete: ";
    cin >> username;   // Find the user by username

    for (int i = 0; i < numUsers; ++i) {
        if (users[i]->getUsername() == username) {
            // Write user deletion information to output file
            string deletedUserData = "User deleted: " + username + "\n";
            writeToFile("user_output.txt", deletedUserData);

            // Delete the user and shift the array
            delete users[i];
            for (int j = i; j < numUsers - 1; ++j) {
                users[j] = users[j + 1];
            }
            numUsers--;
            cout << "User deleted successfully!\n";
            return;
        }
    }

    cout << "User not found!\n";
}

void UMS::readUsersFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error: Unable to open user data file." << endl;
        return;
    }

    string username, password, role;
    while (numUsers < MAX_USERS && inFile >> username >> password >> role) {
        users[numUsers++] = new User(username, password, role);
    }

    inFile.close();
}
