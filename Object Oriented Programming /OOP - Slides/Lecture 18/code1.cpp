#include <iostream>
using namespace std;

    
class rectangleType
{
public:
    void setDimension(double l, double w);
      //Function to set the length and width of the rectangle.
      //Postcondition: length = l; width = w;

    double getLength() const;
      //Function to return the length of the rectangle.
      //Postcondition: The value of length is returned. 

    double getWidth() const;
      //Function to return the width of the rectangle.
      //Postcondition: The value of width is returned. 

    double area() const;
      //Function to return the area of the rectangle.
      //Postcondition: The area of the rectangle is 
      //               calculated and returned.

    double perimeter() const;
      //Function to return the perimeter of the rectangle.
      //Postcondition: The perimeter of the rectangle is 
      //               calculated and returned.

    void print() const;
      //Function to output the length and width of 
      //the rectangle.

    rectangleType();
      //Default constructor
      //Postcondition: length = 0; width = 0;

    rectangleType(double l, double w);
      //Constructor with parameters
      //Postcondition: length = l; width = w;

private:
    double length;
    double width;
};

void rectangleType::setDimension(double l, double w)
{
    if (l >= 0)
        length = l;
    else
        length = 0;

    if (w >= 0)
        width = w;
    else
        width = 0;
}

double rectangleType::getLength() const
{
    return length;
}

double rectangleType::getWidth()const
{
    return width;
}

double rectangleType::area() const
{
    return length * width;
}

double rectangleType::perimeter() const
{
     return 2 * (length + width);
}

void rectangleType::print() const
{
    cout << "Length = "  << length
         << "; Width = " << width;
}

rectangleType::rectangleType(double l, double w)
{
    setDimension(l, w);
}

rectangleType::rectangleType()
{
    length = 0;
    width = 0;
}


  
class boxType: public rectangleType
{
public:
    void setDimension(double l, double w, double h);
      //Function to set the length, width, and height 
      //of the box.
      //Postcondition: length = l; width = w; height = h;

    double getHeight() const;
      //Function to return the height of the box.
      //Postcondition: The value of height is returned. 

    double area() const;
      //Function to return the surface area of the box.
      //Postcondition: The surface area of the box is 
      //                calculated and returned.

    double volume() const;
      //Function to return the volume of the box. 
      //Postcondition: The volume of the box is 
      //               calculated and returned.

    void print() const;
      //Function to output the length, width, and height of a box.

    boxType();
      //Default constructor
      //Postcondition: length = 0; width = 0; height = 0;

    boxType(double l, double w, double h);
      //Constructor with parameters
      //Postcondition: length = l; width = w; height = h;

private:
    double height;
};


void boxType::setDimension(double l, double w, double h)
{
    rectangleType::setDimension(l, w);

    if (h >= 0)
        height = h;
    else
        height = 0;
}

double boxType::getHeight() const
{
    return height;
}

double boxType::area() const
{
    return  2 * (getLength() * getWidth()
               + getLength() * height 
               + getWidth() * height);
}

double boxType::volume() const
{
    return rectangleType::area() * height;
}

void boxType::print() const
{
    rectangleType::print();
    cout << "; Height = " << height;
}

boxType::boxType()	
{
    height = 0.0;
}

boxType::boxType(double l, double w, double h)
         : rectangleType(l, w)
{ 
    if (h >= 0)
        height = h;
    else
        height = 0;
}


int main()
{
    rectangleType myRectangle1;                    //Line 1
    rectangleType myRectangle2(8, 6);              //Line 2

    boxType myBox1;                                //Line 3
    boxType myBox2(10, 7, 3);                      //Line 4
    


    cout << "Line 6: myRectangle1: ";              //Line 6
    myRectangle1.print();                          //Line 7
    cout << endl;                                  //Line 8
    cout << "Line 9: Area of myRectangle1: "
         << myRectangle1.area() << endl;           //Line 9

    cout << "\n\nLine 10: myRectangle2: ";             //Line 10
    myRectangle2.print();                          //Line 11
    cout << endl;                                  //Line 12
    cout << "Line 13: Area of myRectangle2: "
         << myRectangle2.area() << endl;           //Line 13

    cout << "\n\nLine 14: myBox1: ";                   //Line 14
    myBox1.print();                                //Line 15
    cout << endl;                                  //Line 16
    cout << "Line 17: Surface Area of myBox1: "
         << myBox1.area() << endl;                 //Line 17
    cout << "Line 18: Volume of myBox1: "
         << myBox1.volume() << endl;               //Line 18

    cout << "\n\nLine 19: myBox2: ";                   //Line 19
    myBox2.print();                                //Line 20
    cout << endl;                                  //Line 21
    cout << "Line 22: Surface Area of myBox2: "
         << myBox2.area() << endl;                 //Line 22
    cout << "Line 23: Volume of myBox2: "
         << myBox2.volume() << endl;               //Line 23

    return 0;                                      //Line 24
}
