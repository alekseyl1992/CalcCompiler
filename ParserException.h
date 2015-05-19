#ifndef PARSEREXCEPTION
#define PARSEREXCEPTION
#include <exception>
#include "Token.h"

class ParserException
{
public:
    ParserException(const Token &got,
                    const std::initializer_list<Token::Type> &expected)
        : got(got), expected(expected)
    {
        std::wstringstream ss;
        ss << L"Получен токен "
            << got.getTypeString()
            << L": "
            << got.value
            << L", "
            << L"ожидались: {";

        for (auto exp: expected)
            ss << Token::getTypeString(exp) << L", ";

        ss << L"}";

        str = ss.str();
    }

    ParserException(const ParserException &e) = default;
    ParserException(ParserException &&e) = default;

    // exception interface
    virtual const wchar_t *what() const
    {
        return str.c_str();
    }

    const Token &getToken() {
        return got;
    }

private:
    Token got;
    const std::initializer_list<Token::Type> &expected;
    std::wstring str;
};

#endif // PARSEREXCEPTION

