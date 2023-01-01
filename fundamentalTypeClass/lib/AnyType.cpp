#include "AnyType.hpp"
#include "string.h"
#include <iostream>
#include <typeinfo>

AnyType AnyType::operator=(const AnyType& rdata){
    d_data = rdata.d_data;
    data = rdata.data;
    type = rdata.type;
}
AnyType AnyType::operator+=(const AnyType& rdata){
    d_data += rdata.d_data;
    data += rdata.data;
    type = rdata.type;
}
AnyType AnyType::operator-=(const AnyType& rdata){
    d_data -= rdata.d_data;
    data -= rdata.data;
    type = rdata.type;
}
AnyType AnyType::operator/=(const AnyType& rdata){
    
    if(d_data != 0 ){
        if(rdata.d_data != 0) {
            d_data /= rdata.d_data;
        }
        else if(rdata.data != 0){
            d_data /= rdata.data;
        }
    }
    if(data != 0){
        if(rdata.d_data != 0){
            data /= rdata.d_data;
        }
        else if(rdata.data != 0){
            data /= rdata.data;
        }
    }
    type = rdata.type;
}
AnyType AnyType::operator*=(const AnyType& rdata){
    d_data *= rdata.d_data;
    data *= rdata.data;
    type = rdata.type;
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
AnyType::AnyType(const AnyType& other)
    : type(other.type), 
    d_data(other.d_data), 
    data(other.data){}
AnyType::AnyType(const AnyType&& other) noexcept
    :type(std::move(other.type)),
    data(std::move(other.data)),
    d_data(std::move(other.d_data)){}