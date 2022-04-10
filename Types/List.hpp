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

    BstObj *Get(const BstObj &key) const override;
    BstObj *Copy() const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool operator==(const BstObj &value) const override;

    void Set(const BstObj &key, const BstObj &value);
    void PushBack(BstObj *value);
    void PopBack();
    bool Contains(const BstObj &value) const;
    std::vector<BstObj*> ToNative() const;
};

#endif