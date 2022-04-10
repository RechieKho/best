#include <algorithm>
#include <cstdarg>

#include "String.hpp"
#include "List.hpp"
#include "Integer.hpp"
#include "Log.hpp"
#include "Cleaner.hpp"

List::List(int n_args, ...){
    va_list valist;
    va_start(valist, n_args);
    for (int i = 0; i < n_args; i++) {
        BstObj *e = va_arg(valist, BstObj*);
        e->ref_count++;
        lst.push_back(e);
        };
    va_end(valist); //clean memory reserved for valist
}

List::~List(){
    for(int i = 0; i < lst.size(); i++) lst[i]--;
    Cleaner::flush();
}

BstObj *List::get(const BstObj &key) const{
    // checks
    if(key.get_type().compare("Integer")){
        return nullptr; // print error message
    }
    return lst[((Integer &)key).to_native()];
}

BstObj *List::copy() const {
    return new List(); // TODO
}

void List::set(const BstObj &key, const BstObj &value){
    int index;

    // checks
    if(key.get_type().compare("Integer")){
        return; // print error message
    } 
    else if((index = ((Integer &)key).to_native()) < lst.size()){
        return; // print error message
    }
    else if (lst[index] == &value) return;

    BstObj *copied_value = value.copy();

    lst[index]->ref_count--;
    copied_value->ref_count++;
    lst[index] = copied_value;
}

std::string List::to_string() const{
    std::string repr = "[";
    int size = lst.size();
    for(int i = 0; i < size; i++){
        BstObj *e = lst[i];
        if(!e->get_type().compare("String")) repr += "'" + e->to_string() + "'";
        else repr += e->to_string();
        if(i < size - 1) repr += ", ";
    }
    repr += "]";
    return repr;
}

std::string List::get_type() const{
    return "List";
}

bool List::operator==(const BstObj &value) const{
    return !value.get_type().compare("List") && ((List &)value).lst == lst;
}

void List::push_back(BstObj *value){
    lst.push_back(value);
    value->ref_count++;
}

void List::pop_back(){
    lst.back()->ref_count--;
    lst.pop_back();
}

struct ListContainChecker{
    const BstObj &value;
    ListContainChecker(const BstObj &i) : value(i) {}
    bool operator()(BstObj *i) {return value == *i;}
};
bool List::contains(const BstObj &value) const{
    struct ListContainChecker c(value);
    return std::find_if(lst.begin(), lst.end(), c) != lst.end();
}

std::vector<BstObj*> List::to_native() const{
    return lst;
}