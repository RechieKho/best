#include <iostream>
#include "Integer.hpp"
#include "String.hpp"
#include "Float.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

int main(){
    Object o;
    std::cout << o.ToString() << std::endl;
    o.Set(String("LOl"), String("OFF"));
    o.Set(String("SHI"), String("ON"));
    std::cout << o.ToString() << std::endl;
    Cleaner::Flush();
    o.Set(Integer(2), String("YES"));
    std::cout << o.ToString() << std::endl;
    std::cout << (String("s") == String("s")? "Yay": "NOo") << std::endl;
}