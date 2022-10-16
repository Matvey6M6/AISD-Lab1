#pragma once
#include <conio.h>
#include <math.h> /* for sqrt(), fabs(), pow(), cos(), acos(). */
#define M_PI (3.141592653589793)
#define M_2PI (2. * M_PI)
#include <iostream>
#include "MnogochlenExceptions.hpp"
using namespace std;

struct Node
{
    int MyOrder;
    double Value;
    Node *Next;
};

class Mnogochlen
{
    Node *Head;

    int OrderOfMnogochlen;

    void Normalize();

public:
    Node *GetHead() const;

    int GetOrderOfMnogochlen() const;

    Mnogochlen(int Order);

    void Set(int Order, double Coef);

    double CountValue(double x);

    friend ostream &operator<<(ostream &os, const Mnogochlen &Obj);
};
