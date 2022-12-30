#include "AnyType.hpp"
#include "string.h"
#include <iostream>
#include <typeinfo>
AnyType::AnyType(int data)
    : data(data), d_data(0){}
AnyType::AnyType(long data)
    : data(data), d_data(0){}
AnyType::AnyType(long long data)
    : data(data), d_data(0){}
AnyType::AnyType(double d_data)
    : d_data(d_data), data(0){}
AnyType::AnyType(float d_data)
    : d_data(d_data), data(0){}
AnyType AnyType::operator=(const AnyType& rdata){
    d_data = rdata.d_data;
    data = rdata.data;
}
const char* AnyType::GetType(){
    if(data == 0){
        return typeid(d_data).name();
    }
    return typeid(data).name();
}
void AnyType::Check(long long data){
    if(data == 0){
        throw "Cannot convert from double or float\n";
    }
}
char AnyType::ToChar(){
    Check(data);
    if(data <= INT8_MAX && data >= INT8_MIN){
        return static_cast<char>(data);
    }
    else {
        throw "Cannot convert to char\n";
    }
}
short AnyType::ToShort(){
    Check(data);
    if(data <= INT16_MAX && data >= INT16_MIN){
        return static_cast<short>(data);
    }
    throw "Cannot convert to short\n";
}
int AnyType::ToInt(){
    Check(data);
    if(data <= INT32_MAX && data >= INT32_MIN){
        return static_cast<int>(data);
    }
    throw "Cannot convert to int\n";
}
long AnyType::ToLong(){
    Check(data);
    if(data <=  INT64_MAX && data >= INT64_MIN ){
        return static_cast<long>(data);
    }
    throw "Cannot convert to long\n";
}
long long AnyType::ToLongLong(){
    Check(data);
    return data;
}
bool AnyType::ToBool(){
    if(data == 0){
        return (bool)d_data;
    }
    return (bool)data;
}
float AnyType::ToFloat(){
    if(d_data == 0){
        return data;
    }
    return d_data;
}
double AnyType::ToDouble(){
    if(d_data == 0){
        return data;
    }
    return d_data;
}