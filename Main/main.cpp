#include <iostream>
#include "Integer.hpp"
#include "String.hpp"
#include "Float.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

int main(){
    Object o;
    std::cout << o.ToString() << std::endl;
    o.Set(new String(), new Integer(2));
    o.Set(new Integer(2), new String("NOOOO"));
    std::cout << o.ToString() << std::endl;
    Cleaner::Flush();
    o.Set(new Integer(2), new String("YES"));
    std::cout << o.ToString() << std::endl;
}