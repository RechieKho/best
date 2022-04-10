#include "String.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

Integer::Integer()
    : num(0)
{}

Integer::Integer(int number)
    : num(number) 
{}

BstObj *Integer::Get(const BstObj &key) const{
    return nullptr;
}

BstObj *Integer::Copy() const {
    return new Integer(num);
}

std::string Integer::ToString() const{
    return std::to_string(num);
}

std::string Integer::GetType() const{
    return "Integer";
}

bool Integer::operator==(const BstObj &value) const{
    return !value.GetType().compare("Integer") && ((Integer &)value).ToNative() == num;
}

int Integer::ToNative() const{
    return num;
}