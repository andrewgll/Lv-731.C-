#pragma once
#include "AnyType.h"
//copy constructor
AnyType::AnyType(const AnyType& other)
	: m_type(other.m_type)
{
	switch (m_type)
	{
	case Type::BOOL:
		m_value_bool = other.m_value_bool;
		break;
	case Type::SHORT:
		m_value_short = other.m_value_short;
		break;
	case Type::INT:
		m_value_int = other.m_value_int;
		break;
	case Type::LONG_LONG:
		m_value_l_long = other.m_value_l_long;
		break;
	case Type::CHAR:
		m_value_char = other.m_value_char;
		break;
	case Type::FLOAT:
		m_value_float = other.m_value_float;
		break;
	case Type::DOUBLE:
		m_value_double = other.m_value_double;
		break;
	case Type::LONG_DOUBLE:
		m_value_l_double = other.m_value_l_double;
		break;
	default:
		throw ExceptionType("You can't initialize an object with an uninitialized object.");
		break;
	}
}
//assignment operator
AnyType& AnyType::operator=(const AnyType& other)
{
	if (this != &other)
	{
		this->~AnyType();
		new(this) AnyType(other);
	}
	return *this;
}
//move constructor
AnyType::AnyType(AnyType&& other) noexcept
	: m_type(std::move(other.m_type))
{
	switch (m_type)
	{
	case Type::BOOL:
		m_value_bool = std::move(other.m_value_bool);
		break;
	case Type::SHORT:
		m_value_short = std::move(other.m_value_short);
		break;
	case Type::INT:
		m_value_int = std::move(other.m_value_int);
		break;
	case Type::LONG_LONG:
		m_value_l_long = std::move(other.m_value_l_long);
		break;
	case Type::CHAR:
		m_value_char = std::move(other.m_value_char);
		break;
	case Type::FLOAT:
		m_value_float = std::move(other.m_value_float);
		break;
	case Type::DOUBLE:
		m_value_double = std::move(other.m_value_double);
		break;
	case Type::LONG_DOUBLE:
		m_value_l_double = std::move(other.m_value_l_double);
		break;
	}
	other.~AnyType();
}
//move assigment operator
AnyType& AnyType::operator=(AnyType&& other) noexcept
{
	if (this != &other)
	{
		this->~AnyType();
		new(this) AnyType(std::move(other));
	}
	return *this;
}
//assignment operators
AnyType& AnyType::operator+=(AnyType& other)
{
	if (m_type == other.m_type)
	{
		switch (m_type)
		{
		case Type::BOOL: {
			bool val1 = GetValueBool(), val2 = other.GetValueBool();
			this->~AnyType();
			new(this) AnyType(val1 + val2);
			return *this;
		}
		case Type::SHORT: {
			short val1 = GetValueShort(), val2 = other.GetValueShort();
			this->~AnyType();
			new(this) AnyType(val1 + val2);
			return *this;
		}
		case Type::INT: {
			int val1 = GetValueInt(), val2 = other.GetValueInt();
			this->~AnyType();
			new(this) AnyType(val1 + val2);
			return *this;
		}
		case Type::LONG_LONG: {
			long long val1 = GetValueLongLong(), val2 = other.GetValueLongLong();
			this->~AnyType();
			new(this) AnyType(val1 + val2);
			return *this;
		}
		case Type::CHAR: {
			char val1 = GetValueChar(), val2 = other.GetValueChar();
			this->~AnyType();
			new(this) AnyType(val1 + val2);
			return *this;
		}
		case Type::FLOAT: {
			float val1 = GetValueFloat(), val2 = other.GetValueFloat();
			this->~AnyType();
			new(this) AnyType(val1 + val2);
			return *this;
		}
		case Type::DOUBLE: {
			double val1 = GetValueDouble(), val2 = other.GetValueDouble();
			this->~AnyType();
			new(this) AnyType(val1 + val2);
			return *this;
		}
		case Type::LONG_DOUBLE: {
			long double val1 = GetValueLongDouble(), val2 = other.GetValueLongDouble();
			this->~AnyType();
			new(this) AnyType(val1 + val2);
			return *this;
		}
		}
	}
	else
	{
		throw ExceptionType("Error operator '+='. Your type is unknown");
	}
}
AnyType& AnyType::operator-=(AnyType& other)
{
	if (m_type == other.m_type)
	{
		switch (m_type)
		{
		case Type::BOOL: {
			bool val1 = GetValueBool(), val2 = other.GetValueBool();
			this->~AnyType();
			new(this) AnyType(val1 - val2);
			return *this;
		}
		case Type::SHORT: {
			short val1 = GetValueShort(), val2 = other.GetValueShort();
			this->~AnyType();
			new(this) AnyType(val1 - val2);
			return *this;
		}
		case Type::INT: {
			int val1 = GetValueInt(), val2 = other.GetValueInt();
			this->~AnyType();
			new(this) AnyType(val1 - val2);
			return *this;
		}
		case Type::LONG_LONG: {
			long long val1 = GetValueLongLong(), val2 = other.GetValueLongLong();
			this->~AnyType();
			new(this) AnyType(val1 - val2);
			return *this;
		}
		case Type::CHAR: {
			char val1 = GetValueChar(), val2 = other.GetValueChar();
			this->~AnyType();
			new(this) AnyType(val1 - val2);
			return *this;
		}
		case Type::FLOAT: {
			float val1 = GetValueFloat(), val2 = other.GetValueFloat();
			this->~AnyType();
			new(this) AnyType(val1 - val2);
			return *this;
		}
		case Type::DOUBLE: {
			double val1 = GetValueDouble(), val2 = other.GetValueDouble();
			this->~AnyType();
			new(this) AnyType(val1 - val2);
			return *this;
		}
		case Type::LONG_DOUBLE: {
			long double val1 = GetValueLongDouble(), val2 = other.GetValueLongDouble();
			this->~AnyType();
			new(this) AnyType(val1 - val2);
			return *this;
		}
		}
	}
	else
	{
		throw ExceptionType("Error operator '-='. Your type is unknown");
	}
}
AnyType& AnyType::operator*=(AnyType& other)
{
	if (m_type == other.m_type)
	{
		switch (m_type)
		{
		case Type::BOOL: {
			bool val1 = GetValueBool(), val2 = other.GetValueBool();
			this->~AnyType();
			new(this) AnyType(val1 * val2);
			return *this;
		}
		case Type::SHORT: {
			short val1 = GetValueShort(), val2 = other.GetValueShort();
			this->~AnyType();
			new(this) AnyType(val1 * val2);
			return *this;
		}
		case Type::INT: {
			int val1 = GetValueInt(), val2 = other.GetValueInt();
			this->~AnyType();
			new(this) AnyType(val1 * val2);
			return *this;
		}
		case Type::LONG_LONG: {
			long long val1 = GetValueLongLong(), val2 = other.GetValueLongLong();
			this->~AnyType();
			new(this) AnyType(val1 * val2);
			return *this;
		}
		case Type::CHAR: {
			char val1 = GetValueChar(), val2 = other.GetValueChar();
			this->~AnyType();
			new(this) AnyType(val1 * val2);
			return *this;
		}
		case Type::FLOAT: {
			float val1 = GetValueFloat(), val2 = other.GetValueFloat();
			this->~AnyType();
			new(this) AnyType(val1 * val2);
			return *this;
		}
		case Type::DOUBLE: {
			double val1 = GetValueDouble(), val2 = other.GetValueDouble();
			this->~AnyType();
			new(this) AnyType(val1 * val2);
			return *this;
		}
		case Type::LONG_DOUBLE: {
			long double val1 = GetValueLongDouble(), val2 = other.GetValueLongDouble();
			this->~AnyType();
			new(this) AnyType(val1 * val2);
			return *this;
		}
		}
	}
	else
	{
		throw ExceptionType("Error operator '*='. Your type is unknown");
	}
}
AnyType& AnyType::operator/=(AnyType& other)
{
	if (m_type == other.m_type)
	{
		switch (m_type)
		{
		case Type::BOOL: {
			bool val1 = GetValueBool(), val2 = other.GetValueBool();
			this->~AnyType();
			new(this) AnyType(val1 / val2);
			return *this;
		}
		case Type::SHORT: {
			short val1 = GetValueShort(), val2 = other.GetValueShort();
			this->~AnyType();
			new(this) AnyType(val1 / val2);
			return *this;
		}
		case Type::INT: {
			int val1 = GetValueInt(), val2 = other.GetValueInt();
			this->~AnyType();
			new(this) AnyType(val1 / val2);
			return *this;
		}
		case Type::LONG_LONG: {
			long long val1 = GetValueLongLong(), val2 = other.GetValueLongLong();
			this->~AnyType();
			new(this) AnyType(val1 / val2);
			return *this;
		}
		case Type::CHAR: {
			char val1 = GetValueChar(), val2 = other.GetValueChar();
			this->~AnyType();
			new(this) AnyType(val1 / val2);
			return *this;
		}
		case Type::FLOAT: {
			float val1 = GetValueFloat(), val2 = other.GetValueFloat();
			this->~AnyType();
			new(this) AnyType(val1 / val2);
			return *this;
		}
		case Type::DOUBLE: {
			double val1 = GetValueDouble(), val2 = other.GetValueDouble();
			this->~AnyType();
			new(this) AnyType(val1 / val2);
			return *this;
		}
		case Type::LONG_DOUBLE: {
			long double val1 = GetValueLongDouble(), val2 = other.GetValueLongDouble();
			this->~AnyType();
			new(this) AnyType(val1 / val2);
			return *this;
		}
		}
	}
	else
	{
		throw ExceptionType("Error operator '/='. Your type is unknown");
	}
}
//value access
bool AnyType::GetValueBool() const
{
	if (m_type != Type::BOOL)
	{
		throw ExceptionType("BadType. Your type isn't 'bool'");
	}
	return m_value_bool;
}
short AnyType::GetValueShort() const
{
	if (m_type != Type::SHORT)
	{
		throw ExceptionType("BadType. Your type isn't 'short'");
	}
	return m_value_short;
}
int AnyType::GetValueInt() const
{
	if (m_type != Type::INT)
	{
		throw ExceptionType("BadType. Your type isn't 'int'");
	}
	return m_value_int;
}
long long AnyType::GetValueLongLong() const
{
	if (m_type != Type::LONG_LONG)
	{
		throw ExceptionType("BadType. Your type isn't 'long long'");
	}
	return m_value_l_long;
}
char AnyType::GetValueChar() const
{
	if (m_type != Type::CHAR)
	{
		throw ExceptionType("BadType. Your type isn't 'char'");
	}
	return m_value_char;
}
float AnyType::GetValueFloat() const
{
	if (m_type != Type::FLOAT)
	{
		throw ExceptionType("BadType. Your type isn't 'float'");
	}
	return m_value_float;
}
double AnyType::GetValueDouble() const
{
	if (m_type != Type::DOUBLE)
	{
		throw ExceptionType("BadType. Your type isn't 'double'");
	}
	return m_value_double;
}
long double AnyType::GetValueLongDouble() const
{
	if (m_type != Type::LONG_DOUBLE)
	{
		throw ExceptionType("BadType. Your type isn't 'long double'");
	}
	return m_value_l_double;
}

void AnyType::Swap(AnyType& other)
{
	AnyType temp = std::move(other);
	other = std::move(*this);
	*this = std::move(temp);
}

void AnyType::ShowValueType() const
{
	switch (m_type)
	{
	case Type::BOOL:
		std::cout << "bool\n";
		break;
	case Type::SHORT:
		std::cout << "short\n";
		break;
	case Type::INT:
		std::cout << "int\n";
		break;
	case Type::LONG_LONG:
		std::cout << "long long\n";
		break;
	case Type::CHAR:
		std::cout << "char\n";
		break;
	case Type::FLOAT:
		std::cout << "float\n";
		break;
	case Type::DOUBLE:
		std::cout << "double\n";
		break;
	case Type::LONG_DOUBLE:
		std::cout << "long double\n";
		break;
	default:
		std::cout << "Unknown type\n";
		break;
	}
}