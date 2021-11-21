#include <gtest/gtest.h>
#include <iostream>

class EigenBase {};

std::ostream &operator<<(std::ostream &o, const EigenBase &r) {
    o << "operator<< EigenBase called";
    return o;
}

template <typename T>
void print_to(const T &t, std::ostream *o) {
    *o << "Google Print To Called";
}

class EigenSub : public EigenBase {};

template <typename T>
struct StreamBase {
    typedef T value_type;

    // friend function is inline and static
    friend std::ostream &operator<<(std::ostream &o, const value_type &r) {
        o << "operator<< from CRTP called";
        return o;
    }

    friend void print_to(const value_type &t, std::ostream *o) {
        *o << "print_to from CRTP called";

    }
};

// this is were the magic appears, because the oeprators are actually
// defined with signatures matching the MyEigenSub class.
class MyEigenSub : public EigenSub, public StreamBase<MyEigenSub> {
};

TEST(EigenBasePrint, t1) {
    EigenBase e;
    std::cout << e << std::endl; // works
}

TEST(EigenBasePrint, t2) {
    EigenBase e;
    print_to(e, &std::cout); // works
}

TEST(EigenSubPrint, t3) {
    EigenSub e;
    std::cout << e << std::endl; // works
}

TEST(EigenCRTPPrint, t4) {
    MyEigenSub e;
    std::cout << e << std::endl; // operator<< from CRTP called
}

TEST(EigenCRTPPrint, t5) {
    MyEigenSub e;
    print_to(e, &std::cout); // prints print_to from CRTP called
}
