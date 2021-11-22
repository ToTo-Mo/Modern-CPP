#include <iostream>
#include <bitset>

int main(){
    unsigned char i = 0b10010111;
    std::cout << std::bitset<sizeof(i)*8>(i)<<std::endl;
    return 0;
}