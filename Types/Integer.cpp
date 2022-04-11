#include "String.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

Integer::Integer()
    : num(0)
{}

Integer::Integer(int number)
    : num(number) 
{}

BstObj *Integer::get() const {
    return new STR("Integer");
}

BstObj *Integer::get(const BstObj &key) const{
    const BstObj *key_type = key.get();
    bool is_not_str = *key_type != STR("String");
    delete key_type;
    if(is_not_str) return nullptr;

    std::string str_key = ((const String&)key).to_native();

    if(str_key == "copy") return new INT(num);
    else if(str_key == "to_string") return new STR(std::to_string(num));

    return nullptr;
}

bool Integer::operator==(const BstObj &value) const{
    const String *type = (const String *)value.get();
    bool is_int = *type == STR("Integer");
    delete type;
    return is_int && ((Integer &)value).to_native() == num;
}

int Integer::to_native() const{
    return num;
}