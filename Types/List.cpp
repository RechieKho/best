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

BstObj *List::get() const {
    return new STR("List");
}

BstObj *List::get(const BstObj &key) const{
    const BstObj *key_type = key.get();

    if(*key_type == STR("Integer")) {
        delete key_type;
        return lst[((Integer &)key).to_native()];
    }
    else if(*key_type == STR("String")){
        delete key_type;
        const String& str_key = (const String&) key;

        if(str_key == STR("copy")) {
            return new List(); // TODO
        }
        else if (str_key == STR("to_string")){
            std::string repr = "[";
            int size = lst.size();
            for(int i = 0; i < size; i++){
                BstObj *e = lst[i];
                const String *e_type = (const String *)e->get();
                const String *e_string = (const String *)e->get(STR("to_string"));
                const std::string e_string_native = e_string->to_native();
                if(e_type->to_native() == "String") repr += "'" + e_string_native + "'";
                else repr += e_string_native;
                delete e_type;
                delete e_string;
                if(i < size - 1) repr += ", ";
            }
            repr += "]";
            return new STR(repr);
        }
    }
    
    return nullptr;
}

void List::set(const BstObj &key, const BstObj &value){
    const String *tmp = (const String *)key.get();
    const std::string key_type = tmp->to_native();
    delete tmp;
    int index;

    // checks
    if(key_type != "Integer"){
        return; // print error message
    } 
    else if((index = ((Integer &)key).to_native()) < lst.size()){
        return; // print error message
    }
    else if (lst[index] == &value) return;

    BstObj *copied_value = value.get(STR("copy"));

    lst[index]->ref_count--;
    copied_value->ref_count++;
    lst[index] = copied_value;
}

bool List::operator==(const BstObj &value) const{
    const String *tmp = (const String *)value.get();
    const bool is_list = *tmp == STR("List");
    delete tmp;
    return is_list && ((List &)value).lst == lst;
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