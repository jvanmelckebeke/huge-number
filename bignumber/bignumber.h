//
// Created by Jari on 07/01/2022.
//

#ifndef RANDOM_PRIMES_BIGNUMBER_H
#define RANDOM_PRIMES_BIGNUMBER_H

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

class BigNumber;

typedef struct {
    BigNumber *result;
    BigNumber *remainder;
} DivisionResult;


BigNumber pow(const BigNumber &base, const BigNumber &exponent);

BigNumber powMod(const BigNumber &a, const BigNumber &b, const BigNumber &modulo);

class BigNumber {
    explicit operator std::string() const;

    friend ostream &operator<<(ostream &os, const BigNumber &number);

private:
    unit value;
    Sign sign;
    BigNumber *next;

    BigNumber &addRang(unit amount);

    BigNumber &addToRang(int rang, sll amount);

    BigNumber &removeRang(unit amount);

    [[nodiscard]] DivisionResult divide(const BigNumber &b) const;


public:

    explicit BigNumber(const string &numberString);

    explicit BigNumber(sll number);

    BigNumber();

    ~BigNumber();

    BigNumber(const BigNumber &copy) ;


    BigNumber operator+(const BigNumber &b) const;

    BigNumber operator+(sll number) const;


    BigNumber &operator+=(const BigNumber &b);

    BigNumber &operator+=(sll number);


    BigNumber operator-(const BigNumber &b) const;

    BigNumber operator-(sll num) const;


    BigNumber &operator-=(const BigNumber &b);

    BigNumber &operator-=(sll number);

    BigNumber operator*(sll number) const;

    BigNumber operator*(const BigNumber &other) const;


    BigNumber &operator*=(const BigNumber &b);

    BigNumber &operator*=(sll number);


    BigNumber operator/(const BigNumber &b) const;

    BigNumber operator/(sll number) const;

    BigNumber &operator/=(const BigNumber &b);

    BigNumber &operator/=(sll number);

    BigNumber operator%(const BigNumber &b) const;

    BigNumber operator%(sll number) const;

    BigNumber &operator%=(const BigNumber &b);

    BigNumber &operator%=(sll number);

    //misc
    void setFrom(const BigNumber &other);

    BigNumber negate() const;

    BigNumber copy() const;

    sll numValue() const;

    BigNumber abs() const;

    void setSign(Sign nSign);

    Sign getSign() const;

    int getUnits(int current = 0) const;

    //equality
    bool operator==(sll number) const;

    bool operator==(const BigNumber &rhs) const;

    bool operator!=(sll number) const;

    bool operator!=(const BigNumber &rhs) const;


    //compare
    bool operator<(sll number) const;

    bool operator<(const BigNumber &rhs) const;

    bool operator>(const BigNumber &rhs) const;

    bool operator>(sll number) const;

    bool operator<=(const BigNumber &rhs) const;

    bool operator<=(sll number) const;

    bool operator>=(const BigNumber &rhs) const;

    bool operator>=(sll number) const;
};


#endif //RANDOM_PRIMES_BIGNUMBER_H
