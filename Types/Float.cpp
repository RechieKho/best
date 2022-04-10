#include "Float.hpp"
#include "Cleaner.hpp"

Float::Float(float number)
    : m_data(number) 
{}

const Getable *Float::Get(const Getable *key) const{
    return nullptr;
}

std::string Float::ToString() const{
    return std::to_string(m_data);
}

std::string Float::GetType() const{
    return "Float";
}

float Float::GetNumber(){
    return m_data;
}

bool Float::IsEqual(const Getable *value) const{
    return !value->GetType().compare("Float") && ((Float *)value)->GetNumber() == m_data;
}