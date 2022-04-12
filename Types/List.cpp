#include <algorithm>
#include <cstdarg>

#include "String.hpp"
#include "List.hpp"
#include "Integer.hpp"
#include "Log.hpp"
#include "Cleaner.hpp"

List::~List(){
    for(int i = 0; i < lst.size(); i++) delete lst[i];
}

BstObj *List::get() const {
    return new STR("List");
}

BstObj *List::get(const BstObj &key) const{
    const BstObj *key_type_p = key.get();
    const std::string key_type = ((const String *)(key_type_p))->to_native();
    delete key_type_p;

    if(key_type == "Integer") {
        return lst[((Integer &)key).to_native()]->get(STR("@copy"));
    }
    else if(key_type == "String"){
        const std::string str_key = ((const String&) key).to_native();

        if(str_key == "@copy") {
            List *l = new List();
            for (int i = 0; i < lst.size(); i++) l->push_back(*lst[i]);
            return l;
        }
        else if (str_key == "@to_string"){
            String &repr = *(new STR("["));
            int size = lst.size();
            for(int i = 0; i < size; i++){
                const BstObj *e = lst[i];
                const String *e_type = (const String *)e->get();
                const String *e_string = (const String *)e->get(STR("@to_string"));
                const std::string e_string_native = e_string->to_native();
                if(e_type->to_native() == "String") repr += "'" + e_string_native + "'";
                else repr += e_string_native;
                delete e_type;
                delete e_string;
                if(i < size - 1) repr += ", ";
            }
            repr += "]";
            return &repr;
        }
    }
    
    return nullptr;
}

void List::set(const BstObj &key, const BstObj &value){
    const String *key_type_p = (const String *)key.get();
    const std::string key_type = key_type_p->to_native();
    delete key_type_p;
    int index = lst.size();

    // checks
    if(key_type != "Integer"){
        return; // print error message
    } 
    else if((index = ((Integer &)key).to_native()) >= lst.size()){
        return; // print error message
    }
    else if (*lst[index] == value) return;

    const BstObj *copied_value = value.get(STR("@copy"));

    delete lst[index];
    copied_value->ref_count++;
    lst[index] = copied_value;
}

bool List::operator==(const BstObj &value) const{
    const String *value_type_p = (const String *)value.get();
    const bool is_not_list = *value_type_p != STR("List");
    delete value_type_p;
    if (is_not_list) return false;
    
    for (int i = 0; i < lst.size(); i++) if(*lst[i] != *((List &)value).lst[i]) return false;
    return true;
}

void List::push_back(const BstObj &value){
    const BstObj *copied_value = value.get(STR("@copy"));
    copied_value->ref_count++;
    lst.push_back(copied_value);
}

void List::pop_back(){
    delete lst.back();
    lst.pop_back();
}

struct ListContainChecker{
    const BstObj &value;
    ListContainChecker(const BstObj &i) : value(i) {}
    bool operator()(const BstObj *i) {return value == *i;}
};
bool List::contains(const BstObj &value) const{
    struct ListContainChecker c(value);
    return std::find_if(lst.begin(), lst.end(), c) != lst.end();
}