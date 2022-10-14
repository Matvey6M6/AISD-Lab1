#include "Mnogochlen.hpp"
#include <iostream>
using namespace std;

ostream &operator<<(ostream &os, const Mnogochlen &Obj)
{
    if (Obj.GetOrderOfPolynominal() == -1)
    {
        cout << "Polynominal has no coefs" << endl;
    }
    Node *Pointer = Obj.GetHead();
    for (int i = 0; i < Obj.GetOrderOfPolynominal() + 1; i++)
    {
        os << Pointer->Value << "*x^" << Pointer->MyOrder;
        if (i != Obj.GetOrderOfPolynominal())
            os << " + ";
        Pointer = Pointer->Next;
    }
    return os;
}

int main()
{
    Mnogochlen first_obj(2);
    for (int i = 2; i >= 0; i--)
    {
        first_obj.Set(i, (i + 1) * 3);
    }

    Mnogochlen second_obj(4);
    for (int i = 4; i >= 0; i--)
    {
        second_obj.Set(i, ((i + 2) * 3));
    }

    cout << first_obj[0] << endl;

    cout << first_obj << endl;

    cout << second_obj << endl;

    cout << (first_obj * 2) << endl;

    cout << first_obj + second_obj << endl;

    cout << first_obj - second_obj << endl;

    cout << first_obj.CountValue(2.0) << endl;

    Mnogochlen OrderThree(3);

    for (int i = 3; i >= 0; i--)
    {
        OrderThree.Set(i, (i + 1) * 10);
    }

    double *X = new double[2]{0};
    int NumOfRoots = OrderThree.GetRoots(X);

    /*
    Returns: 3 - 3 real roots;
             1 - 1 real root + 2 complex;
             2 - 1 real root + complex roots imaginary part is zero
                 (i.e. 2 real roots).
     */

    switch (NumOfRoots)
    {
    case 1:
        cout << "Root 1: " << X[0] << endl;
        break;
    case 2:
        cout << "Root 1 : " << X[0] << endl;
        cout << "Root 2 : " << X[1] << endl;
        break;
    case 3:
        cout << "Root 1 : " << X[0] << endl;
        cout << "Root 2 : " << X[1] << endl;
        cout << "Root 3 : " << X[2] << endl;
        break;
    default:
        cout << "Roots not found" << endl;
        break;
    }

    return 0;
}