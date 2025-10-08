// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.GetMaxPower())
{
    MaxPower = s.MaxPower;
    for (int i = 0; i < MaxPower; i++) {
        if (s.BitField.GetBit(i)) BitField.SetBit(i);
    }
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
    MaxPower = bf.GetLength();
    for (int i = 0; i < MaxPower; i++) {
        if (bf.GetBit(i)) BitField.SetBit(i);
    }
}

TSet::operator TBitField()
{
    TBitField temp(MaxPower);
    for (int i = 0; i < MaxPower; i++) {
        if (BitField.GetBit(i)) temp.SetBit(i);
    }
    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return BitField.GetLength();
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField==s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField!=s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet temp(max(MaxPower, s.MaxPower));
    temp.BitField = BitField | s.BitField;
    return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < MaxPower) {
        TSet temp(MaxPower);
        temp.BitField | BitField;
        temp.InsElem(Elem);
        return temp;
    }
    else { throw new exception; }
    //TSet temp(Elem + 1);
    //temp.BitField | BitField;
    //temp.InsElem(Elem);
    //return temp;
    
    
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet temp(MaxPower);
    temp.BitField | BitField;
    if (Elem < MaxPower) DelElem(Elem);
    return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet temp(max(MaxPower, s.MaxPower));
    temp.BitField = BitField & s.BitField;
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(MaxPower);
    temp.BitField = ~BitField;
    return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    std::cin >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    std::cout << s.BitField;
    return ostr;
}
