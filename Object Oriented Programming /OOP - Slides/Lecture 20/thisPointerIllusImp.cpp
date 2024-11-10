  
#include <iostream>
#include "thisPointerIllus.h"

using namespace std;

void thisPointerClass::set(int a, int b, int c)
{
    x = a;
    y = b;
    z = c;
}

void thisPointerClass::print() const
{
    cout << "x = " << x
         << ", y = " << y
         << ", z = " << z << endl;
}

thisPointerClass thisPointerClass::updateXYZ()
{
    x = 2 * x; 
    y = y + 2;
    z = z * z;

    return *this;
}

thisPointerClass::thisPointerClass(int a, int b, int c)
{
    x = a;
    y = b;
    z = c;
}

