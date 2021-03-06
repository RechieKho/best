#ifndef BLEXER_H
#define BLEXER_H

#include <vector>
#include <string>
#include "BToken.hpp"

struct TokenTextPair
{
    BToken token;
    std::string text;

    TokenTextPair(BToken token, std::string text);
};


class BLexer{
public:
    static std::vector<TokenTextPair> get_tokens(std::string text);
};

#endif