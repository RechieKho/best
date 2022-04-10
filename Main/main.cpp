#include <iostream>
#include "Integer.hpp"
#include "String.hpp"
#include "Float.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

int main(){
    Object o;
    std::cout << o.ToString() << std::endl;
    o.Set(STR("LOl"), STR());
    o.Set(STR("SHI"), STR("ON"));
    std::cout << o.ToString() << std::endl;
    Cleaner::Flush();
    o.Set(INT(2), STR("YES"));
    std::cout << o.ToString() << std::endl;
    std::cout << (STR("s") == STR("s")? "Yay": "NOo") << std::endl;
}