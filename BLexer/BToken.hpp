#ifndef BTOKEN_H
#define BTOKEN_H

enum class BToken{
    WORD,
    S_QUOTE_STRING, // '
    D_QUOTE_STRING, // "
    BACKTICK_STRING, // `
    NEWLINE,
    CURLY_OPEN,
    CURLY_CLOSE,
    SQUARE_OPEN,
    SQUARE_CLOSE,
    COMMENT, // # comment
    EQUAL,
    COLON,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    DOT,
    P_OPEN, // (
    P_CLOSE // )
};

#endif