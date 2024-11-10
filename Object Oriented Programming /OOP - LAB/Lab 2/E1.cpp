#include<iostream>
#include<string>
using namespace std;
void resize(int *p,int size, int newsize)
{
    if(size<newsize)
    {
        int *q= new int[newsize];
        for(int i=0;i<size;i++)
        {
            q[i]=p[i];}
            for(int i=size;i<newsize;i++)
            {q[i]=0;}
            for (int i=0;i<newsize;i++)
            {
                cout<<q[i]<<" ";
            }
        }
            if (size>newsize)
            {
                int *q= new int[newsize];
        for(int i=0;i<newsize;i++)
        {
            q[i]=p[i];}
            for (int i=0;i<newsize;i++)
            {
                cout<<q[i]<<" ";
            }
            }
        }
    

int main()
{
    int size, newsize;
    cout<<"Enter size of array"<<endl;
    cin>>size;
    int *p=new int[size];
    cout<<"Enter the elements of array"<<endl;
    for (int i=0;i<size;i++)
    {cin>>p[i];
    }
    cout<<"Enter the new size of array"<<endl;
    cin>>newsize;
    cout<<"Elements in array:";
    resize(p,size,newsize);
    cout<<endl;
    delete[] p;
    return 0;
    
}