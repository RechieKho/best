#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "Getable.hpp"
#include "Array.hpp"
#include "Cleaner.hpp"

struct KeyValuePair{
    const Getable *key;
    Getable *value;
    KeyValuePair(const Getable *key, Getable *value);
    ~KeyValuePair();
};

class Object: public Getable{
    std::vector<KeyValuePair *> *m_hash_arr;
    int m_hash_arr_size;

    int hash(std::string text, int max_number) const;
public:
    Object();
    Object(int arg, ...);
    ~Object();

    Getable *Get(const Getable &key) const override;
    Getable *Copy() const override;
    std::string GetType() const override;
    std::string ToString() const override;
    bool operator==(const Getable &value) const override;
    
    void Set(const Getable &key, const Getable &value);
};

#endif