#ifndef COURSE_H
#define COURSE_H

#define MAX_PREREQS 10

#include <string>
#include<fstream>
using namespace std;

class Course {
private:
    string courseCode;
    string courseName;
    int credits;
    string prerequisites[MAX_PREREQS];
    int numPrereqs;

public:
 
    Course(string code, string name, int credits, string prereqs[MAX_PREREQS], int numPrereqs);
    string getCourseCode();
    string getCourseName();
    int getCredits();
    string* getPrerequisites();
    int getNumPrereqs();
  
};

#endif