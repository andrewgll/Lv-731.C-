#include <iostream>
#pragma once
class AnyType {
private:
    long long data;
    double d_data;
    char *type;
    
private:
    void Check(long long data);
    void CheckDouble(double data);
public:
    AnyType(long long data, double d_data, char* type){}
    AnyType(const AnyType& other);
    AnyType(AnyType&& other);
	AnyType(char value) : type("char"), data(value), d_data(0) {}
	AnyType(short value) : type("short"), data(value), d_data(0) {}
	AnyType(int value) : type("int"), data(value),d_data(0) {}
	AnyType(long long value) : type("long long"), data(value), d_data(0) {}
	AnyType(float value) : type("float"), data(0),d_data(value) {}
	AnyType(double value) : type("double"), data(0), d_data(value)  {}
	AnyType(bool value) : type("bool"), data(value), d_data(0){}
    ~AnyType(){delete type;}
    char ToChar();
    short ToShort();
    int ToInt();
    long ToLong();
    long long ToLongLong();
    bool ToBool();
    float ToFloat();
    double ToDouble();
    char* GetType() {return type;}
    AnyType operator = (const AnyType& rdata);
    AnyType operator += (const AnyType& rdata);
    AnyType operator -= (const AnyType& rdata);
    AnyType operator /= (const AnyType& rdata);
    AnyType operator *= (const AnyType& rdata);
   };