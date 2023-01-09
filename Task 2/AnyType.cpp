#include <iostream>
#include "AnyType.h"

AnyType::AnyType(const AnyType& other) {
	this->t_value = other.t_value;

	switch (t_value) {
	case TypeValue::SHORT:
		this->short_value = other.short_value;
		break;
	case TypeValue::INT:
		this->int_value = other.int_value;
		break;
	case TypeValue::LONG_LONG:
		this->l_l_value = other.l_l_value;
		break;
	case TypeValue::FLOAT:
		this->float_value = other.float_value;
		break;
	case TypeValue::DOUBLE:
		this->double_value = other.double_value;
		break;
	case TypeValue::LONG_DOUBLE:
		this->l_double_value = other.l_double_value;
		break;
	case TypeValue::CHAR:
		this->char_value = other.char_value;
		break;
	case TypeValue::BOOL:
		this->bool_value = other.bool_value;
		break;
	default:
		throw AnyTypeException("Wrong type!");
		break;
	}
}

AnyType::AnyType(AnyType&& other) noexcept 
	: t_value(std::move(other.t_value)) {
	switch (t_value) {
	case TypeValue::SHORT:
		this->short_value = std::move(other.short_value);
		break;
	case TypeValue::INT:
		this->int_value = std::move(other.int_value);
		break;
	case TypeValue::LONG_LONG:
		this->l_l_value = std::move(other.l_l_value);
		break;
	case TypeValue::FLOAT:
		this->float_value = std::move(other.float_value);
		break;
	case TypeValue::DOUBLE:
		this->double_value = std::move(other.double_value);
		break;
	case TypeValue::LONG_DOUBLE:
		this->l_double_value = std::move(other.l_double_value);
		break;
	case TypeValue::CHAR:
		this->char_value = std::move(other.char_value);
		break;
	case TypeValue::BOOL:
		this->bool_value = std::move(other.bool_value);
		break;
	default:
		throw AnyTypeException("Wrong type!");
		break;
	}
	other.~AnyType();
}

AnyType& AnyType::operator=(const AnyType& other)
{
	if (this != &other) {
		this->~AnyType();
		new(this) AnyType(other);
	}
	return *this;
}

AnyType& AnyType::operator=(AnyType&& other) {
	if (this != &other) {
		this->~AnyType();
		new(this) AnyType(std::move(other));
	}
	return *this;
}

void AnyType::SwapObjects(AnyType& other) {
	AnyType temp = other;
	other = *this;
	*this = temp;
}

short AnyType::ToShort() const {
	if (this->t_value == TypeValue::SHORT) {
		return this->short_value;
	}
	else {
		throw AnyTypeException("Your type: short.");
	}
}

int AnyType::ToInt() const {
	if (this->t_value == TypeValue::INT) {
		return this->int_value;
	}
	else {
		throw AnyTypeException("Your type: int.");
	}
}

long long AnyType::ToLongLong() const {
	if (this->t_value == TypeValue::LONG_LONG) {
		return this->l_l_value;
	}
	else {
		throw AnyTypeException("Your type: long long.");
	}
}

float AnyType::ToFloat() const {
	if (this->t_value == TypeValue::FLOAT) {
		return this->float_value;
	}
	else {
		throw AnyTypeException("Your type: float.");
	}
}

double AnyType::ToDouble() const {
	if (this->t_value == TypeValue::DOUBLE) {
		return this->double_value;
	}
	else {
		throw AnyTypeException("Your type: double.");
	}
}

long double AnyType::ToLongDouble() const {
	if (this->t_value == TypeValue::LONG_DOUBLE) {
		return this->l_double_value;
	}
	else {
		throw AnyTypeException("Your type: long double.");
	}
}

char AnyType::ToChar() const {
	if (this->t_value == TypeValue::CHAR) {
		return this->char_value;
	}
	else {
		throw AnyTypeException("Your type: char.");
	}
}

bool AnyType::ToBool() const {
	if (this->t_value == TypeValue::BOOL) {
		return this->bool_value;
	}
	else {
		throw AnyTypeException("Your type: bool.");
	}
}

void AnyType::OutputTypeValue() const {
	switch (t_value) {
	case TypeValue::SHORT:
		std::cout << "Short type." << std::endl;
		break;
	case TypeValue::INT:
		std::cout << "Int type." << std::endl;
		break;
	case TypeValue::LONG_LONG:
		std::cout << "Long long type." << std::endl;
		break;
	case TypeValue::FLOAT:
		std::cout << "Float type." << std::endl;
		break;
	case TypeValue::DOUBLE:
		std::cout << "Double type." << std::endl;
		break;
	case TypeValue::LONG_DOUBLE:
		std::cout << "Long double type." << std::endl;
		break;
	case TypeValue::CHAR:
		std::cout << "Char type." << std::endl;
		break;
	case TypeValue::BOOL:
		std::cout << "Bool type." << std::endl;
		break;
	default:
		throw AnyTypeException("Wrong type!");
		break;
	}
}
