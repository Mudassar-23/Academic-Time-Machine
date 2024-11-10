#include <iostream>
#include<cstring>
using namespace std;
 
// Function to reverse the string 
// using pointers 
void reverseString(char* str) 
{ 
  int l, i; 
  char *begin_ptr, *end_ptr, ch; 
 
  // Get the length of the string 
  l = strlen(str); 
 
  // Set the begin_ptr
  // initially to start of string 
  begin_ptr = str;
   
  //Setting end_ptr initially to
  //the end of the string
  end_ptr = str + l - 1;
 
  // Swap the char from start and end 
  // index using begin_ptr and end_ptr 
  for (i = 0; i < (l - 1) / 2; i++) { 
 
    // swap character 
    ch = *end_ptr; 
    *end_ptr = *begin_ptr; 
    *begin_ptr = ch; 
 
    // update pointers positions 
    begin_ptr++; 
    end_ptr--; 
  } 
} 
 
// Driver code 
int main() 
{ 
 
  // Get the string 
  char str[100] = "OOPSP24"; 
  cout<<"Enter a string: "<<str<<endl;
 
  // Reverse the string 
  reverseString(str); 
 
  // Print the result 
  cout<<"Reverse of the string:"<<str; 
 
  return 0; 
} 