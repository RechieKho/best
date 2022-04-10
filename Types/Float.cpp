#include "String.hpp"
#include "Float.hpp"
#include "Cleaner.hpp"

Float::Float(float number)
    : num(number) 
{}

BstObj *Float::get(const BstObj &key) const{
    return nullptr;
}

BstObj *Float::copy() const {
    return new Float(num);
}

std::string Float::to_string() const{
    return std::to_string(num);
}

std::string Float::get_type() const{
    return "Float";
}

bool Float::operator==(const BstObj &value) const{
    return !value.get_type().compare("Float") && ((Float &)value).to_native() == num;
}

float Float::to_native() const {
    return num;
}