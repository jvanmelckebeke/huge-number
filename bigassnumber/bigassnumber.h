//
// Created by Jari on 07/01/2022.
//

#ifndef RANDOM_PRIMES_BIGASSNUMBER_H
#define RANDOM_PRIMES_BIGASSNUMBER_H

#include <ostream>

#define GETSIGN(X) (((X) >= 0) ? positive : negative)
#define ABS(X) (X)>= 0 ? (X) : (-(X))

#define MAX_UNIT 10


using namespace std;

typedef long long int sll;
typedef unsigned char unit;

enum Sign {
    none = 0, positive = 1, negative = -1
};

class BigAssNumber;

typedef struct {
    BigAssNumber *result;
    BigAssNumber *remainder;
} DivisionResult;


BigAssNumber pow(const BigAssNumber &base, const BigAssNumber &exponent);

BigAssNumber powMod(const BigAssNumber &a, const BigAssNumber &b, const BigAssNumber &modulo);

class BigAssNumber {
    explicit operator std::string() const;

    friend ostream &operator<<(ostream &os, const BigAssNumber &number);

private:
    unit value;
    Sign sign;
    BigAssNumber *next;

    BigAssNumber &addRang(unit amount);

    BigAssNumber &addToRang(int rang, sll amount);

    BigAssNumber &removeRang(unit amount);

    [[nodiscard]] DivisionResult divide(const BigAssNumber &b) const;


public:

    explicit BigAssNumber(const string &numberString);

    explicit BigAssNumber(sll number);

    BigAssNumber();

    ~BigAssNumber();

    BigAssNumber(const BigAssNumber &copy) ;


    BigAssNumber operator+(const BigAssNumber &b) const;

    BigAssNumber operator+(sll number) const;


    BigAssNumber &operator+=(const BigAssNumber &b);

    BigAssNumber &operator+=(sll number);


    BigAssNumber operator-(const BigAssNumber &b) const;

    BigAssNumber operator-(sll num) const;


    BigAssNumber &operator-=(const BigAssNumber &b);

    BigAssNumber &operator-=(sll number);

    BigAssNumber operator*(sll number) const;

    BigAssNumber operator*(const BigAssNumber &other) const;


    BigAssNumber &operator*=(const BigAssNumber &b);

    BigAssNumber &operator*=(sll number);


    BigAssNumber operator/(const BigAssNumber &b) const;

    BigAssNumber operator/(sll number) const;

    BigAssNumber &operator/=(const BigAssNumber &b);

    BigAssNumber &operator/=(sll number);

    BigAssNumber operator%(const BigAssNumber &b) const;

    BigAssNumber operator%(sll number) const;

    BigAssNumber &operator%=(const BigAssNumber &b);

    BigAssNumber &operator%=(sll number);

    //misc
    void setFrom(const BigAssNumber &other);

    BigAssNumber negate() const;

    BigAssNumber copy() const;

    sll numValue() const;

    BigAssNumber abs() const;

    void setSign(Sign nSign);

    Sign getSign() const;

    int getUnits(int current = 0) const;

    //equality
    bool operator==(sll number) const;

    bool operator==(const BigAssNumber &rhs) const;

    bool operator!=(sll number) const;

    bool operator!=(const BigAssNumber &rhs) const;


    //compare
    bool operator<(sll number) const;

    bool operator<(const BigAssNumber &rhs) const;

    bool operator>(const BigAssNumber &rhs) const;

    bool operator>(sll number) const;

    bool operator<=(const BigAssNumber &rhs) const;

    bool operator<=(sll number) const;

    bool operator>=(const BigAssNumber &rhs) const;

    bool operator>=(sll number) const;
};


#endif //RANDOM_PRIMES_BIGASSNUMBER_H
