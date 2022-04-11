#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

#include "BstObj.hpp"

class List: public BstObj{
    std::vector<BstObj*> lst;
public:
    List() = default;
    List(int n_args,...);
    ~List();

    BstObj *get() const override;
    BstObj *get(const BstObj &key) const override;
    bool operator==(const BstObj &value) const override;

    void set(const BstObj &key, const BstObj &value);
    void push_back(BstObj *value);
    void pop_back();
    bool contains(const BstObj &value) const;
    std::vector<BstObj*> to_native() const;
};

#endif