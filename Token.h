#ifndef TOKEN_H
#define TOKEN_H
#include <string>

struct Token {
    enum Type { UNKNOWN, BEGIN, END, LINE_BREAK,
                ARRAY, STRING,
                NUMBER, VARIABLE,
                ASSIGN, LABEL,
                PLUS, MINUS, MULTIPLY, DIVIDE, POWER,
                AND, OR,
                LBRACE, RBRACE, TOKEN_TYPES_COUNT };

    const wchar_t *getTypeString() const {
        return getTypeString(type);
    }

    static const wchar_t *getTypeString(Type type) {
        static const wchar_t *strings[] = {
            L"UNKNOWN", L"BEGIN", L"END", L"LINE_BREAK",
            L"ARRAY", L"STRING",
            L"NUMBER", L"VARIABLE",
            L"ASSIGN", L"LABEL",
            L"PLUS", L"MINUS", L"MULTIPLY", L"DIVIDE", L"POWER"
            L"AND", L"OR",
            L"LBRACE", L"RBRACE"
        };

        return strings[type];
    }

    Type type;
    std::wstring value;
    int pos;
};

#endif // TOKEN_H

