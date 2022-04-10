#include "String.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

Integer::Integer()
    : m_data(0)
{}

Integer::Integer(int number)
    : m_data(number) 
{}

Getable *Integer::Get(const Getable &key) const{
    return nullptr;
}

Getable *Integer::Copy() const {
    return new Integer(m_data);
}

std::string Integer::ToString() const{
    return std::to_string(m_data);
}

std::string Integer::GetType() const{
    return "Integer";
}

bool Integer::operator==(const Getable &value) const{
    return !value.GetType().compare("Integer") && ((Integer &)value).ToNative() == m_data;
}

int Integer::ToNative() const{
    return m_data;
}