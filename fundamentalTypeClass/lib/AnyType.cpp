#include "AnyType.hpp"
#include <iostream>
#include <string.h>
#include <stdexcept>

AnyType::AnyType(AnyType&& obj)
    : data(std::move(obj.data)) {

    }
AnyType AnyType:: operator = (AnyType const &rvalue){
    data = rvalue.data;
    type = rvalue.type;
}
AnyType AnyType:: operator = (char value){
    data.c = value; 
    type = "c";
}
AnyType AnyType:: operator = (short value){
    data.si = value; 
    type = "si";
}
AnyType AnyType:: operator = (int value){
    data.i = value; 
    type = "i";
}
AnyType AnyType:: operator = (long value){
    data.l = value; 
    type = "l";
}
AnyType AnyType:: operator = (long long value){
    data.ll = value; 
    type = "ll";
}
AnyType AnyType:: operator = (double value){
    data.d = value; 
    type = "d";
}
AnyType AnyType:: operator = (long double value){
    data.ld = value; 
    type = "ld";
}
AnyType AnyType:: operator = (bool value){
    data.b = value; 
    type = "b";
}

AnyType::AnyType(char c)
{
    data.c = c;
    type = "c";
}
AnyType::AnyType(short s)
{
    data.si = s;
    type = "si";
}
AnyType::AnyType(int i)
{
    data.i = i;
    type = "i";
}
AnyType::AnyType(long l)
{
    data.l = l;
    type = "l";
}
AnyType::AnyType(long long ll)
{
    data.ll = ll;
    type = "l";
}
AnyType::AnyType(float f)
{
    data.f = f;
    type = "f";
}
AnyType::AnyType(double d)
{
    data.d = d;
    type = "d";
}
AnyType::AnyType(long double ld)
{
    data.ld = ld;
    type = "ld";
}
AnyType::AnyType(bool b)
{
    data.b = b;
    type = "b";
}
char* AnyType::GetType(){
    return type;
}
int AnyType:: ToInt(){
    if(strcmp(type, "i")==0){
        return data.i;
    }
    else if(strcmp(type, "c") == 0){
        return static_cast<int>(data.c);
    }
    else if(strcmp(type, "si") == 0){
        return static_cast<int>(data.si);
    }
    else if(strcmp(type, "f") == 0){
        return static_cast<int>(data.f);
    }
    else if(strcmp(type, "d") == 0){
        return static_cast<int>(data.d);
    }
    else if(strcmp(type, "ld") == 0){
        return static_cast<int>(data.ld);
    }
    else if(strcmp(type, "b") == 0){
        return static_cast<int>(data.b);
    }
    else if(strcmp(type, "ll") == 0 || strcmp(type, "l") == 0){
        throw "Can not convert long to int.";
    }
}
long AnyType:: ToLong(){
    if(strcmp(type, "l")==0){
        return data.l;
    }
    else if(strcmp(type, "i") == 0){
        return static_cast<long>(data.i);    
    }
    else if(strcmp(type, "c") == 0){
        return static_cast<long>(data.c);
    }
    else if(strcmp(type, "si") == 0){
        return static_cast<long>(data.si);
    }
    else if(strcmp(type, "f") == 0){
        return static_cast<long>(data.f);
    }
    else if(strcmp(type, "d") == 0){
        return static_cast<long>(data.d);
    }
    else if(strcmp(type, "ld") == 0){
        return static_cast<long>(data.ld);
    }
    else if(strcmp(type, "b") == 0){
        return static_cast<long>(data.b);
    }
    else if(strcmp(type, "ll") == 0){
        throw "Can not convert long long to long.";
    }
}
AnyType::~AnyType() {

}