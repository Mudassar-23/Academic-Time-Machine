//Test Program: class personType
 
#include <iostream>
#include <string>
#include "personType.h"

using namespace std;

int main()
{
    personType student1("Angela", "Smith");               //Line 1

    personType student2;                                  //Line 2

    personType student3;                                  //Line 3

    cout << "Line 4 -- Student 1: ";                      //Line 4
    student1.print();                                     //Line 5
    cout << endl;                                         //Line 6

    student2.setFirstName("Shelly").setLastName("Malik"); //Line 7

    cout << "Line 8 -- Student 2: ";                      //Line 8
    student2.print();                                     //Line 9
    cout << endl;                                         //Line 10

    student3.setFirstName("Chelsea");                     //Line 11

    cout << "Line 12 -- Student 3: ";                     //Line 12
    student3.print();                                     //Line 13
    cout << endl;                                         //Line 14

    student3.setLastName("Tomek");                        //Line 15

    cout << "Line 16 -- Student 3: ";                     //Line 16
    student3.print();                                     //Line 17
    cout << endl;                                         //Line 18

    return 0;
}
