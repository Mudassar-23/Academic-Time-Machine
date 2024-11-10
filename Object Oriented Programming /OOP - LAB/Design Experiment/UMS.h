
#ifndef UMS_H
#define UMS_H

#include "USER.h"
#include "STUDENT.h"
#include "FACULTY.h"
#include "ADMIN.h"
#include "COURSE.h"
#include<fstream>
using namespace std;

#define MAX_USERS 100
#define MAX_COURSES 40
#define MAX_PREREQS 10

class UMS {
private:
    User* users[MAX_USERS];
    Course* courses[MAX_COURSES];
    int numUsers;
    int numCourses;

public:
    UMS();
    
    User* authenticateUser(string username, string password);
    void displayCourses();
    void displayPrerequisites(string courseCode);

    void addCourse(Course*course);


    void createUser();
    void enrollStudent(Student* student, string courseCode);

   
    void manageUserAccounts();

    void writeToFile(string filename, string data);
    void readUsersFromFile(const string& filename); 
    
    void updateUser();
    void deleteUser();
   

    ~UMS();
};

#endif
