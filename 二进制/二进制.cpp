#include "stdafx.h"
#include "Binary.h"


int main()
{
	Binary b1 = Binary(0);
	Binary b2 = Binary(-128);

	b1.convertBuMa().display();
	b2.convertBuMa().display();

	Binary b4 = b1 - b2;
	
	//cout << b3.getDecimal() << endl;
	//cout << b4.getDecimal() << endl;
	cout << b4.getDecimal() << endl;


	system("pause");
    return 0;
}