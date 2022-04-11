#include "String.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

String::String(const std::string& text)
    : str(text)
{}

String::String(const char *text)
    : str(text)
{}

BstObj *String::get() const {
    return new STR("String");
}

BstObj *String::get(const BstObj &key) const{
    const BstObj *key_type = key.get();
    bool is_not_str = *key_type != STR("String");
    delete key_type;
    if(is_not_str) return nullptr;

    std::string str_key = ((const String&)key).to_native();

    if(str_key == "copy" || str_key == "to_string") return new STR(str);

    return nullptr;
}

bool String::operator==(const BstObj &value) const{
    const String *type = (const String *)value.get();
    const bool is_str = type->to_native() == "String";
    delete type;
    return is_str && ((const String &)value).str == str;
}

bool String::operator==(const String &value){
    return value.str == str;
}

String String::operator+(const String &value){
    return STR(str + value.str);
}

String &String::operator+=(const String &value){
    str += value.str;
    return *this;
}

std::string String::to_native() const {
    return str;
}