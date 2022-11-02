#include "Mnogochlen.hpp"

Node *Mnogochlen::GetHead() const
{
    return Head;
}

long long Mnogochlen::GetOrderOfMnogochlen() const
{
    return OrderOfMnogochlen;
}

Mnogochlen::Mnogochlen(long long Order)
{
    if (Order >= 0)
    {
        OrderOfMnogochlen = Order;
        Head = nullptr;
    }
    else
    {
        delete this;
        throw RangeError("Incorrect \"Order\" for polynomianl");
    }
}

Mnogochlen::~Mnogochlen()
{
    while (Head != NULL)
    {
        Node *tmp = Head;
        Head = Head->Next;
        delete tmp;
    }
}

void Mnogochlen::Set(long long Order, double Coef)
{
    if (Coef == 0)
    {
        cout << "\n!!!Only non-zero coefs will be saved!!!" << endl;
        if (Order == GetOrderOfMnogochlen())
        {
            OrderOfMnogochlen -= 1;
            cout << "Order -= 1" << endl;
        }
        return;
    }
    if (Order < 0 || Order > GetOrderOfMnogochlen())
    {
        throw RangeError("Incorrect \"Order\", value can't be initialized\n");
    }
    if (Head == nullptr)
    {
        Node *newbie = new Node;
        newbie->MyOrder = Order;
        newbie->Value = Coef;
        newbie->Next = nullptr;
        Head = newbie;
        return;
    }

    Node *PointerA = GetHead();
    Node *PointerB = PointerA;
    for (long long i = 0; i < GetOrderOfMnogochlen() + 1 && PointerA; i++)
    {
        if (PointerA->Next == nullptr && Order < PointerA->MyOrder) //последний эдемент
        {
            Node *newbie = new Node;
            newbie->MyOrder = Order;
            newbie->Value = Coef;
            newbie->Next = nullptr;

            PointerA->Next = newbie;
            return;
        }
        else if (PointerA->MyOrder == Order) // просто изменить значение
        {
            PointerA->Value = Coef;
            return;
        }
        else if (PointerA->MyOrder < Order) // добавить между
        {
            Node *newbie = new Node;
            newbie->MyOrder = Order;
            newbie->Value = Coef;

            newbie->Next = PointerA;
            PointerB->Next = newbie;
            return;
        }
        PointerB = PointerA;
        PointerA = PointerA->Next;
    }
}

double Mnogochlen::operator[](long long Order) const
{
    Node *Pointer = GetHead();

    while (Pointer)
    {
        if (Pointer->MyOrder == Order)
            return Pointer->Value;
        Pointer = Pointer->Next;
    }
    return 0;
}

