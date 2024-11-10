#include "student.h"
#include <iostream>
#include <fstream>

Student::Student(string username, string password) : User(username, password,role), numCoursesEnrolled(0) {}

bool Student::authenticate(string enteredPassword) {
    return User::authenticate(enteredPassword);
}

void Student::enroll(Course* course) {
    if (numCoursesEnrolled >= MAX_ENROLLED_COURSES) {
        cout << "Maximum number of courses enrolled reached!" << endl;
        return;
    }

    enrolledCourses[numCoursesEnrolled++] = course;
}

void Student::addExamMark(Course* course, float marks) {
    for (int i = 0; i < numCoursesEnrolled; ++i) {
        if (enrolledCourses[i] == course) {
            examMarks[i] = marks;
            return;
        }
    }
    cout << "Course not found in enrolled courses!" << endl;
}

void Student::addGrade(Course* course, string grade) {
    for (int i = 0; i < numCoursesEnrolled; ++i) {
        if (enrolledCourses[i] == course) {
            grades[i] = grade;
            return;
        }
    }
    cout << "Course not found in enrolled courses!" << endl;
}

void Student::viewCourses() {
    cout << "Enrolled Courses:" << endl;
    for (int i = 0; i < numCoursesEnrolled; ++i) {
        cout << enrolledCourses[i]->getCourseCode() << " - " << enrolledCourses[i]->getCourseName() << endl;
    }
}

int Student::getNumCoursesEnrolled() const {
    return numCoursesEnrolled;
}

string Student::getEnrolledCourses() {
    string courses;
    for (int i = 0; i < numCoursesEnrolled; ++i) {
        courses += enrolledCourses[i]->getCourseCode();
        if (i < numCoursesEnrolled - 1) {
            courses += ", ";
        }
    }
    return courses;
}

float Student::calculateGPA() {
  
    float totalGradePoints = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < numCoursesEnrolled; ++i) {
   
        Course* course = enrolledCourses[i];
        int credits = course->getCredits();

       
        float gradePoints = 0.0;
        if (examMarks[i] >= 90.0) {
            grades[i] = "A+";
            gradePoints = 4.0;
        }
        else if (examMarks[i] >= 80.0) {
            grades[i] = "A";
            gradePoints = 3.0;
        }
        else if (examMarks[i] >= 70.0) {
            grades[i] = "B";
            gradePoints = 2.0;
        }
        else if (examMarks[i] >= 60.0) {
            grades[i] = "C";
            gradePoints = 1.0;
        }
        else {
            grades[i] = "F";
            gradePoints = 0.0;
        }

        // Update total grade points and credits
        totalGradePoints += gradePoints * credits;
        totalCredits += credits;
    }

   
    float gpa = totalGradePoints / totalCredits;
    return gpa;
}
void Student::writeTranscriptToFile( string& transcriptData) {
    ofstream transcriptFile("transcript.txt");
    if (!transcriptFile.is_open()) {
        cout << "Unable to open transcript file!" << endl;
        return;
    }

    transcriptFile << "Transcript for Student: " << getUsername() << endl << endl;
    transcriptFile << "-------------------------------------------" << endl;
    // Write details for each enrolled course
    for (int i = 0; i < numCoursesEnrolled; ++i) {
        Course* course = enrolledCourses[i];
        
        transcriptFile << "Course Code: " << course->getCourseCode() << endl;
        transcriptFile << "Course Name: " << course->getCourseName() << endl;
        transcriptFile << "Exam Marks: " << examMarks[i] << endl;
        transcriptFile << "Grade: " << grades[i] << endl << endl;
    }
    transcriptFile << "-------------------------------------------" << endl;

    
    transcriptFile << "GPA: " << calculateGPA() << endl;

    transcriptFile.close();
    cout << "Transcript generated and saved to transcript.txt" << endl;
}
