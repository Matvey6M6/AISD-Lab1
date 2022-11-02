#pragma once
#include <iostream>
#include <math.h>
#include "MnogochlenExceptions.hpp"
using namespace std;
#define M_PI (3.141592653589793)
#define M_2PI (2. * M_PI)

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

    Mnogochlen operator+(const Mnogochlen &Other) const;

    Mnogochlen operator-(const Mnogochlen &Other) const;

    Mnogochlen operator*(double Val) const;

    void GetRoots() const;

    double CountValue(double x) const;

    friend ostream &operator<<(ostream &os, const Mnogochlen &Obj);
};
