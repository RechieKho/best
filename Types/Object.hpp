#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "BstObj.hpp"
#include "List.hpp"
#include "Cleaner.hpp"

struct KeyValuePair;

class Object: public BstObj{
    std::vector<KeyValuePair *> *arr;
    int arr_size;

    int hash(std::string text, int max_number) const;
public:
    Object(int pair_count = 30);
    ~Object();

    BstObj *get() const override;
    BstObj *get(const BstObj &key) const override;
    bool operator==(const BstObj &value) const override;
    
    void set(const BstObj &key, const BstObj &value);
};

#endif