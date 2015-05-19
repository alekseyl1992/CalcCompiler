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
            L"", L"начало", L"окончание", L"перенос строки",
            L"массив", L"строка",
            L"число", L"переменная",
            L"=", L"метка",
            L"+", L"-", L"*", L"/", L"^",
            L"&", L"|",
            L"(", L")"
        };

        return strings[type];
    }

    Type type;
    std::wstring value;
    int pos;
};

#endif // TOKEN_H

