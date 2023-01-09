#pragma once
#include <iostream>
#include <exception>

class AnyTypeException : public std::exception {
private:
	std::string ex_msg;

public:
	AnyTypeException(std::string msg) {
		ex_msg = msg;
	}
	std::string reason() {
		return "Exception: " + ex_msg;
	}
};

class AnyType {
private:
	enum class TypeValue {
		SHORT, INT, LONG_LONG, FLOAT, DOUBLE, LONG_DOUBLE, CHAR, BOOL
	};

	union {
		short short_value;
		int int_value;
		long long l_l_value;
		float float_value;
		double double_value;
		long double l_double_value;
		char char_value;
		bool bool_value;
	};
	TypeValue t_value;

public:
	// Constructors
	AnyType() = default;

	AnyType(short value) : t_value(TypeValue::SHORT) {
		short_value = value; 
	}

	AnyType(int value) : t_value(TypeValue::INT) {
		int_value = value; 
	}

	AnyType(long long value) : t_value(TypeValue::LONG_LONG) {
		l_l_value = value;
	}

	AnyType(float value) : t_value(TypeValue::FLOAT) {
		float_value = value;
	}

	AnyType(double value) : t_value(TypeValue::DOUBLE) {
		double_value = value;
	}

	AnyType(long double value) : t_value(TypeValue::LONG_DOUBLE) {
		l_double_value = value;
	}

	AnyType(char value) : t_value(TypeValue::CHAR) {
		char_value = value;
	}

	AnyType(bool value) : t_value(TypeValue::BOOL) {
		bool_value = value;
	}

	// Destructor
	~AnyType() = default;

	// Copy constructor
	AnyType(const AnyType& other);

	// Move constructor
	AnyType(AnyType&& other) noexcept;

	// Assignment operator
	AnyType& operator=(const AnyType& other);

	// Move assigment operator
	AnyType& operator=(AnyType&& other);

	// Swap two objects
	void SwapObjects(AnyType& other);

	// Access functions
	short ToShort() const;

	int ToInt() const;

	long long ToLongLong() const;

	float ToFloat() const;

	double ToDouble() const;

	long double ToLongDouble() const;

	char ToChar() const;

	bool ToBool() const;

	// Output type of value
	void OutputTypeValue() const;

};

