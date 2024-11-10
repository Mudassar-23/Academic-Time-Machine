#ifndef FACULTY_H
#define FACULTY_H

#include "USER.h"
#include "STUDENT.h"
#include "COURSE.h" 
using namespace std;

class Faculty : public User {
public:
    Faculty(string username, string password);
    bool authenticate(string enteredPassword);


    void addExamMarks(Student* student, Course* course, float marks); 
    void updateExamMarks(Student* student, Course* course, float marks); 
    void uploadGrade(Student* student, Course* course, string grade); 
};

#endif 
