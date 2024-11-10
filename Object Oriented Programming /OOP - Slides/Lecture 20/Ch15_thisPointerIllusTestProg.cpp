//Chapter 15: this pointer illustration
  
#include <iostream>
#include "thisPointerIllus.h"

using namespace std;

int main()
{
    thisPointerClass object1(3, 5, 7);      //Line 1
    thisPointerClass object2;               //Line 2

    cout << "Object 1: ";                   //Line 3
    object1.print();                        //Line 4

    object2 = object1.updateXYZ();          //Line 5

    cout << "After updating object1: ";     //Line 6
    object1.print();                        //Line 7

    cout << "Object 2: ";                   //Line 8
    object2.print();                        //Line 9

    return 0;
}
