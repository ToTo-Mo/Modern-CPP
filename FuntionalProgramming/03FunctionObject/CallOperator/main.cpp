#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

class OrderThan
{
public:
    OrderThan(int limit) : m_limit(limit){}

    template<typename T>
    bool operator()(T&& object) const
    {
        return std::forward<T>(object).age() > m_limit;
    }

private:
    int m_limit;
};

class Age
{
    virtual int age() const = 0;
};

class Car : Age
{
public:
    Car(int productYear) : m_productYear(productYear){}
    virtual int age() const override {return m_productYear;}
private:
    int m_productYear;
};

class Person : Age
{
public:
    Person(int age) : m_age(age){}
    virtual int age() const override {return m_age;}
private:
    int m_age;
};

class Animal : Age
{
public:
    Animal(int age) : m_age(age){}
    virtual int age() const override {return m_age;}
private:
    int m_age;
};

int main()
{
    OrderThan predicate(5);

    std::vector<Animal> animals{5,10,15};
    std::vector<Person> people{5,10,15};
    std::vector<Car> cars{2,8,10};

    std::cout<<std::count_if(animals.cbegin(), animals.cend(), predicate)<<std::endl;
    std::cout<<std::count_if(people.cbegin(), people.cend(), predicate)<<std::endl;
    std::cout<<std::count_if(cars.cbegin(), cars.cend(), predicate)<<std::endl;
}