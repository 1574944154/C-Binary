#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

#define BIT 8

class Binary
{
public:
	Binary(int p[])
	{
		copy(binary, p);
		sign = binary[1];
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
		return Binary(tArray);
	}
	Binary convertBuMa()
	{
		if (sign == 0)
			return Binary(binary);
		else if (sign == 1 && absDecimalNum == pow(2, 7))
			return Binary(new int[9]{ 0,1,0,0,0,0,0,0,0 });
		return Binary(add(convertFanMa().getBinary(), new int[9]{ 0,0,0,0,0,0,0,0,1 }));
	}
	Binary convertFanMa()
	{
		if (sign == 0)
			return Binary(binary);

		int tArray[9];
		for (int i = 8; i > 1; i--)
			tArray[i] = 1 - binary[i];
		tArray[1] = binary[1];
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
		Binary b1 = Binary(pt);
		b1.display();
		delete[] pt;
		return b1.convertBuMa();
	}
	Binary operator-(Binary b)
	{
		int *pt = sub(convertBuMa().getBinary(), b.convertBuMa().getBinary());
		Binary b1 = Binary(pt);
		b1.display();
		delete[] pt;
		return b1.convertBuMa();
		//return *this + Binary(-b.getDecimal());
		//return Binary(1) + Binary(2);
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
	int *add(int x[], int y[])
	{
		int carry = 0;
		int *tArray = new int[9];
		for (int i = 8; i > 0; i--)
		{
			tArray[i] = x[i] + y[i] + carry;
			carry = tArray[i] / 2;
			tArray[i] = tArray[i] % 2;
		}
		tArray[0] = carry;
		return tArray;
	}
	int *sub(int x[], int y[])
	{
		int borrow = 0;
		int *tArray = new int[9];
		for (int i = 8; i > 0; i--)
		{
			tArray[i] = x[i] - y[i] + borrow;
			borrow = tArray[i] < 0 ? tArray[i] : 0;
			tArray[i] = abs(tArray[i] % 2);
			//borrow = tArray[i] < 0 ? -tArray[i] : 0;
			//tArray[i] = tArray[i] >= 0 ? tArray[i] : -tArray[i];
		}
		tArray[0] = abs(borrow%2);
		return tArray;
	}
	void init(int x)
	{
		binary[1] = sign;
		binary[0] = 0;
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