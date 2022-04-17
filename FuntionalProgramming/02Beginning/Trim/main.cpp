#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <cctype>
#include <iostream>

std::string TrimLeft(std::string s)
{
    s.erase(s.begin(),
        std::find_if_not(s.begin(),s.end(), isspace));
    return s;
}

std::string TrimRight(std::string s)
{
    s.erase(std::find_if_not(s.rbegin(),s.rend(), isspace).base(), 
        s.end());
    return s;
}

std::string Trim(std::string s)
{
    return TrimLeft(TrimRight(std::move(s)));
}

int main()
{
    std::cout<<Trim("\n\t    hello    world    ")<<std::endl;
}