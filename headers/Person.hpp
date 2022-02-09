#ifndef __PERSON_HPP__
#define __PERSON_HPP__
#include "IRecord.hpp"

#include <iostream>
using ll = long long;

class Person : public IRecord {
    const int Password;
    int Age;

protected:
    IRecord_OVERRIDE;
    std::string Name;
    std::string fname;
    std::string MobileNumber;
    const ll CNIC;
    int hasvoted;

public:
    static const std::string TableName;
    Person(ll cnic, int pass) : CNIC(cnic), Password(pass) {}
    Person(const std::vector<std::string> &);

    void setName(const std::string &);
    void setAge(int);
    void setMobileNum(const std::string &);
    void setFname(const std::string &);
    void setvoted(int x) {
        hasvoted = x;
        Person::update();
    }

    std::string getName() const noexcept;
    int getAge() const noexcept;
    ll getCNIC() const noexcept;
    std::string getMobileNumber() const noexcept;
    std::string getFname() const noexcept;
    int getPassword() const noexcept;
    int getcitycode() const noexcept;
    int voted() const {
        return hasvoted;
    }

    friend std::ostream &operator<<(std::ostream &out, const Person &p);
    friend std::istream &operator>>(std::istream &in, Person &p);
    bool operator<(const Person &other) const {
        return this->CNIC < other.CNIC;
    }
    bool operator>(const Person &other) const {
        return !(*this < other);
    }
};

#endif // __PERSON_HPP__
