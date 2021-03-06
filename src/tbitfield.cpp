// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw "Error";
	BitLen = len;
	MemLen = (len  - 1) / (sizeof(TELEM) * 8)+1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i<MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i<MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) *8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n<0) throw "Error";
	if (n>BitLen) throw "Error";
	pMem[GetMemIndex(n)]|= GetMemMask(n);
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	
	if (n < 0) throw "Error";
	if (n > BitLen) throw "Error";
	pMem[GetMemIndex(n)] &= ~GetMemMask(n); 

}

int TBitField::GetBit(const int n) const // получить значение бита
{
	
	if (n < 0) throw "Error";
	if (n > BitLen) throw "Error";
	return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	   
	   delete pMem; 
	   MemLen = bf.MemLen;
	   pMem = new TELEM[MemLen];
	   BitLen = bf.BitLen;
	   for (int i = 0; i<bf.MemLen; i++) 
		    pMem[i] = bf.pMem[i]; 
	   return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	
	if (BitLen != bf.BitLen) return 0; else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return 0;
	
	return 1;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	
	if (*this == bf) return 0;		
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen; 
	if (len < bf.BitLen)  
		len = bf.BitLen;
	TBitField temp(len); 
	for (int i = 0; i < MemLen; i++) 
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) 
		temp.pMem[i] |= bf.pMem[i]; 
	return temp; 
	
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen; 
	if (len > bf.BitLen)  
		len = bf.BitLen;
	TBitField temp(len); 
	for (int i = 0; i < MemLen; i++) 
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < len; i++)
		temp.pMem[i] &= bf.pMem[i]; 
	return temp; 
	
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < MemLen-1; i++)
		tmp.pMem[i] = ~tmp.pMem[i];
	for (int i = sizeof(TELEM) * 8 * (MemLen - 1); i < BitLen; i++)
	{
		if ((tmp).GetBit(i) == 1) 
			tmp.ClrBit(i); 
		else
			tmp.SetBit(i); 
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char c; 
	int i = 0;
	istr >> c; 
	while ((c == '1') || (c == '0'))
	{
		if (c == '1')
		{
			bf.SetBit(i); 
		}
		if (c == '0')
		{
			bf.ClrBit(i); 
		}
		i++;
		istr >> c; 
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << " Length of BitField=" << bf.BitLen << endl; 
	for (int i = 0; i < bf.BitLen; i++) 
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}
