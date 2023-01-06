// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_ANYTYPE_EXCEPTION_
#define _KLEPATSKYI_ANYTYPE_EXCEPTION_
#include <stdexcept>

class AnyTypeException : public std::runtime_error {
public:
	AnyTypeException(const char* msg) : std::runtime_error(msg) {}
};

class StoredTypeMismatchException : public AnyTypeException {
public:
	StoredTypeMismatchException() : AnyTypeException("Type mismatch occurred when trying to get value from AnyType.") {}
};

class EmptyValueException : public AnyTypeException {
public:
	EmptyValueException() : AnyTypeException("No value present in AnyType") {}
};

class TypeConversionException : public AnyTypeException {
public:
	TypeConversionException(const char* T1, const char* T2) : AnyTypeException(getMessage(T1, T2).c_str()) {}
private:
	static std::string getMessage(const char* T1, const char* T2)
	{
		return std::string("Could not convert ")
			+ T1
			+ " to "
			+ T2
			+ ": loss of information/precision occurred.";
	}
};

#endif // _KLEPATSKYI_ANYTYPE_EXCEPTION_
