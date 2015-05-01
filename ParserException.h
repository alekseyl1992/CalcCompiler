#ifndef PARSEREXCEPTION
#define PARSEREXCEPTION
#include <exception>
#include "Token.h"

class ParserException : public std::exception
{
public:
    ParserException(const Token &got, const std::initializer_list<Token::Type> &expected)
        : got(got), expected(expected)
    {
        std::stringstream ss;
        ss << "Got "
            << got.getTypeString()
            << ": "
            << got.value
            << ", "
            << "expected: {";

        for (auto exp: expected)
            ss << Token::getTypeString(exp) << ", ";

        ss << "}";

        str = ss.str();
    }

    ParserException(const ParserException &e) = default;
    ParserException(ParserException &&e) = default;

    // exception interface
    virtual const char *what() const noexcept override
    {
        return str.c_str();
    }

private:
    const Token &got;
    const std::initializer_list<Token::Type> &expected;
    std::string str;
};

#endif // PARSEREXCEPTION

