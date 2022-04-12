#include <cstdarg>
#include "String.hpp"
#include "Object.hpp"
#include "Cleaner.hpp"

#define AVG_PAIR_COUNT_PER_VECTOR 30
#define MIN_ARR_SIZE 5
#define MAX_PAIR_COUNT(arr_size) arr_size * AVG_PAIR_COUNT_PER_VECTOR
#define EXPANDED_ARR_SIZE(arr_size) arr_size * 2
#define INIT_ARR_SIZE(pair_count) (int)(pair_count / AVG_PAIR_COUNT_PER_VECTOR)*2 > MIN_ARR_SIZE ? (int)(pair_count / AVG_PAIR_COUNT_PER_VECTOR)*2 : MIN_ARR_SIZE

struct KeyValuePair{
    const String *key;
    const BstObj *value;
};

Object::Object(int pair_count)
    : arr_size(INIT_ARR_SIZE(pair_count)),
    arr((std::vector<KeyValuePair *> *)calloc(
        INIT_ARR_SIZE(pair_count), sizeof(std::vector<KeyValuePair *>)
    ))
{}

Object::~Object(){
    for(int i = 0; i < arr_size; i++){
        const std::vector<KeyValuePair *> &pairs = arr[i];
        for(int j = 0; j < pairs.size(); j++){
            delete pairs[j]->key;
            delete pairs[j]->value;
            delete pairs[j];
        }
    }
    free(arr);
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
        Object *o = new Object(arr_size * AVG_PAIR_COUNT_PER_VECTOR);
        for(int i = 0; i < arr_size; i++){
            const std::vector<KeyValuePair *> &pairs = arr[i];
            for(const KeyValuePair * const pair : pairs)
                o->set(*pair->key, *pair->value);
        }
        return o;
    }

    else if(str_key == "@to_string"){
        bool past_first_element = false;

        String &repr = *(new String("{"));
        for(int i = 0; i<arr_size; i++){
            const std::vector<KeyValuePair *> &pairs = arr[i];
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
        std::vector<KeyValuePair *> &pairs = arr[hash(str_key, arr_size)];
        for(const KeyValuePair * const pair: pairs) if(*pair->key == key){ 
            BstObj *copied_value = pair->value->get(STR("@copy"));
            return copied_value;
        }
    }

    return nullptr;
}

void Object::set(const BstObj &key, const BstObj &value){
    const String *str_key_p = (const String *)key.get(STR("@to_string"));
    const BstObj *copied_value_p = value.get(STR("@copy"));
    std::vector<KeyValuePair *> &pairs = arr[hash(str_key_p->to_native(), arr_size)];

    copied_value_p->ref_count++;

    for(int i = 0; i < pairs.size(); i++){
        if(*pairs[i]->key == *str_key_p){
            const BstObj *tmp = pairs[i]->value;
            pairs[i]->value = copied_value_p;
            delete tmp;
            delete str_key_p;
            return;
        }
    }

    // add new key value pair
    str_key_p->ref_count++;
    KeyValuePair * const pair = new KeyValuePair();
    pair->key = str_key_p;
    pair->value = copied_value_p;
    pairs.push_back(pair);
}

// TODO: Make it aware of item count
bool Object::operator==(const BstObj &value) const{
    const String *value_type_p = (const String *)value.get();
    bool is_not_obj = *value_type_p != STR("Object");
    delete value_type_p;

    if(is_not_obj) return false;
    else {
        const Object &o = (const Object&)value;
        for(int i = 0; i<arr_size; i++){
            const std::vector<KeyValuePair *> &pairs = arr[i];
            for(int j = 0; j < pairs.size(); j++){
                const BstObj *value = o.get(*(pairs[j]->key));
                bool is_value_not_the_same = *value != *pairs[j]->value;
                delete value;
                if(is_value_not_the_same) return false;
            } 
        }
    }
    return true;
}

int Object::hash(std::string text, int max_number) const {
    int n = 1;
    for(int i = 0; i < text.size(); i++) n *= (int)text[i];
    return n % max_number;
}