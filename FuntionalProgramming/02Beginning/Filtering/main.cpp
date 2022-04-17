#include <iostream>
#include <vector>
#include <algorithm>

enum class EGender
{
    EG_Male,
    EG_Female
};

struct Person
{
std::string m_name;
EGender m_sexual;
};

bool IsFemale(const Person& p)
{
    return p.m_sexual == EGender::EG_Female;
}

std::string GetName(const Person& p)
{
    return p.m_name;
}

std::vector<Person> Filter(std::vector<Person>& people)
{
    std::vector<Person> females;

    std::copy_if(people.cbegin(), people.cend(),
        std::back_inserter(females),
        IsFemale);
    
    return std::move(females);
}

std::vector<std::string> Names(std::vector<Person> people)
{
    std::vector<std::string> names(people.size());
    std::transform(people.cbegin(), people.cend(), names.begin(), GetName);

    return names;
}

int main()
{
    std::vector<Person> people  {{"Peter",   EGender::EG_Male},
                                {"Jane",    EGender::EG_Female},
                                {"Tom",     EGender::EG_Male},
                                {"Martha",  EGender::EG_Female},
                                {"David",   EGender::EG_Male},
                                {"Rose",    EGender::EG_Female}};

    for(auto name : Names(Filter(people)))
    {
        std::cout<<name<<std::endl;
    }
}