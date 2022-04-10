#include <fstream>

#include "BLexer.hpp"

TokenTextPair::TokenTextPair(BToken token, std::string text)
    : token(token), text(text)
{}

enum LexMode{
    NORMAL,
    STRING,
    COMMENT,
};

std::vector<TokenTextPair> BLexer::get_tokens(std::string text){
    std::vector<TokenTextPair> pairs;
    LexMode lex_mode = NORMAL;
    BToken current_word_token = BToken::WORD;
    std::string staged;

    char string_opening = '"';

    for(int i = 0; i < text.size(); i++){
        char current = text[i];
        char next = i + 1 < text.size()? text[i+1] : '\0';

        switch (lex_mode)
        {
        case NORMAL:
            if(current == ' '){ // Skip white spaces
                if(staged.size()) {pairs.push_back(TokenTextPair(current_word_token, staged)); staged = "";}
                continue;
            }

            if(current == '\'' || current == '"' || current == '`'){
                // to String mode
                if(staged.size()) {pairs.push_back(TokenTextPair(current_word_token, staged)); staged = "";}
                lex_mode = STRING;
                string_opening = current;
                if(current == '\'') current_word_token = BToken::S_QUOTE_STRING;
                else if(current == '"') current_word_token = BToken::D_QUOTE_STRING;
                else current_word_token = BToken::BACKTICK_STRING;
                continue;
            }

            if(current == '#'){
                // to comment mode
                if(staged.size()) {pairs.push_back(TokenTextPair(current_word_token, staged)); staged = "";}
                lex_mode = COMMENT;
                current_word_token = BToken::COMMENT;
                continue;
            }

            if(
                current == '{' ||
                current == '}' ||
                current == '[' ||
                current == ']' ||
                current == ':' ||
                current == '=' ||
                current == '+' ||
                current == '-' ||
                current == '*' ||
                current == '/' ||
                current == '.' ||
                current == '(' ||
                current == ')' ||
                current == '\n'
            ){
                if(staged.size()) {pairs.push_back(TokenTextPair(current_word_token, staged)); staged = "";}
                staged += current;
                if(current == '{') {pairs.push_back(TokenTextPair(BToken::CURLY_OPEN, staged)); staged = "";}
                else if(current == '}') {pairs.push_back(TokenTextPair(BToken::CURLY_CLOSE, staged)); staged = "";}
                else if(current == '[') {pairs.push_back(TokenTextPair(BToken::SQUARE_OPEN, staged)); staged = "";}
                else if(current == ']') {pairs.push_back(TokenTextPair(BToken::SQUARE_CLOSE, staged)); staged = "";}
                else if(current == ':') {pairs.push_back(TokenTextPair(BToken::COLON, staged)); staged = "";}
                else if(current == '=') {pairs.push_back(TokenTextPair(BToken::EQUAL, staged)); staged = "";}
                else if(current == '+') {pairs.push_back(TokenTextPair(BToken::PLUS, staged)); staged = "";}
                else if(current == '-') {pairs.push_back(TokenTextPair(BToken::MINUS, staged)); staged = "";}
                else if(current == '*') {pairs.push_back(TokenTextPair(BToken::MULTIPLY, staged)); staged = "";}
                else if(current == '/') {pairs.push_back(TokenTextPair(BToken::DIVIDE, staged)); staged = "";}
                else if(current == '.') {pairs.push_back(TokenTextPair(BToken::DOT, staged)); staged = "";}
                else if(current == '(') {pairs.push_back(TokenTextPair(BToken::P_OPEN, staged)); staged = "";}
                else if(current == ')') {pairs.push_back(TokenTextPair(BToken::P_CLOSE, staged)); staged = "";}
                else {pairs.push_back(TokenTextPair(BToken::NEWLINE, staged)); staged = "";}
                continue;
            }

            staged += current;
            break;
            
        case STRING:
            if(current == string_opening){
                pairs.push_back(TokenTextPair(current_word_token, staged)); 
                staged = "";
                lex_mode = NORMAL;
                current_word_token = BToken::WORD;
                continue;
            } 
            staged += current;
            break;
        case COMMENT:
            if(current == '\n'){
                pairs.push_back(TokenTextPair(current_word_token, staged)); 
                pairs.push_back(TokenTextPair(BToken::NEWLINE, "\n"));
                staged = "";
                lex_mode = NORMAL;
                current_word_token = BToken::WORD;
                continue;
            }
            staged += current;
            break;
        }
        
    }
    pairs.push_back(TokenTextPair(current_word_token, staged));

    return pairs;
}