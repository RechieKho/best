#include "BstObj.hpp"
#include "String.hpp"

bool BstObj::operator!=(const BstObj &value) const{
    return !(*this == value);
}

std::ostream &operator<<(std::ostream &stream, BstObj &entity){
    const String *str = (const String *)entity.get(STR("@to_string"));
    stream << str->to_native();
    delete str;
    return stream;
}

std::ostream& operator<<(std::ostream &stream, const BstObj &entity){
    const String *str = (const String *)entity.get(STR("@to_string"));
    stream << str->to_native();
    delete str;
    return stream;
}