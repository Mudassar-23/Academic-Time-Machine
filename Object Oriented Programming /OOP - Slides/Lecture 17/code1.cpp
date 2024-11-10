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
student list;

public:
course( string="",int =0,string ="", int = -1, string ="None");

void PrintDetails();
void RegisterStudent();
};

course::course(string CName, int CH, string IN,int rN, string sName):list(rN, sName)
{
Name=CName;
creditHours=CH;
InstructorName=IN;}

 
void course::RegisterStudent()
{
string N;
int rN;

cout<<"\n Enter Student Name ";
cin>>N;

cout<<"\n Enter Roll Number "; 
cin>>rN;

list.AddDetails(rN, N); }

void course:: PrintDetails()
{
	cout<<Name<<endl;
	cout<<creditHours<<endl;
	cout<<InstructorName<<endl;

cout<<"\nStudent Details  .. \n";
list.PrintDetails();
}

int main()
{
course Programming("Programming", 3 , "Tooba");
Programming.PrintDetails();
return 0;
}

