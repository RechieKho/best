#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

#include "Setable.hpp"

class Array: public Setable{
    std::vector<Getable*> m_data;
public:
    Array() = default;
    Array(int n_args,...);
    ~Array();
    const Getable *Get(const Getable *key = NULL) const override;
    void Set(Getable *key, Getable *value) override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool IsEqual(const Getable *value) const override;

    void PushBack(Getable *value);
    void PopBack();
    bool Contains(Getable *value) const;
};

#endif