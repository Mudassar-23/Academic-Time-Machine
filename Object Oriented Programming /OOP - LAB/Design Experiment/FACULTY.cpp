#include "Faculty.h"
#include "Student.h"
#include <iostream>
using namespace std;

Faculty::Faculty(string username, string password) : User(username, password,role) {}


bool Faculty::authenticate(string enteredPassword) {
    return User::authenticate(enteredPassword);
}

void Faculty::addExamMarks(Student* student, Course* course, float marks) {
    student->addExamMark(course, marks);
    
    string transcriptData = "Exam marks added for student " + student->getUsername() + " in course " + course->getCourseCode() + ". Marks: " + to_string(marks);
    student->writeTranscriptToFile(transcriptData);
}

// Update exam marks for a student in a course
void Faculty::updateExamMarks(Student* student, Course* course, float marks) {
    // Since Student class doesn't have an updateExamMark method, we'll use the addExamMarks method to overwrite the marks
    addExamMarks(student, course, marks);
}

// Upload grade for a student in a course
void Faculty::uploadGrade(Student* student, Course* course, string grade) {
    student->addGrade(course, grade);
    // Write to transcript file
    string transcriptData = "Grade uploaded for student " + student->getUsername() + " in course " + course->getCourseCode() + ". Grade: " + grade;
    student->writeTranscriptToFile(transcriptData);
}
