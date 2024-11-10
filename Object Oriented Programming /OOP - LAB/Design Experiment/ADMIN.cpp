#include "admin.h"
#include <iostream>
#include<fstream>
using namespace std;
Admin::Admin(string username, string password) : User(username, password,role) {}

bool Admin::authenticate(string enteredPassword) {
    return User::authenticate(enteredPassword);
}


// Add a new course
void Admin::AddCourse(string courseCode, string courseName, int credits, string prereqs[MAX_PREREQS], int numPrereqs) {
    ofstream outputFile("add_course.txt"); 
    if (outputFile.is_open()) {
        outputFile << "Course added: " << courseCode << " - " << courseName << " (" << credits << " credits)" << endl;
        outputFile.close();
    }
    else {
        cout << "Unable to open file for writing course information." << endl;
    }
}

// Enroll a student in a course
void Admin::enrollStudent(Student* student, string courseCode) {
   
      cout << "Student " << student->getUsername() << " enrolled in course " << courseCode << endl;

 
    ofstream outputFile("Enrollment.txt");
    if (outputFile.is_open()) {
        outputFile << "Student " << student->getUsername() << " enrolled in course " << courseCode << endl;
        outputFile.close();
    }
    else {
        cout << "Unable to open file for writing enrollment information." << endl;
    }
}
