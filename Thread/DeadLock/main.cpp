//#include "lock.h"
//#include <iostream>
//#include <thread>
//
//using namespace std;
//
//int a;
//CriticalSection aMutex;
//
//int b;
//CriticalSection bMutex;
//
//int main()
//{
//    thread t1([](){
//        while (1)
//        {
//            CriticalSectionLock lock(aMutex);
//            a++;
//            CriticalSectionLock lock2(bMutex);
//            b++;
//
//            cout<<"t1 done"<<endl;
//        }
//    });
//
//    thread t2([](){
//        while(1)
//        {
//            CriticalSectionLock lock(bMutex);
//            b++;
//            CriticalSectionLock lock2(aMutex);
//            a++;
//            cout<<"t2 done"<<endl;
//        }
//    });
//
//    t1.join();
//    t2.join();
//
//    return 0;
//}