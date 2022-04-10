#include <cstdarg>
#include "String.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

#define MAX_VECTOR_SIZE 30
#define MIN_HASH_ARR_SIZE 5
#define MAX_TABLE_SIZE(hash_arr_size) MAX_VECTOR_SIZE*hash_arr_size
#define EXPANDED_HASH_ARR_SIZE(hash_arr_size) hash_arr_size * 2

KeyValuePair::KeyValuePair(const BstObj *key, BstObj *value): key(key), value(value) {
    key->ref_count++;
    value->ref_count++;
}

KeyValuePair::~KeyValuePair(){
    key->ref_count--;
    value->ref_count--;
}

Object::Object()
    : table_size(MIN_HASH_ARR_SIZE),
    table((std::vector<KeyValuePair *> *)malloc(
        MIN_HASH_ARR_SIZE * sizeof(std::vector<KeyValuePair>)
    ))
{
}

Object::Object(int n_args, ...)
    : table_size(n_args? n_args * 2 : MIN_HASH_ARR_SIZE),
    table((std::vector<KeyValuePair *> *)malloc(
       (n_args? n_args * 2 : MIN_HASH_ARR_SIZE) * sizeof(std::vector<KeyValuePair>)
    ))
{
    for(
        int i = 0;
        i < (table_size);
        i++
    ) table[i] = std::vector<KeyValuePair *>();

    va_list valist;
    va_start(valist, n_args);
    for(int i = 0; i < n_args; i++) {
        KeyValuePair *pair = va_arg(valist, KeyValuePair *);
        table[hash(pair->key->to_string(), table_size)].push_back(pair);
    }
    va_end(valist);
}

Object::~Object(){
    for(int i = 0; i < table_size; i++){
        std::vector<KeyValuePair *> &pairs = table[i];
        for(int j = 0; j < pairs.size(); j++){
            delete pairs[j];
        }
    }
    free(table);
    Cleaner::flush();
}


BstObj *Object::get(const BstObj &key) const {
    std::vector<KeyValuePair *> &pairs = table[hash(key.to_string(), table_size)];
    for(const KeyValuePair * const pair: pairs) if(*pair->key == key) return pair->value;
    return nullptr;
}

BstObj *Object::copy() const {
    return new Object(); // TODO
}

void Object::set(const BstObj &key, const BstObj &value) {
    // copying
    const BstObj *copied_key = key.copy();
    BstObj *copied_value = value.copy();

    std::vector<KeyValuePair *> &pairs = table[hash(key.to_string(), table_size)];
    for(KeyValuePair * const pair: pairs) if(*pair->key == key) {
        pair->value = copied_value; 
        return;
    }
    KeyValuePair *pair = new KeyValuePair(copied_key, copied_value);
    pairs.push_back(pair);
}

std::string Object::get_type() const {
    return "Object";
}

std::string Object::to_string() const {
    bool past_first_element = false;
    std::string repr = "{";
    for(int i = 0; i<table_size; i++){
        const std::vector<KeyValuePair *> &pairs = table[i];
        int size = pairs.size();
        for(int j = 0; j < size; j++){
            if(past_first_element) repr += ", ";
            else past_first_element = true;

            const KeyValuePair * const pair = pairs[j];
            if(!pair->key->get_type().compare("String")) repr += "'" + pair->key->to_string() + "'";
            else repr += pair->key->to_string();

            repr += ": ";

            if(!pair->value->get_type().compare("String")) repr += "'" + pair->value->to_string() + "'";
            else repr += pair->value->to_string();
        }
    }
    repr += "}";
    return repr;
}

bool Object::operator==(const BstObj &value) const{
    if(value.get_type().compare("Object")) return false;
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