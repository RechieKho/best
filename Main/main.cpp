#include <iostream>
#include "BstObj.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Float.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

int main(){
    Object o;
    o.set(STR("NO"), STR("string key."));
    o.set(INT(2), STR("integer key."));
    o.set(FLT(3.5), STR("This is hell"));
    std::cout << o << std::endl;

    List l;
    l.push_back(INT(1));
    l.push_back(INT(2));
    std::cout << l <<std::endl;

    const List &s = *(List *)l.get(STR("@copy"));
    std::cout << s <<std::endl;

    std::cout << (s == l? "yes": "no") << std::endl;
}