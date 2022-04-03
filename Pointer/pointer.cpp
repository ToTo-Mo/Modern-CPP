#include <iostream>
using namespace std;

int main()
{
    int* pInt1;             // X, 초기화되지 않은 포인터 변수
    int* pInt2 = nullptr;   // O

    cout<<pInt1<<endl;
    cout<<pInt2<<endl;

    int* pInt = new int;
    *pInt = 12;
}