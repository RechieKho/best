#ifndef ARRAY_H
#define ARRAY_H

#include <vector>

#include "Getable.hpp"

class Array: public Getable{
    std::vector<Getable*> m_data;
public:
    Array() = default;
    Array(int n_args,...);
    ~Array();

    Getable *Get(const Getable &key) const override;
    Getable *Copy() const override;
    std::string ToString() const override;
    std::string GetType() const override;
    bool operator==(const Getable &value) const override;

    void Set(const Getable &key, const Getable &value);
    void PushBack(Getable *value);
    void PopBack();
    bool Contains(const Getable &value) const;
    std::vector<Getable*> ToNative() const;
};

#endif