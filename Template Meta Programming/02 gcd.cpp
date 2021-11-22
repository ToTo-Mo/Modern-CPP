#include <iostream>

template <int X, int Y>
struct GCD
{
    static const int value = GCD<Y, X % Y>::value;
};

template <int X>
struct GCD<X, 0>
{
    static const int value = X;
};

template <int N, int D = 1>
struct Ratio
{
    using type =  Ratio<N, D>;
    static const int num = N;
    static const int den = D;
};

template <class R1, class R2>
struct _Ratio_Add
{
    using type =  Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_Add : _Ratio_Add<R1, R2>::type
{
};

template <class R1, class R2>
struct _Ratio_Sub
{
    using type =  Ratio<R1::num * R2::den - R2::num * R1::den, R1::den * R2::den>;
};

template <class R1, class R2>
struct Ratio_Sub : _Ratio_Sub<R1, R2>::type{};

int main()
{
    std::cout << "gcd(36, 24) = " << GCD<36, 24>::value << std::endl;

    /*
        c++ 11 부터 typedef 대신 using 키워드를 지원한다.

        typedef Ratio<2, 3> r1;
        using r1 = Ratio<2,3>;
    */

    using r1 =  Ratio<2, 3>;
    using r2 =  Ratio<3, 3>;

    using r3 =  Ratio_Add<r1, r2>;
    std::cout << r3::num << " / " << r3::den << std::endl;

    using r4 = Ratio_Sub<r1, r2>;
    std::cout<<r4::num<<" / "<<r4::den<<std::endl;
}
