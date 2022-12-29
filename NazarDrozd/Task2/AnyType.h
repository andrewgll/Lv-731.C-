#pragma once
#include <iostream>
#include <exception>
#include <string>

class ExceptionType : public std::exception
{
public:
	ExceptionType(std::string msg) { m_msg = msg; }
	std::string what() { return "Exception: " + m_msg; }
private:
	std::string m_msg;
};

class AnyType
{
public:
	//constructors
	AnyType() : m_type(Type::UNKNOWN) { }
	AnyType(bool value) : m_type(Type::BOOL) { m_value_bool = value; }
	AnyType(short value) : m_type(Type::SHORT) { m_value_short = value; }
	AnyType(int value) : m_type(Type::INT) { m_value_int = value; }
	AnyType(long long value) : m_type(Type::LONG_LONG) { m_value_l_long = value; }
	AnyType(char value) : m_type(Type::CHAR) { m_value_char = value; }
	AnyType(float value) : m_type(Type::FLOAT) { m_value_float = value; }
	AnyType(double value) : m_type(Type::DOUBLE) { m_value_double = value; }
	AnyType(long double value) : m_type(Type::LONG_DOUBLE) { m_value_l_double = value; }
	//constructor copy
	AnyType(const AnyType& other);
	//assignment operator
	AnyType& operator=(const AnyType& other);
	//move constructor
	AnyType(AnyType&& other) noexcept;
	//move assigment operator
	AnyType& operator= (AnyType&& other) noexcept;
	//assignment operators
	AnyType& operator += (AnyType& other);
	AnyType& operator -= (AnyType& other);
	AnyType& operator *= (AnyType& other);
	AnyType& operator /= (AnyType& other);
	//value access
	bool GetValueBool() const;
	short GetValueShort() const;
	int GetValueInt() const;
	long long GetValueLongLong() const;
	char GetValueChar() const;
	float GetValueFloat() const;
	double GetValueDouble() const;
	long double GetValueLongDouble() const;

	void Swap(AnyType& other);

	void ShowValueType() const;
	//destructor
	virtual ~AnyType() = default;
private:
	enum Type
	{
		BOOL, SHORT, INT, LONG_LONG, CHAR, FLOAT,
		DOUBLE, LONG_DOUBLE, UNKNOWN
	};
	union {
		bool m_value_bool;
		short m_value_short;
		int m_value_int;
		long long m_value_l_long;
		char m_value_char;
		float m_value_float;
		double m_value_double;
		long double m_value_l_double;
	};
	Type m_type;
};