#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "student.h"

using namespace std;

class Admin : public User {
public:

    Admin(string username, string password);
    bool authenticate(string enteredPassword);
    void AddCourse(string courseCode, string courseName, int credits, string prereqs[MAX_PREREQS], int numPrereqs);
    void enrollStudent(Student* student, string courseCode);
 
};

#endif