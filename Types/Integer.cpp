#include "Integer.hpp"

Integer::Integer(int number)
    : m_data(number) {}

Getable *Integer::Get(Getable *key){
    return this;
}

std::string Integer::ToString(){
    return std::to_string(m_data);
}