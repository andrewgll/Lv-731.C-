#include <iostream>
#include <typeinfo>
#include "../lib/AnyType.hpp"

void Conversion(AnyType b){
    try{
        std::cout << "Char:\t"<< b.ToChar() << "\n";
    }
    catch(const char* msg){
        std::cerr << msg;
    }
    try{
        std::cout << "Short:\t"<< b.ToShort() << "\n";
    }
    catch(const char* msg){
        std::cerr << msg;
    }
    try{
        std::cout << "Int:\t"<< b.ToInt() << "\n";
    }
    catch(const char* msg){
        std::cerr << msg;
    }
    try{
        std::cout << "Long:\t"<< b.ToLong() << "\n";
    }
    catch(const char* msg){
        std::cerr << msg;
    }
    try{
        std::cout << "Long L:\t"<< b.ToLongLong() << "\n";
    }
    catch(const char* msg){
        std::cerr << msg;
    }
    try{
         std::cout << "Bool:\t"<< b.ToBool() << "\n";
    }
    catch(const char* msg){
        std::cerr << msg;
    }
    try{
        std::cout << "Float:\t"<< b.ToFloat() << "\n";
    }
    catch(const char* msg){
        std::cerr << msg;
    }
    try{
        std::cout << "Double:\t"<< b.ToDouble() << "\n";
    }
    catch(const char* msg){
        std::cerr << msg;
    }
         std::cout << "*****************\n";
   }
int main(){
    AnyType d = 2.2232323233232;
    Conversion(d);
    AnyType b = true;
    Conversion(b);
    b = 'c';
    Conversion(b);
    b = 1.1;
    Conversion(b);
    std::cout << b.GetType() << '\n';
    b = 100;
    b /= 15.5;
    std::cout << b.ToFloat() << '\n';
 }