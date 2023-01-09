#include <iostream>
#include "AnyType.h"


int main(int argc, char* argv[]) {

	try {
		AnyType any;
		AnyType anyType = any;

		any = 532;
		int storedValue = any.ToInt();
		std::cout << storedValue << std::endl;

		anyType = 3.14;
		double storedValue1 = anyType.ToDouble();
		std::cout << storedValue1 << std::endl;
	}
	catch (AnyTypeException& ex) {
		std::cout << ex.reason() << std::endl;
	}

	return 0;
}
