#include <iostream>
#include "Integer.hpp"
#include "String.hpp"
#include "Float.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

int main(){
    Object o;
    std::cout << o.to_string() << std::endl;
    o.set(STR("LOl"), STR());
    o.set(STR("SHI"), STR("ON"));
    std::cout << o.to_string() << std::endl;
    Cleaner::flush();
    o.set(INT(2), STR("YES"));
    std::cout << o.to_string() << std::endl;
    std::cout << (STR("s") == STR("s")? "Yay": "NOo") << std::endl;
}