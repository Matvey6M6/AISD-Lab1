#include "Mnogochlen.hpp"

Node *Mnogochlen::GetHead() const
{
    return Head;
}

double Mnogochlen::CountValue(double x)
{
    Node *Pointer = GetHead();
    double Ans = 0;
    for (int i = 0; i < GetOrderOfMnogochlen() + 1; i++)
    {
        Ans += Pointer->Value * pow(x, Pointer->MyOrder);
        Pointer = Pointer->Next;
    }
    return Ans;
}

void Mnogochlen::Normalize()
{
    Node *Pointer = GetHead();
    double Devider = Pointer->Value;
    for (int i = 0; i < GetOrderOfMnogochlen() + 1; i++)
    {
        Pointer->Value = Pointer->Value / Devider;
        Pointer = Pointer->Next;
    }
}

int Mnogochlen::GetOrderOfMnogochlen() const
{
    return OrderOfMnogochlen;
}

Mnogochlen::Mnogochlen(int Order)
{
    if (Order >= 0)
    {
        OrderOfMnogochlen = Order;
        Head = nullptr;
    }
    else
    {
        throw RangeError("Incorrect \"Order\" for polynomianl");
    }
}

void Mnogochlen::Set(int Order, double Coef)
{
    if (Coef == 0)
    {
        cout << "Only non-zero coefs are available" << endl;
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
    for (int i = 0; i < GetOrderOfMnogochlen() + 1; i++)
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

int Mnogochlen::GetRoots(double *x)
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
        x[1] = q * cos((t + M_2PI) / 3.) - a;
        x[2] = q * cos((t - M_2PI) / 3.) - a;
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
}

double Mnogochlen::operator[](int Order)
{
    if (Order < 0 || Order > OrderOfMnogochlen)
    {
        throw RangeError("Incorrect \"Order\", value can't be found\n");
    }

    Node *Pointer = GetHead();

    for (int i = 0; i <= GetOrderOfMnogochlen(); i++)
    {
        if (Pointer->MyOrder == Order)
            return Pointer->Value;
        Pointer = Pointer->Next;
    }
    throw RangeError("Order has no coef\n");
}

Mnogochlen Mnogochlen::operator+(const Mnogochlen &other)
{
    int Length = 0;
    int Maximum = 0;
    this->GetOrderOfMnogochlen() > other.GetOrderOfMnogochlen() ? Length = other.GetOrderOfMnogochlen() : Length = this->GetOrderOfMnogochlen();

    this->GetOrderOfMnogochlen() < other.GetOrderOfMnogochlen() ? Maximum = other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Length);

    Node *PointerA = this->GetHead();
    Node *PointerB = other.GetHead();

    for (int i = 0; i < Length + 1; i++)
    {
        for (int j = 0; j <= Maximum + 1; j++)
        {
            if (PointerA->MyOrder == PointerB->MyOrder)
            {
                Result.Set(PointerA->MyOrder, (PointerA->Value + PointerB->Value));
                break;
            }
            PointerB = PointerB->Next;
        }
        PointerB = other.GetHead();
        PointerA = PointerA->Next;
    }
    return Result;
}

Mnogochlen Mnogochlen::operator-(const Mnogochlen &other)
{
    int Length = 0;
    int Maximum = 0;
    this->GetOrderOfMnogochlen() > other.GetOrderOfMnogochlen() ? Length = other.GetOrderOfMnogochlen() : Length = this->GetOrderOfMnogochlen();

    this->GetOrderOfMnogochlen() < other.GetOrderOfMnogochlen() ? Maximum = other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Length);

    Node *PointerA = this->GetHead();
    Node *PointerB = other.GetHead();

    for (int i = 0; i < Length + 1; i++)
    {
        for (int j = 0; j <= Maximum + 1; j++)
        {
            if (PointerA->MyOrder == PointerB->MyOrder)
            {
                Result.Set(PointerA->MyOrder, (PointerA->Value - PointerB->Value));
                break;
            }
            PointerB = PointerB->Next;
        }
        PointerB = other.GetHead();
        PointerA = PointerA->Next;
    }
    return Result;
}

Mnogochlen Mnogochlen::operator*(double Val)
{
    Node *Pointer = GetHead();
    Mnogochlen Result(Pointer->MyOrder);

    for (int i = 0; i <= GetOrderOfMnogochlen(); i++)
    {
        Result.Set(Pointer->MyOrder, Pointer->Value * Val);
        Pointer = Pointer->Next;
    }
    return Result;
}
