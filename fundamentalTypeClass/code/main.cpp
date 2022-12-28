#include <iostream>
#include <typeinfo>
#include "../lib/AnyType.hpp"

int main(){
    AnyType any = 1;
    any = true;
    std::cout << any.GetType();
    int b = any.ToInt();
    std::cout << any;
}