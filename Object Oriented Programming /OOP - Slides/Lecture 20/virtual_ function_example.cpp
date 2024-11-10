#include <iostream>
using namespace std;

    
class shape
{
protected:
float area;
public:
shape();
float calc_area();
};
shape::shape()
{
area=0;
}

float shape::calc_area()
{
area=1;
return area;
}



class circle: public shape
{
private:
float  radius;

public:
circle(float=1);
float calc_area()
{
area=3.14*radius*radius;
return area;
}

};

circle::circle(float r)
{
radius=r;
}

class triangle: public shape
{
private:
float  base;
float height;

public:
triangle(float=1, float=1);
float calc_area()
{
area=0.5*base*height;
return area;
}
};

triangle::triangle(float b, float h)
{
base=b;
height=h;
}

class rectangle: public shape
{
private:
float  base;
float length;

public:
rectangle(float =1, float=1);
float calc_area()
{
area=base*length;
return area;
}
};

rectangle::rectangle(float b, float l)
{
base=b;
length=l;
}


int main()
{

shape *ptr;
char choice;
cin>>choice;

if(choice=='T')
ptr=new triangle(1,5);
else if (choice =='C') 
ptr=new circle(3);
else
ptr=new rectangle(3,4);

cout<<"\nArea= "<<ptr->calc_area();



return 0;
}
