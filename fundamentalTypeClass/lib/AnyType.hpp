#include <iostream>
#pragma once
class AnyType {
private:
    long long data;
    double d_data;
private:
    void Check(long long data);
    void CheckDouble(double data);
public:
    AnyType(int data);
    AnyType(long data);
    AnyType(long long data);
    AnyType(double d_data);
    AnyType(float d_data);
    char ToChar();
    short ToShort();
    int ToInt();
    long ToLong();
    long long ToLongLong();
    bool ToBool();
    float ToFloat();
    double ToDouble();
    const char* GetType();
    AnyType operator = (const AnyType& rdata);
   };