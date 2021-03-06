#ifndef ex7_48_h
#define ex7_48_h

#include <string>
#include <iostream>

struct Sales_data {
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);

public:
    Sales_data(const std::string &s, unsigned n, double p):
                bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(): Sales_data("", 0, 0.0) {}
    Sales_data(const std::string &s): Sales_data(s, 0, 0.0) {}
    Sales_data(std::istream &is);

    std::string isbn() const { return bookNo; };
    unsigned get_units_sold() const { return units_sold; };
    double get_revenue() const { return revenue; };

    inline double avg_price() const;

    Sales_data& combine(const Sales_data&);
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

inline double Sales_data::avg_price() const {
    return units_sold ? (revenue/units_sold) : 0;
}

/*
 * non-member functions
 */
std::istream &read(std::istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue;
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}


/*
 * member functions
 */
Sales_data::Sales_data(std::istream &is) {
    read(is, *this);
}

Sales_data& Sales_data::combine(const Sales_data& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

#endif
