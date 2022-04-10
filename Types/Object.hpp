#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "BstObj.hpp"
#include "List.hpp"
#include "Cleaner.hpp"

struct KeyValuePair{
    const BstObj *key;
    BstObj *value;
    KeyValuePair(const BstObj *key, BstObj *value);
    ~KeyValuePair();
};

class Object: public BstObj{
    std::vector<KeyValuePair *> *table;
    int table_size;

    int hash(std::string text, int max_number) const;
public:
    Object();
    Object(int arg, ...);
    ~Object();

    BstObj *Get(const BstObj &key) const override;
    BstObj *Copy() const override;
    std::string GetType() const override;
    std::string ToString() const override;
    bool operator==(const BstObj &value) const override;
    
    void Set(const BstObj &key, const BstObj &value);
};

#endif