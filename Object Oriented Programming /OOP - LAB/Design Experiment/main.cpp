#include "Faculty.h"
#include "Admin.h"
#include "Student.h"
#include "UMS.h"
#include "Course.h"
#include "User.h"
#include <iostream>
#include <fstream>

using namespace std;
int main() {
    UMS ums;
    ums.readUsersFromFile("user.txt");

    // Add courses
    Course* course1 = new Course("CSE101", "Computer Science", 3, nullptr, 0);
    Course* course2 = new Course("MAT101", "Calculus I", 4, nullptr, 0);
    Course* course3 = new Course("PHY101", "Physics I", 4, nullptr, 0);

    ums.addCourse(course1);
    ums.addCourse(course2);
    ums.addCourse(course3);
    while (true) {
       
        cout << "Welcome to the University Management System (UMS)" << endl;
        cout << "\nMenu\n" << endl;
        cout << "1. Student" << endl;
        cout << "2. Faculty" << endl;
        cout << "3. Administrator" << endl;
        cout << "4. Admin" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        string username, password,data;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        User* user = ums.authenticateUser(username, password);
        if (user != nullptr) {
            switch (choice) {
            case 1:
            {
                cout << "Welcome Student!" << endl;
                cout << "1. View Transcript" << endl;
                cout << "2. View Enrolled Courses" << endl;
                cout << "Enter your choice: ";

                
                int studentChoice;
                cin >> studentChoice;

                if (Student* studentUser = dynamic_cast<Student*>(user)) {
                    switch (studentChoice) {
                    case 1:
                        studentUser->calculateGPA();
                        studentUser->writeTranscriptToFile(data);
                        break;
                    case 2:
                  
                        studentUser->viewCourses();
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        break;
                    }
                }
                else {
                    cout << "Invalid user type for student actions!" << endl;
                }
                break;

            }
            case 2: 
            {
                Faculty* faculty = dynamic_cast<Faculty*>(user);
                if (faculty) {
                    cout << "\nWelcome Faculty!" << endl;
                
                    Student* student = new Student("USMAN", "1254");
                    Course* course = new Course("CSE101", "Computer Science", 3, nullptr, 0);
                    float marks = 85.0;
                    string grade = "A";
                    faculty->addExamMarks(student, course, marks);
                    faculty->updateExamMarks(student, course, marks);
                    faculty->uploadGrade(student, course, grade);
                }
                else {
                    cout << "Error: User is not a faculty member." << endl;
                    return 1;
                }
                break;
            }
            case 3: // Administrator
            {
                cout << "\nWelcome Administrator!" << endl;
                cout << "1. Manage user acccount " << endl;
                cout << "2. Update user " << endl;
                cout << "3. DisplayCourses " << endl;
                cout << "4. DisplayPrerequisite" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 1) {
                    ums.manageUserAccounts();
                }
                else if (choice == 2) {
                    ums.updateUser();
                }
                else if (choice == 3) {
                    ums.displayCourses();
                }// Display available courses
                else if (choice == 4) {
                    ums.displayPrerequisites("CSE101");
                }
                break;
            }  
            case 4:
            {
                cout << "Welcome Admin!" << endl;
                cout << "1. Add new course" << endl;
                cout << "2. Enroll student in a course" << endl;
                cout << "Enter your choice: ";
               
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
                return 1; // Exit 
            }
        }
        else {
            cout << "Authentication failed. Invalid username or password." << endl;
            return 1; 
        }
    }
    return 0;
}
