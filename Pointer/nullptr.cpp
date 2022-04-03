#include <iostream>
using namespace std;

void func(char* str)
{
    cout<<"char*"<<endl;
}

void func(int i)
{
    cout<<"i"<<endl;
}

int main()
{
    func(0);
    return 0;
}