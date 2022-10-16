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