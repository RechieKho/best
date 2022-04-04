#include <iostream>
#include "Text.hpp"
#include "Integer.hpp"


int main(){
    Text s = Text("length");
    Integer *length = (Integer *) s.Get(&s);
    std::cout << "Text contained: " << s.ToString() << "\nText's length: " << length->ToString() << std::endl;
}