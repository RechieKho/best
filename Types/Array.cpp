#include <algorithm>
#include <cstdarg>

#include "Array.hpp"
#include "Integer.hpp"
#include "Log.hpp"
#include "Cleaner.hpp"

Array::Array(int n_args, ...){
    va_list valist;
    va_start(valist, n_args);
    for (int i = 0; i < n_args; i++) {
        Getable *e = va_arg(valist, Getable *);
        e->ref_count++;
        m_data.push_back(e);
        };
    va_end(valist); //clean memory reserved for valist
}

Array::~Array(){
    for(int i = 0; i < m_data.size(); i++) m_data[i]--;
    Cleaner::Flush();
}

Getable *Array::Get(Getable *key) const{
    // checks
    if(key->GetType().compare("Integer")){
        return NULL; // print error message
    }
    return m_data.at(((Integer *)key)->GetNumber());
}

void Array::Set(Getable *key, Getable *value){
    int index;

    // checks
    if(key->GetType().compare("Integer")){
        return; // print error message
    } 
    else if((index = ((Integer *)key)->GetNumber()) < m_data.size()){
        return; // print error message
    }
    else if (m_data[index] == value) return;

    m_data[index]->ref_count--;
    value->ref_count++;
    m_data[index] = value;
}

std::string Array::ToString() const{
    std::string repr = "[";
    int size = m_data.size();
    for(int i = 0; i < size; i++){
        Getable *e = m_data[i];
        if(!e->GetType().compare("String")) repr += "'" + e->ToString() + "'";
        else repr += e->ToString();
        if(i < size - 1) repr += ", ";
    }
    repr += "]";
    return repr;
}

std::string Array::GetType() const{
    return "Array";
}

bool Array::IsEqual(Getable *value) const{
    return !value->GetType().compare("Array") && ((Array *)value)->m_data == m_data;
}

void Array::PushBack(Getable *value){
    m_data.push_back(value);
    value->ref_count++;
}

void Array::PopBack(){
    m_data.back()->ref_count--;
    m_data.pop_back();
}

struct ArrayContainChecker{
    Getable *value;
    ArrayContainChecker(Getable *i) : value(i) {}
    bool operator()(Getable *i) {return value->IsEqual(i);}
};
bool Array::Contains(Getable *value) const{
    struct ArrayContainChecker c(value);
    return std::find_if(m_data.begin(), m_data.end(), c) != m_data.end();
}