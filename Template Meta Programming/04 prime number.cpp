#include <iostream>

template <int N>
struct IsPrime
{
    static const bool value = IsPrime<N>::value;
};

template <int N>
struct IsPrime
{
    static const bool value = !check_div<N, 2>::value;
};

template <int N, int d>
struct check_div
{
    static const bool value = (N % d == 0) || check_div<N, d+1>::value;
};


template <>
struct IsPrime<2>
{
    static const bool value = true;
};

template <>
struct IsPrime<3>
{
    static const bool value = true;
};

int main()
{
    std::cout << "Is prime ? :: " << IsPrime<2>::value << std::endl;  // true
    std::cout << "Is prime ? :: " << IsPrime<10>::value << std::endl; // false

    std::cout << "Is prime ? :: " << IsPrime<11>::value << std::endl; // true
    std::cout << "Is prime ? :: " << IsPrime<61>::value << std::endl; // true
}