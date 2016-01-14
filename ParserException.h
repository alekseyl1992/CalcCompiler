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
        ss << L"Получен токен '"
            << got.value
            << L"', "
            << L"ожидались: ";

        if (expected.size()) {
            ss << Token::getTypeString(*expected.begin());

            for (auto it = expected.begin() + 1; it != expected.end(); ++it)
                ss << L", " << Token::getTypeString(*it);
        }

        str = ss.str();
    }

    ParserException(std::wstring message,
                    const Token &got)
        : got(got), expected({}) {
        std::wstringstream ss;
        ss << message
            << got.getTypeString()
            << L": "
            << got.value;

        str = ss.str();
    }

    ParserException(std::wstring message) {
        std::wstringstream ss;
        ss << message;

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
    std::initializer_list<Token::Type> expected;
    std::wstring str;
};

class ParserExprException : public ParserException {
public:
    ParserExprException(std::wstring message,
                    int from, int to)
        : ParserException(message), from(from), to(to) {

    }

    int getFrom() {
        return from;
    }

    int getTo() {
        return to;
    }

private:
    int from = 0, to = 0;
};

#endif // PARSEREXCEPTION

