#include <cstdarg>
#include "String.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

#define MAX_VECTOR_SIZE 30
#define MIN_HASH_ARR_SIZE 5
#define MAX_TABLE_SIZE(hash_arr_size) MAX_VECTOR_SIZE*hash_arr_size
#define EXPANDED_HASH_ARR_SIZE(hash_arr_size) hash_arr_size * 2

KeyValuePair::KeyValuePair(const Getable *key, Getable *value): key(key), value(value) {
    key->ref_count++;
    value->ref_count++;
}

KeyValuePair::~KeyValuePair(){
    key->ref_count--;
    value->ref_count--;
}

Object::Object()
    : m_hash_arr_size(MIN_HASH_ARR_SIZE),
    m_hash_arr((std::vector<KeyValuePair *> *)malloc(
        MIN_HASH_ARR_SIZE * sizeof(std::vector<KeyValuePair>)
    ))
{
}

Object::Object(int n_args, ...)
    : m_hash_arr_size(n_args? n_args * 2 : MIN_HASH_ARR_SIZE),
    m_hash_arr((std::vector<KeyValuePair *> *)malloc(
       (n_args? n_args * 2 : MIN_HASH_ARR_SIZE) * sizeof(std::vector<KeyValuePair>)
    ))
{
    for(
        int i = 0;
        i < (m_hash_arr_size);
        i++
    ) m_hash_arr[i] = std::vector<KeyValuePair *>();

    va_list valist;
    va_start(valist, n_args);
    for(int i = 0; i < n_args; i++) {
        KeyValuePair *pair = va_arg(valist, KeyValuePair *);
        m_hash_arr[hash(pair->key->ToString(), m_hash_arr_size)].push_back(pair);
    }
    va_end(valist);
}

Object::~Object(){
    for(int i = 0; i < m_hash_arr_size; i++){
        std::vector<KeyValuePair *> &pairs = m_hash_arr[i];
        for(int j = 0; j < pairs.size(); j++){
            delete pairs[j];
        }
    }
    free(m_hash_arr);
    Cleaner::Flush();
}


Getable *Object::Get(const Getable &key) const {
    std::vector<KeyValuePair *> &pairs = m_hash_arr[hash(key.ToString(), m_hash_arr_size)];
    for(const KeyValuePair * const pair: pairs) if(*pair->key == key) return pair->value;
    return nullptr;
}

Getable *Object::Copy() const {
    return new Object(); // TODO
}

void Object::Set(const Getable &key, const Getable &value) {
    // copying
    const Getable *copied_key = key.Copy();
    Getable *copied_value = value.Copy();

    std::vector<KeyValuePair *> &pairs = m_hash_arr[hash(key.ToString(), m_hash_arr_size)];
    for(KeyValuePair * const pair: pairs) if(*pair->key == key) {
        pair->value = copied_value; 
        return;
    }
    KeyValuePair *pair = new KeyValuePair(copied_key, copied_value);
    pairs.push_back(pair);
}

std::string Object::GetType() const {
    return "Object";
}

std::string Object::ToString() const {
    bool past_first_element = false;
    std::string repr = "{";
    for(int i = 0; i<m_hash_arr_size; i++){
        const std::vector<KeyValuePair *> &pairs = m_hash_arr[i];
        int size = pairs.size();
        for(int j = 0; j < size; j++){
            if(past_first_element) repr += ", ";
            else past_first_element = true;

            const KeyValuePair * const pair = pairs[j];
            if(!pair->key->GetType().compare("String")) repr += "'" + pair->key->ToString() + "'";
            else repr += pair->key->ToString();

            repr += ": ";

            if(!pair->value->GetType().compare("String")) repr += "'" + pair->value->ToString() + "'";
            else repr += pair->value->ToString();
        }
    }
    repr += "}";
    return repr;
}

bool Object::operator==(const Getable &value) const{
    if(value.GetType().compare("Object")) return false;
    else {
        const Object &o = (const Object&)value;
        for(int i = 0; i<m_hash_arr_size; i++){
            const std::vector<KeyValuePair *> &pairs = m_hash_arr[i];
            for(int j = 0; j < pairs.size(); j++) if(o.Get(*(pairs[j]->key)) != pairs[j]->value) return false;
        }
    }
    return true;
}

int Object::hash(std::string text, int max_number) const {
    int n = 1;
    for(int i = 0; i < text.size(); i++) n *= (int)text[i];
    return n % max_number;
}