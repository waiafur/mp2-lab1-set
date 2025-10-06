// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
// int  BitLen;  длина битового поля - макс. к-во битов
// TELEM* pMem; память для представления битового поля
// int  MemLen; к-во эл-тов Мем для представления бит.поля
TBitField::TBitField(int len)
{
    if (len <= 0) throw new exception;
    MemLen = ((len+31)/32);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = TELEM(0);
    }
    BitLen = len;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    BitLen = bf.BitLen;
}

TBitField::~TBitField()
{
    delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return pMem[n >> sizeof(TELEM)] & (1 << ((1 << 5) - 1) & n);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return pMem[n/32];
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) throw new exception("negative input");
    if (n > BitLen) throw new exception("out of tange input");
    pMem[n /32] = pMem[n/32] | (1 << (n % 32));
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) throw new exception("negative input");
    if (n > BitLen) throw new exception("out of tange input");
    pMem[n /32] = pMem[n/32] & (~0 - (1 << (n % 32)));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) throw new exception("negative input");
    if (n > BitLen) throw new exception("out of tange input");
    return (pMem[n /32] >> (n % 32)) & 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    MemLen = bf.MemLen;
    delete pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    BitLen = bf.BitLen;
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (MemLen != bf.MemLen) return 0;
    for (int i = 0; i < MemLen; i++) if (pMem[i] != bf.pMem[i]) return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (MemLen != bf.MemLen) return 1;
    for (int i = 0; i < MemLen; i++) if (pMem[i] != bf.pMem[i]) return 1;
    return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField temp(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++) temp.pMem[i] = pMem[i] | bf.pMem[i];
    if (MemLen < bf.MemLen) for (int i = MemLen; i < bf.MemLen; i++) temp.pMem[i] = bf.pMem[i];
    else{ for (int i = bf.MemLen; i < MemLen; i++) temp.pMem[i] = pMem[i]; }
    return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField temp(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++) temp.pMem[i] = pMem[i] & bf.pMem[i];
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(BitLen);
    for (int i = 0; i < BitLen; i++) {
        if (GetBit(i) != 1) temp.SetBit(i);
    }
    return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
