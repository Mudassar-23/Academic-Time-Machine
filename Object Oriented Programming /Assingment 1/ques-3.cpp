#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string rollNumber;
    string name;
    string courseCodes[5]; 
    int numCourses;
};
void loadDataFromFile(ifstream & inputFile, Student& student) {
    
    if (inputFile.is_open()) {
        inputFile >> student.rollNumber;
       
        getline(inputFile, student.name);

        student.numCourses = 0;
        string courseCode;

        while (inputFile >> courseCode && student.numCourses < 5) {
            student.courseCodes[student.numCourses++] = courseCode;
        }

        inputFile.close();
    }
    else {
        cout << "Unable to open RollNumber file ";
    }
}
bool hasStudiedCourse( Student& student,  string& courseCode) {
    for (int i = 0; i < student.numCourses; i++) {
        if (student.courseCodes[i] == courseCode) {
            return true;
            break;
        }
    }
    return false;
}
int main() {
    Student student;
    string rollNumber,courseCode;

    cout << "Enter student's roll number: ";
    cin >> rollNumber;

    cout << "Enter course code: ";
    cin >> courseCode;
    ifstream   inFile;
    inFile.open("rollnumber.txt");

    loadDataFromFile(inFile, student);

    if (hasStudiedCourse(student, courseCode)) {
        cout << "Student with roll number " << student.rollNumber << " has studied course " << courseCode << "." << endl;
    }
    else {
        cout << "Student with roll number " << student.rollNumber << " has not studied course " << courseCode << "." << endl;
    }
  
}

