#include "String.hpp"
#include "Float.hpp"
#include "Cleaner.hpp"

Float::Float(float number)
    : num(number) 
{}

BstObj *Float::Get(const BstObj &key) const{
    return nullptr;
}

BstObj *Float::Copy() const {
    return new Float(num);
}

std::string Float::ToString() const{
    return std::to_string(num);
}

std::string Float::GetType() const{
    return "Float";
}

bool Float::operator==(const BstObj &value) const{
    return !value.GetType().compare("Float") && ((Float &)value).ToNative() == num;
}

float Float::ToNative() const {
    return num;
}