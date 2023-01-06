// by Klepatskyi Oleh 

#include "AnyType.h"
#include "AnyTypeException.h"
#include <iostream>

using namespace std;

int main()
{
	AnyType any = 65;
	cout << any.toChar() << endl << any.toInt() << endl;
	try {
		any.getChar();
	}
	catch (const std::runtime_error& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}