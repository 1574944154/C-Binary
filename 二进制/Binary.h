#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

extern int SpecialArray[9];

class Binary
{
public:
	Binary(){}
	Binary(int p[])
	{
		copy(binary, p);
		sign = binary[0];
		absDecimalNum = binaryToAbsDecimal(binary);
	}
	Binary(int decimalNum)
	{
		sign = decimalNum > 0 ? 0 : 1;
		absDecimalNum = abs(decimalNum);
		init(absDecimalNum);
	}
	Binary(int sign, int x)
	{
		this->sign = sign;
		absDecimalNum = abs(x);
		init(absDecimalNum);
	}
	int getDecimal()
	{
		return sign == 1 ? -absDecimalNum : absDecimalNum;
	}
	int *getBinary()
	{
		return binary;
	}
	void display()
	{
		for (int i = 0; i < 9; i++)
			cout << binary[i];
		cout << endl;
	}
	Binary convertYiMa()
	{
		int tArray[9];
		copy(tArray, convertBuMa().getBinary());
		tArray[1] = 1 - sign;
		tArray[0] = 1 - sign;
		return Binary(tArray);
	}
	Binary convertBuMa()
	{
		if (sign == 0)
			return Binary(binary);
		else if (sign == 1 && absDecimalNum == pow(2, 7))
		{
			return Binary(SpecialArray);
		}
		else if (arrayEqual(binary, SpecialArray))
			return Binary(-pow(2, 7));
		int tArray[9] = { 0,0,0,0,0,0,0,0,1 };
		return Binary(add(convertFanMa().getBinary(), tArray));
	}
	Binary convertFanMa()
	{
		if (sign == 0)
			return Binary(binary);

		int tArray[9];
		for (int i = 8; i > 1; i--)
			tArray[i] = 1 - binary[i];
		tArray[1] = binary[0];
		tArray[0] = binary[0];
		return Binary(tArray);
	}
	Binary convertYuanMa()
	{
		return Binary(binary);
	}
	Binary operator+(Binary b)
	{
		int *pt = add(convertBuMa().getBinary(), b.convertBuMa().getBinary());
		if (*pt != *(pt + 1))
		{
			string error = *pt > 0 ? string("负溢") : string("正溢");
			delete[] pt;
			throw error;
		}
		Binary b1 = Binary(pt);
		delete[] pt;
		return b1.convertBuMa();
	}
	Binary operator-(Binary b)
	{
		int *pt = sub(convertBuMa().getBinary(), b.convertBuMa().getBinary());
		if (*pt != *(pt + 1))
		{
			string error = *pt > 0 ? string("负溢") : string("正溢");
			delete[] pt;
			throw error;
		}
		Binary b1 = Binary(pt);
		delete[] pt;
		return b1.convertBuMa();
	}
	string toBinaryString()
	{
		char tArray[9];
		for (int i = 0; i < 8; i++)
			tArray[i] = binary[i] + 48;
		tArray[8] = '\0';
		return tArray;
	}
private:
	int binaryToAbsDecimal(int *p)
	{
		int sum = 0;
		for (int i = 2; i <= 8; i++)
			sum += (p[i] * pow(2, 8 - i));
		return sum;
	}
	bool arrayEqual(int x[], int y[])
	{
		for (int i = 0; i < 9; i++)
			if (x[i] != y[i])
				return false;
		return true;
	}
	int *add(int x[], int y[])
	{
		int carry = 0;
		int *tArray = new int[9];
		for (int i = 8; i >= 0; i--)
		{
			tArray[i] = x[i] + y[i] + carry;
			carry = tArray[i] / 2;
			tArray[i] = tArray[i] % 2;
		}
		return tArray;
	}
	int *sub(int x[], int y[])
	{
		int borrow = 0;
		int *tArray = new int[9];
		for (int i = 8; i >= 0; i--)
		{
			tArray[i] = x[i] - y[i] + borrow;
			borrow = tArray[i] < 0 ? -1 : 0;
			tArray[i] = tArray[i] < 0 ? abs(tArray[i] % 2) : tArray[i];
		}
		return tArray;
	}
	void init(int x)
	{
		binary[1] = sign;
		binary[0] = sign;
		for (int i = 8; i > 1; i--)
		{
			binary[i] = x % 2;
			x = x / 2;
		}
	}
	void copy(int newArray[], int oldArray[])
	{
		memcpy(newArray, oldArray, 9 * sizeof(int));
	}
	int binary[9];
	int absDecimalNum;
	int sign;  //0为正 1为负
};