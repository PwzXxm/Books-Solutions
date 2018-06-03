#ifndef ex7_15_h
#define ex7_15_h

#include <string>
#include <iostream>

struct Person;
std::istream &read(std::istream &, Person &);

struct Person {
    Person() = default;
    Person(std::string n): name(n) {}
    Person(std::string n, std::string addr): name(n), address(addr) {}
    Person(std::istream &is) { read(is, *this); }

    std::string name;
    std::string address;


    std::string const& get_name() const { return name; }
    std::string const& get_addr() const { return address; }

};

std::istream &read(std::istream &is, Person &p) {
    return is >> p.name >> p.address;
}

std::ostream &print(std::ostream &os, const Person &p) {
    return os << p.name << p.address;
}

#endif
