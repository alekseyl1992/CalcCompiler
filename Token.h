#ifndef TOKEN_H
#define TOKEN_H
#include <string>

struct Token {
    enum Type { BEGIN, END, LINE_BREAK,
                ARRAY, STRING,
                NUMBER, VARIABLE,
                ASSIGN, LABEL,
                PLUS, MINUS, MULTIPLY, DIVIDE,
                AND, OR,
                LBRACE, RBRACE };

    Type type;
    std::string value;
};

#endif // TOKEN_H

