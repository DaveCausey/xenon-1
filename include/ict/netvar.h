#pragma once
//-- Copyright 2015 Intrig
//-- see https://github.com/intrig/xenon for license
#include <array>

/** Define a network integer.  */
namespace ict {
template <class T> class netvar {
    public:
    typedef unsigned char * iterator;
    typedef const iterator const_iterator;

    template <typename InputIter> 
    netvar(const char * first) { // presume big-endian to start with
        std::copy(first, first + data.size(), data.begin());
    }

    netvar(T number = 0) {
        auto first = (char *) &number;
        std::reverse_copy(first, first + data.size(), data.begin());
    }

    // Assignment Operators
    netvar &operator=(netvar const number) { 
        std::copy(number.begin(), number.end(), data.begin());
        return *this;
    }

    netvar &operator=(T const number) { 
        auto first = (char *) &number;
        std::reverse_copy(first, first + data.size(), data.begin());
        return *this;
    }

    netvar &operator+=(netvar number) { return *this = value() + number; }
    netvar &operator-=(netvar number) { return *this = value() - number; }
    netvar &operator/=(netvar number) { return *this = value() / number; }
    netvar &operator*=(netvar number) { return *this = value() * number; }


    // Arithmatic Operators
    T operator+(T number) const { return value() + number; }
    T operator-(T number) const { return value() - number; }
    T operator*(T number) const { return value() * number; }
    T operator/(T number) const { return value() / number; }
    T operator<<(T number) const { return value() << number; }
    T operator>>(T number) const { return value() >> number; }
    T operator+(netvar number) const { return value() + number.value(); }
    T operator-(netvar number) const { return value() - number.value(); }
    T operator*(netvar number) const { return value() * number.value(); }
    T operator/(netvar number) const { return value() / number.value(); }
    T operator<<(netvar number) const{ return value() << number.value(); }
    T operator>>(netvar number) const{ return value() >> number.value(); }

    // Comparison operators
    bool operator<(T number) const { return value() < number; }
    bool operator>(T number) const { return value() > number; }
    bool operator==(T number) const { return value() == number; }
    bool operator!=(T number) const { return value() != number; }
    bool operator<(netvar number) const { return value() < number.value(); }
    bool operator>(netvar number) const { return value() > number.value(); }
    bool operator==(netvar number) const { return value() == number.value(); }
    bool operator!=(netvar number) const { return value() != number.value(); }

    /** Automatic cast.  */
    operator T() const { return value(); }

    /** Conversion */
    T value() const {
        T number;
        std::reverse_copy(data.begin(), data.end(), (char *) &number);
        return number;
    }

    /** Conversion */
    void encode(T number) { *this = number; }

    std::array<unsigned char, sizeof(T)> data;
};
} // namespace
