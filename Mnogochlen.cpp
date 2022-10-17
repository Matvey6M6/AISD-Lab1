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
