#ifndef TOKEN_H
#define TOKEN_H
#include <string>

struct Token {
    enum Type { BEGIN, END, LINE_BREAK,
                ARRAY, STRING,
                NUMBER, VARIABLE,
                ASSIGN, LABEL,
		PLUS, MINUS, MULTIPLY, DIVIDE, POWER,
                AND, OR,
                LBRACE, RBRACE, TOKEN_TYPES_COUNT };

    const char *getTypeString() const {
        return getTypeString(type);
    }

    static const char *getTypeString(Type type) {
        static const char *strings[] = {
                "BEGIN", "END", "LINE_BREAK",
                "ARRAY", "STRING",
                "NUMBER", "VARIABLE",
                "ASSIGN", "LABEL",
		"PLUS", "MINUS", "MULTIPLY", "DIVIDE", "POWER"
                "AND", "OR",
                "LBRACE", "RBRACE"
        };

        return strings[type];
    }

    Type type;
    std::string value;
};

#endif // TOKEN_H