Mnogochlen Mnogochlen::operator+(const Mnogochlen &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfMnogochlen() < Other.GetOrderOfMnogochlen() ? Maximum = Other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Maximum);

    int CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) + (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

Mnogochlen Mnogochlen::operator-(const Mnogochlen &Other) const
{
    int Maximum = 0;

    this->GetOrderOfMnogochlen() < Other.GetOrderOfMnogochlen() ? Maximum = Other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Maximum);

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) - (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

Mnogochlen Mnogochlen::operator*(double Val) const
{
    Node *Pointer = GetHead();
    Mnogochlen Result(Pointer->MyOrder);

    for (long long i = 0; i <= GetOrderOfMnogochlen(); i++)
    {
        Result.Set(Pointer->MyOrder, Pointer->Value * Val);
        Pointer = Pointer->Next;
    }
    return Result;
}

double Mnogochlen::CountValue(double x) const
{
    Node *Pointer = GetHead();
    double Ans = 0;
    for (long long i = 0; i < GetOrderOfMnogochlen() + 1 && Pointer; i++)
    {
        Ans += Pointer->Value * pow(x, Pointer->MyOrder);
        Pointer = Pointer->Next;
    }
    return Ans;
}
/*
void Mnogochlen::GetRoots() const
{
    Mnogochlen *Newbie = &Normalize();
    double a = (*Newbie)[3];
    double b = (*Newbie)[2];
    double c = (*Newbie)[1];
    double d = (*Newbie)[0];

    long double p = ((3. * a * c - b * b) / (3. * a * a));
    long double q = ((2. * b * b - 9. * a * b * c + 27. * a * a * d));
    long double s = (((q * q) / 4.) + (p * p * p) / 27.);

    long double x1, x2, x3, x2i, x3i;

    long double f;

    if (q < 0)
    {
        f = (atan(pow(-s, 0.5) / (-q / 2)));
    }
    else if (q > 0)
    {
        f = (atan(pow(-s, 0.5) / (-q / 2)) + M_PI);
    }
    else
    {
        f = (M_PI / 2);
    }

    if (s < 0)
    {
        x1 = (2. * pow((-p / 3.), 0.5) * cos(f / 3.) - b / 3. * a);
        x2 = (2. * pow((-p / 3.), 0.5) * cos(f / 3. + (2. * M_PI) / 3.) - b / 3. * a);
        x3 = (2. * pow((-p / 3.), 0.5) * cos(f / 3. + (2. * M_PI) / 3.) - b / 3. * a);
    }
    else if (s > 0)
    {
        x1 = (pow(-q / 2. + pow(s, 0.5), 1. / 3.) + pow(-q / 2. - (pow(s, 0.5)), 1. / 3.) - b / (3. * a));
        x2 = (-0.5 * (pow(-q / 2. + pow(s, 0.5), 1. / 3.) + pow(-q / 2. - (pow(s, 0.5)), 1. / 3.) - b / (3. * a)));
        x2i = ((pow(3., 0.5) / 2.) * (pow(-q / 2. + (pow(s, 0.5)), 1. / 3.) - pow(-q / 2. - (pow(s, 0.5)), 1. / 3.)));
        x3 = (-0.5 * (pow(-q / 2 + pow(s, 0.5), 1 / 3) + pow(-q / 2 - (pow(s, 0.5)), 1 / 3) - b / (3 * a)));
        x3i = ((pow(3., 0.5) / 2.) * (pow(-q / 2. + (pow(s, 0.5)), 1. / 3.) - pow(-q / 2. - (pow(s, 0.5)), 1. / 3.)));
    }
    else
    {
        x1 = (2. * pow(-q / 2., 1. / 3.) - b / (3. * a));
        x2 = (-1. * pow(-q / 2., 1. / 3.) - b / (3. * a));
        x3 = (-1. * pow(-q / 2., 1. / 3.) - b / (3. * a));
    }

    cout << "x1= " << x1 << endl;

    if (s > 0)
    {
        cout << "x2= " << x2 << "+" << x2i << "i" << endl;
        cout << "x3= " << x3 << "-" << x3i << "i" << endl;
    }
    else
    {
        cout << "x2= " << x2 << endl;
        cout << "x3= " << x3 << endl;
    }
}*/

/*int Mnogochlen::GetRoots(double *x) const
{
    if (GetOrderOfMnogochlen() != 3)
    {
        throw RangeError("Order is not 3");
    }
    Node *Pointer = GetHead();
    if (Pointer->Value != 1)
        Normalize();

    double a = 0;
    double b = 0;
    double c = 0;

    for (int i = 0; i < GetOrderOfMnogochlen() + 1; i++)
    {
        if (Pointer->MyOrder == 2)
            a = Pointer->Value;
        if (Pointer->MyOrder == 1)
            b = Pointer->Value;
        if (Pointer->MyOrder == 0)
            c = Pointer->Value;

        Pointer = Pointer->Next;
    }

    double q, r, r2, q3;
    q = (a * a - 3. * b) / 9.;
    r = (a * (2. * a * a - 9. * b) + 27. * c) / 54.;
    r2 = r * r;
    q3 = q * q * q;
    if (r2 < q3)
    {
        double t = acos(r / sqrt(q3));
        a /= 3.;
        q = -2. * sqrt(q);
        x[0] = q * cos(t / 3.) - a;
        x[1] = q * cos((t + M_2M_M_M_PI) / 3.) - a;
        x[2] = q * cos((t - M_2M_M_M_PI) / 3.) - a;
        return (3);
    }
    else
    {
        double aa, bb;
        if (r <= 0.)
            r = -r;
        aa = -pow(r + sqrt(r2 - q3), 1. / 3.);
        if (aa != 0.)
            bb = q / aa;
        else
            bb = 0.;
        a /= 3.;
        q = aa + bb;
        r = aa - bb;
        x[0] = q - a;
        x[1] = (-0.5) * q - a;
        x[2] = (sqrt(3.) * 0.5) * fabs(r);
        if (x[2] == 0.)
            return (2);
        return (1);
    }
}*/
