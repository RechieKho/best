#include <cstdarg>
#include "String.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

#define MAX_VECTOR_SIZE 30
#define MIN_HASH_ARR_SIZE 5
#define MAX_TABLE_SIZE(hash_arr_size) MAX_VECTOR_SIZE*hash_arr_size
#define EXPANDED_HASH_ARR_SIZE(hash_arr_size) hash_arr_size * 2

struct KeyValuePair{
    const String *key;
    const BstObj *value;

    KeyValuePair(const String *key, const BstObj *value) : key(key), value(value) {}
};

Object::Object()
    : table_size(MIN_HASH_ARR_SIZE),
    table((std::vector<KeyValuePair *> *)malloc(
        MIN_HASH_ARR_SIZE * sizeof(std::vector<KeyValuePair>)
    ))
{}

// Object::Object(int n_args, ...)
//     : table_size(n_args? n_args * 2 : MIN_HASH_ARR_SIZE),
//     table((std::vector<KeyValuePair *> *)malloc(
//        (n_args? n_args * 2 : MIN_HASH_ARR_SIZE) * sizeof(std::vector<KeyValuePair>)
//     ))
// {
//     for(
//         int i = 0;
//         i < (table_size);
//         i++
//     ) table[i] = std::vector<KeyValuePair *>();

//     va_list valist;
//     va_start(valist, n_args);
//     for(int i = 0; i < n_args; i++) {
//         KeyValuePair *pair = va_arg(valist, KeyValuePair *);
//         table[hash(((const String *)pair->key), table_size)].push_back(pair);
//     }
//     va_end(valist);
// }

Object::~Object(){
    for(int i = 0; i < table_size; i++){
        std::vector<KeyValuePair *> &pairs = table[i];
        for(int j = 0; j < pairs.size(); j++){
            delete pairs[j]->key;
            delete pairs[j]->value;
            delete pairs[j];
        }
    }
    free(table);
}

BstObj *Object::get() const {
    return new STR("Object");
}

BstObj *Object::get(const BstObj &key) const {
    const BstObj *key_type_p = key.get();
    bool is_not_str = *key_type_p != STR("String");
    delete key_type_p;
    if(is_not_str) return nullptr;

    std::string str_key = ((const String&)key).to_native();

    if(str_key == "@copy") {
        Object *o = new Object();
        return o; // TODO
    }

    else if(str_key == "@to_string"){
        bool past_first_element = false;

        String &repr = *(new String("{"));
        for(int i = 0; i<table_size; i++){
            const std::vector<KeyValuePair *> &pairs = table[i];
            int size = pairs.size();
            for(int j = 0; j < size; j++){
                if(past_first_element) repr += ", ";
                else past_first_element = true;

                const KeyValuePair * const pair = pairs[j];

                const String *key_type_p = (const String *)pair->key->get();
                const String *key_p = (const String*)pair->key;
                const String *value_type_p = (const String *)pair->value->get();
                const String *value_p = (const String *)pair->value;
                
                if(*key_type_p == STR("String")) repr += STR("'") + *key_p + "'";
                else repr += *key_p;

                repr += ": ";

                if(*value_type_p == STR("String")) repr += STR("'") + *value_p + "'";
                else repr += *value_p;

                delete key_type_p;
                delete value_type_p;
            }
        }
        repr += "}";
        return &repr;
    }
    else {
        std::vector<KeyValuePair *> &pairs = table[hash(str_key, table_size)];
        for(const KeyValuePair * const pair: pairs) if(*pair->key == key){ 
            BstObj *copied_value = pair->value->get(STR("@copy"));
            return copied_value;
        }
    }

    return nullptr;
}

void Object::set(const BstObj &key, const BstObj &value){
    const String *copied_key_p = (const String *)key.get(STR("@to_string"));
    const BstObj *copied_value_p = value.get(STR("@copy"));
    std::vector<KeyValuePair *> &pairs = table[hash(copied_key_p->to_native(), table_size)];

    copied_value_p->ref_count++;

    for(KeyValuePair * const pair: pairs) if(*pair->key == *copied_key_p){
        const BstObj *tmp = pair->value;
        pair->value = copied_value_p;
        delete tmp;
        delete copied_key_p;
        return;
    }

    // add new key value pair
    copied_key_p->ref_count++;
    KeyValuePair * const pair = new KeyValuePair(copied_key_p, copied_value_p);
    pairs.push_back(pair);
}

bool Object::operator==(const BstObj &value) const{
    const String *value_type_p = (const String *)value.get();
    bool is_obj = *value_type_p == STR("Object");
    delete value_type_p;

    if(is_obj) return false;
    else {
        const Object &o = (const Object&)value;
        for(int i = 0; i<table_size; i++){
            const std::vector<KeyValuePair *> &pairs = table[i];
            for(int j = 0; j < pairs.size(); j++) if(o.get(*(pairs[j]->key)) != pairs[j]->value) return false;
        }
    }
    return true;
}

int Object::hash(std::string text, int max_number) const {
    int n = 1;
    for(int i = 0; i < text.size(); i++) n *= (int)text[i];
    return n % max_number;
}