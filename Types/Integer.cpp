#include "String.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

Integer::Integer()
    : num(0)
{}

Integer::Integer(int number)
    : num(number) 
{}

BstObj *Integer::get(const BstObj &key) const{
    return nullptr;
}

BstObj *Integer::copy() const {
    return new Integer(num);
}

std::string Integer::to_string() const{
    return std::to_string(num);
}

std::string Integer::get_type() const{
    return "Integer";
}

bool Integer::operator==(const BstObj &value) const{
    return !value.get_type().compare("Integer") && ((Integer &)value).to_native() == num;
}

int Integer::to_native() const{
    return num;
}