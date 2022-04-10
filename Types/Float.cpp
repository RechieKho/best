#include "String.hpp"
#include "Float.hpp"
#include "Cleaner.hpp"

Float::Float(float number)
    : m_data(number) 
{}

Getable *Float::Get(const Getable &key) const{
    return nullptr;
}

Getable *Float::Copy() const {
    return new Float(m_data);
}

std::string Float::ToString() const{
    return std::to_string(m_data);
}

std::string Float::GetType() const{
    return "Float";
}

bool Float::operator==(const Getable &value) const{
    return !value.GetType().compare("Float") && ((Float &)value).ToNative() == m_data;
}

float Float::ToNative() const {
    return m_data;
}