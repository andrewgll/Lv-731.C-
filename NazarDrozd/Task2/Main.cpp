#include <iostream>
#include "AnyType.h"

AnyType func()
{
	AnyType x = 10;
	return x;
}

int main()
{
	AnyType any = 1;
	any = true;
	any = 1.7;

	any = func();

	try
	{
		int storedValue = any.GetValueInt();
		std::cout << storedValue << std::endl;
	}
	catch (ExceptionType& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	try
	{
		double storedValue = any.GetValueDouble();
		std::cout << storedValue << std::endl;
	}
	catch (ExceptionType& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}