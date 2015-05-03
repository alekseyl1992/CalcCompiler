#ifndef LEXER_H
#define LEXER_H
#include <sstream>
#include <vector>
#include <string>
#include <QRegExp>
#include <QString>
#include <locale>
#include "Token.h"

class Lexer
{
public:
    Lexer(std::wstringstream &str);

    Token getNextToken();

private:
    bool tryAppend(std::wstring &value, wchar_t ch);

    std::wstringstream &str;

    struct Domain {
        Token::Type type;

        QRegExp regex;
        std::wstring exact;
        bool isRegex;

        Domain(Token::Type type, std::wstring value, bool isRegex=false)
            : type(type), isRegex(isRegex) {
            if (isRegex)
                regex = QRegExp(QString::fromStdWString(value));
            else
                exact = value;
        }

        bool match(std::wstring str, bool full=false) {
            if (isRegex) {
                return regex.exactMatch(QString::fromStdWString(str));
            }
            else if (full)
                return exact == str;
            else
                return exact.find(str) == 0;
        }
    };

    std::vector<Domain> domains = {
        Domain(Token::BEGIN,         L"начало"),
        Domain(Token::END,           L"окончание"),
        Domain(Token::ARRAY,         L"массив"),
        Domain(Token::STRING,        L"строка"),
        Domain(Token::LINE_BREAK,    L"\n"),
        Domain(Token::NUMBER,        L"([0-9A-F]|\\.)+", true),
        Domain(Token::VARIABLE,      L"[а-я]\\d{0,3}", true),
        Domain(Token::ASSIGN,        L"="),
        Domain(Token::LABEL,         L"(\\d)+\\:", true),
        Domain(Token::PLUS,          L"+"),
        Domain(Token::MINUS,         L"-"),
        Domain(Token::MULTIPLY,      L"*"),
        Domain(Token::DIVIDE,        L"/"),
        Domain(Token::AND,           L"&"),
        Domain(Token::OR,            L"|"),
        Domain(Token::LBRACE,        L"("),
        Domain(Token::RBRACE,        L")")
    };
};

#endif // LEXER_H
