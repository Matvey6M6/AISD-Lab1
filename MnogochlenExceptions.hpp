#pragma once
#include <conio.h>
#include <math.h> /* for sqrt(), fabs(), pow(), cos(), acos(). */
#define M_PI (3.141592653589793)
#define M_2PI (2. * M_PI)
#include <iostream>
#include "MnogochlenExceptions.hpp"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <locale.h>
using namespace std;

struct Node
{
    long long MyOrder;
    double Value;
    Node *Next;
};

class Mnogochlen
{
    Node *Head;

    long long OrderOfMnogochlen;

    Mnogochlen Normalize() const;

public:
    Node *GetHead() const;

    long long GetOrderOfMnogochlen() const;

    Mnogochlen(long long Order);

    ~Mnogochlen();

    void Set(long long Order, double Coef);

    double operator[](long long Order) const;

    Mnogochlen operator+(const Mnogochlen &other) const;

    Mnogochlen operator-(const Mnogochlen &other) const;

    Mnogochlen operator*(double Val) const;

    double CountValue(double x) const;

    //void GetRoots() const;

    friend ostream &operator<<(ostream &os, const Mnogochlen &Obj);
};
