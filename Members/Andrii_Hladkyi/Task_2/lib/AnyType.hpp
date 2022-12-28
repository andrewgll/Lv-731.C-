#pragma once
class AnyType{
private:
    char *type; 
    union AnyData {
        char c;
        short si;
        int i;
        long l;
        long long ll;
        bool b;
        float f;
        double d;
        long double ld;
    }data;
public:
    AnyType(char c);
    AnyType(short s);
    AnyType(int i);
    AnyType(long l);
    AnyType(long long ll);
    AnyType(bool b);
    AnyType(float f);
    AnyType(double d);
    AnyType(long double ld);
    AnyType(AnyType&& obj);
    ~AnyType();
public:
    char ToChar();
    short ToShort();
    int ToInt();
    long ToLong();
    long long ToLongLong();
    bool ToBool();
    float ToFloat();
    double ToDouble();
    long double ToLongDouble();
public:
    void Swap(AnyType const &first, AnyType const &second);
    char* GetType();
public:
    AnyType operator = (AnyType const &rvalue);
    AnyType operator = (char value);
    AnyType operator = (short value);
    AnyType operator = (int value);
    AnyType operator = (long value);
    AnyType operator = (long long value);
    AnyType operator = (float value);
    AnyType operator = (double value);
    AnyType operator = (long double value);
    AnyType operator = (bool value);
    AnyType operator << (AnyType const &rvalue);
    AnyType operator >> (AnyType const &rvalue);
};