#include "Person.hpp"

using ll = long long;
#include <bits/stdc++.h>

Person::Person(const std::vector<std::string> &values) :
    CNIC(std::stoll(values.at(0))), Password(std::stoi(values.at(3))),
    Name(values.at(1)), fname(values.at(2)), MobileNumber(values.at(4)),
    Age(std::stoi(values.at(5))), hasvoted(std::stoi(values.at(6))) {}

const std::string Person::TableName = "Person";
const std::string &Person::insertColumns() const noexcept {
    static const std::string cols =
        "Cnic , Name , Fname , Password , MobileNumber , Age , hasvoted";
    return cols;
}

std::string Person::insertValues() const noexcept {
    return build(CNIC, Name, fname, Password, MobileNumber, Age, hasvoted);
}

std::string Person::updateValues() const noexcept {
    static const std::vector<std::string> cols = {"hasvoted"};
    return build(cols, hasvoted);
}
std::vector<Condition> Person::updateConditions() const noexcept {
    return {{Condition("Cnic", CNIC)}};
}
std::vector<Condition> Person::removeConditions() const noexcept {
    return {Condition::Impossible};
}

std::string Person::getTable() const noexcept {
    return "Person";
}

void Person::setName(const std::string &name) {
    this->Name = name;
}
std::string Person::getName() const noexcept {
    return Name;
}

void Person::setAge(int age) {
    Expects((age > 0), "Invalid input , Age Cannot be Negative");
    Age = age;
}
int Person::getAge() const noexcept {
    return Age;
}

ll Person::getCNIC() const noexcept {
    return CNIC;
}

int Person::getPassword() const noexcept {
    return Password;
}

void Person::setMobileNum(const std::string &num) {
    Expects(num.length() < 12,
            "Invalid Mobile Number , it must be of 11 digits");
    MobileNumber = num;
}
std::string Person::getMobileNumber() const noexcept {
    return MobileNumber;
}

void Person::setFname(const std::string &f) {
    this->fname = f;
}
std::string Person::getFname() const noexcept {
    return fname;
}

int Person::getcitycode() const noexcept {
    const int codes[5] = {44300, 42100, 45504, 32100, 33100};
    int code = CNIC / 100000000;
    for (int i = 0; i < 5; ++i) {
        if (codes[i] == code) {
            return i;
        }
    }
    // control would never reach this
    return -1;
}

std::ostream &operator<<(std::ostream &out, const Person &p) {
    out << "\nCNIC:" << p.getCNIC();
    out << "\nName:" << p.getName();
    out << "\nPassword:" << p.Password;
    out << "\nFather's Name:" << p.getFname();
    out << "\nPhoneNumber:" << p.getMobileNumber();
    out << "\nAge:" << p.Age;
    return out;
}
std::istream &operator>>(std::istream &in, Person &p) {
    fflush(stdin);
    std::cout << "Enter Name:";
    getline(in, p.Name);
    std::cout << "Enter Age:";
    in >> p.Age;
    std::cout << "Enter Mobile Number:";
    in >> p.MobileNumber;
    return in;
}
