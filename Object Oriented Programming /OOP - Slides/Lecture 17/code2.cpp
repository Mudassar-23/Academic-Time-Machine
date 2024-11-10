#include <iostream>
using namespace std;
#include <string>

class student 
{
int rollNumber;
string Name;

public:

student(int =0, string="Default");
void AddDetails(int, string);
void PrintDetails();

};

student::student(int rN, string N)
{
rollNumber=rN;
Name=N;
}

void student::PrintDetails()
{
cout<<rollNumber<<" "<<Name<<endl;
}

void student::AddDetails(int rN, string N)
{
rollNumber=rN;
Name=N;
}


class course
{
private:

string Name;
int creditHours;
string InstructorName;
student list[35];
int currentStudents;

public:
course( string="", int =0, string ="");

void PrintDetails();
void RegisterStudent();
};

//constructor of container class
course::course(string CName, int CH, string IN)
{
Name=CName;
creditHours=CH;
InstructorName=IN;
currentStudents=0;}

 
void course::RegisterStudent()
{
string N;
int rN;

cout<<"\n Enter Student Name ";
cin>>N;

cout<<"\n Enter Roll Number "; 
cin>>rN;

list[currentStudents].AddDetails(rN, N);
currentStudents++;}

void course:: PrintDetails()
{
	cout<<Name<<endl;
	cout<<creditHours<<endl;
	cout<<InstructorName<<endl;
	for (int i=0; i< 2 ; i++)
	list[i].PrintDetails();}




int main()
{
course Programming("Programming", 3 , "Tooba");

Programming.PrintDetails();

return 0;}
