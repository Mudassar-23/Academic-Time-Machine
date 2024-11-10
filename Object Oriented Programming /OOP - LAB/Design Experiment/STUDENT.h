#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "course.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#define MAX_ENROLLED_COURSES 10

class Student : public User {
private:
    Course* enrolledCourses[MAX_ENROLLED_COURSES];
    float examMarks[MAX_ENROLLED_COURSES];
    string grades[MAX_ENROLLED_COURSES];
    int numCoursesEnrolled;

public:
    Student(string username, string password);
    bool authenticate(string enteredPassword);
    void enroll(Course* course);
    void addExamMark(Course* course, float marks);
    void addGrade(Course* course, string grade);
    void viewCourses();
 
    int getNumCoursesEnrolled() const;
    string getEnrolledCourses();
    float calculateGPA();
    void writeTranscriptToFile(string& transcriptData);
};

#endif
