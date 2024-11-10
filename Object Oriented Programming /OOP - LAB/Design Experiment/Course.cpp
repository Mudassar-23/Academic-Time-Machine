#include "Course.h"
#include<fstream>
using namespace std;

Course::Course(string code, string name, int credits, string prereqs[MAX_PREREQS], int numPrereqs)
    : courseCode(code), courseName(name), credits(credits), numPrereqs(numPrereqs) {
    for (int i = 0; i < numPrereqs; ++i) {
        prerequisites[i] = prereqs[i];
    }
}

string Course::getCourseCode() {
    return courseCode;
}

string Course::getCourseName() {
    return courseName;
}

int Course::getCredits() {
    return credits;
}

string* Course::getPrerequisites() {
    return prerequisites;
}

int Course::getNumPrereqs() {
    return numPrereqs;
}
