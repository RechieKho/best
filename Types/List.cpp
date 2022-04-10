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
    Cleaner::Flush();
}

BstObj *List::Get(const BstObj &key) const{
    // checks
    if(key.GetType().compare("Integer")){
        return nullptr; // print error message
    }
    return lst[((Integer &)key).ToNative()];
}

BstObj *List::Copy() const {
    return new List(); // TODO
}

void List::Set(const BstObj &key, const BstObj &value){
    int index;

    // checks
    if(key.GetType().compare("Integer")){
        return; // print error message
    } 
    else if((index = ((Integer &)key).ToNative()) < lst.size()){
        return; // print error message
    }
    else if (lst[index] == &value) return;

    BstObj *copied_value = value.Copy();

    lst[index]->ref_count--;
    copied_value->ref_count++;
    lst[index] = copied_value;
}

std::string List::ToString() const{
    std::string repr = "[";
    int size = lst.size();
    for(int i = 0; i < size; i++){
        BstObj *e = lst[i];
        if(!e->GetType().compare("String")) repr += "'" + e->ToString() + "'";
        else repr += e->ToString();
        if(i < size - 1) repr += ", ";
    }
    repr += "]";
    return repr;
}

std::string List::GetType() const{
    return "List";
}

bool List::operator==(const BstObj &value) const{
    return !value.GetType().compare("List") && ((List &)value).lst == lst;
}

void List::PushBack(BstObj *value){
    lst.push_back(value);
    value->ref_count++;
}

void List::PopBack(){
    lst.back()->ref_count--;
    lst.pop_back();
}

struct ListContainChecker{
    const BstObj &value;
    ListContainChecker(const BstObj &i) : value(i) {}
    bool operator()(BstObj *i) {return value == *i;}
};
bool List::Contains(const BstObj &value) const{
    struct ListContainChecker c(value);
    return std::find_if(lst.begin(), lst.end(), c) != lst.end();
}

std::vector<BstObj*> List::ToNative() const{
    return lst;
}