#include "Integer.hpp"
#include "Cleaner.hpp"

Integer::Integer()
    : m_data(0)
{}

Integer::Integer(int number)
    : m_data(number) 
{}

Getable *Integer::Get(Getable *key) const{
    return nullptr;
}

std::string Integer::ToString() const{
    return std::to_string(m_data);
}

std::string Integer::GetType() const{
    return "Integer";
}

bool Integer::IsEqual(Getable *value) const{
    return !value->GetType().compare("Integer") && ((Integer *)value)->GetNumber() == m_data;
}

int Integer::GetNumber(){
    return m_data;
}
