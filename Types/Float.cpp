#include "String.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Cleaner.hpp"

Float::Float(const float &number)
    : num(number) 
{}

BstObj *Float::get() const {
    return new STR("Float");
}

BstObj *Float::get(const BstObj &key) const{
    const BstObj *key_type = key.get();
    bool is_not_str = *key_type != STR("String");
    delete key_type;
    if(is_not_str) return nullptr;

    std::string str_key = ((const String&)key).to_native();

    if(str_key == "copy") return new FLT(num);
    else if(str_key == "to_string") return new STR(std::to_string(num));

    return nullptr;
}

bool Float::operator==(const BstObj &value) const{
    const String *type = (const String *)value.get();
    bool is_float = *type == STR("Float");
    delete type;
    return is_float && ((Float &)value).to_native() == num;
}

float Float::to_native() const {
    return num;
}