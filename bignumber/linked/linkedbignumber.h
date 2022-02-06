//
// Created by Jari on 07/01/2022.
//

#ifndef RANDOM_PRIMES_LINKEDBIGNUMBER_H
#define RANDOM_PRIMES_LINKEDBIGNUMBER_H

#include <ostream>
#include "bignumber.h"

#define GETSIGN(X) (((X) >= 0) ? positive : negative)
#define ABS(X) (((X)>= 0) ? (X) : (-(X)))

#define MAX_UNIT 10


using namespace std;

typedef unsigned char unit;


class LinkedBigNumber : public BigNumber<LinkedBigNumber> {
private:
    unit value;
    Sign sign;
    LinkedBigNumber *next;

    LinkedBigNumber &addRang(unit amount);

    LinkedBigNumber &addToRang(int rang, sll amount);

    LinkedBigNumber &removeRang(unit amount);

    [[nodiscard]] DivisionResult<LinkedBigNumber> divide(const LinkedBigNumber &b) const;

public:

#pragma region constructors

    LinkedBigNumber();

    ~LinkedBigNumber();

    explicit LinkedBigNumber(const string &numberString);

    LinkedBigNumber(const LinkedBigNumber &from);

    LinkedBigNumber(sll value);

    template<class T>
    LinkedBigNumber(const BigNumber<T> &from);

#pragma endregion


#pragma region plus

    LinkedBigNumber operator+(const LinkedBigNumber &b) const override;

    LinkedBigNumber &operator+=(const LinkedBigNumber &b) override;


#pragma endregion

#pragma region minus

    LinkedBigNumber operator-(const LinkedBigNumber &b) const override;

    LinkedBigNumber &operator-=(const LinkedBigNumber &b) override;


#pragma endregion

#pragma region product

    LinkedBigNumber operator*(const LinkedBigNumber &b) const override;


    LinkedBigNumber &operator*=(const LinkedBigNumber &b) override;


#pragma endregion

#pragma region division

    LinkedBigNumber operator/(const LinkedBigNumber &b) const override;


    LinkedBigNumber &operator/=(const LinkedBigNumber &b) override;

#pragma endregion

#pragma region modulo

    LinkedBigNumber operator%(const LinkedBigNumber &b) const override;


    LinkedBigNumber &operator%=(const LinkedBigNumber &b) override;


#pragma endregion


    bool operator==(const LinkedBigNumber &rhs) const override;

    bool operator!=(const LinkedBigNumber &rhs) const override;

    bool operator<(const LinkedBigNumber &rhs) const override;


#pragma region misc

    void setFrom(const LinkedBigNumber &other) override;

    LinkedBigNumber copy() const override;

    [[nodiscard]] LinkedBigNumber negate() const override;

    [[nodiscard]] LinkedBigNumber abs() const override;

    [[nodiscard]] sll numValue() const override;

    [[nodiscard]] int getUnits(int current = 0) const;

    [[nodiscard]] string to_string() const override;

    void setSign(Sign nSign) override;

    [[nodiscard]] Sign getSign() const override;

#pragma endregion


};

#endif //RANDOM_PRIMES_LINKEDBIGNUMBER_H
