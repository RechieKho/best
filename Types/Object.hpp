#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "Setable.hpp"
#include "Array.hpp"
#include "Cleaner.hpp"

struct KeyValuePair{
    Getable *key, *value;
    KeyValuePair(Getable *key, Getable *value);
    ~KeyValuePair();
};

class Object: public Setable{
    std::vector<KeyValuePair *> *m_hash_arr;
    int m_hash_arr_size;

    int hash(std::string text, int max_number) const;
public:
    Object();
    Object(int arg, ...);
    ~Object();
    const Getable *Get(const Getable *key = NULL) const override;
    void Set(Getable *key, Getable *value) override;
    std::string GetType() const override;
    std::string ToString() const override;
    bool IsEqual(const Getable *value) const override;
    
    Array *GetKeys() const;
};

#endif