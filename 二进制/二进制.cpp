#include "Binary.h"

int SpecialArray[9] = { 1,1,0,0,0,0,0,0,0 };//-128的反码

int main()
{
	Binary b1, b2, b3, b4;
	int a, b;
	while (true)
	{
		cout << "请输入两个数：";
		cin >> a >> b;
		b1 = Binary(a);
		b2 = Binary(b);
		try
		{ 
			b3 = b1 + b2;
			cout << a << " + " << b << " = " << b3.getDecimal() << endl;
		}
		catch (string s)
		{
			cout << a << "+" << b << "  出错：" << s << endl;
		}

		try
		{
			b4 = b1 - b2;
			cout << a << " - " << b << " = " << b4.getDecimal() << endl;
		}
		catch (string s)
		{
			cout << a << "-" << b << "  出错：" << s << endl;
		}
	}

	system("pause");
    return 0;
}