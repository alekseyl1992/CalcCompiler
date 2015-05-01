#include <iostream>
#include <chrono>
#include <thread>
#include "Parser.h"
#include "Lexer.h"

Parser::Parser(std::stringstream& str)
    : lexer(str)
{

}

Program Parser::parse() {
//    Token token;

//    do {
//        token = lexer.getNextToken();
//        std::cout << "Token: {" << token.type << ", " << token.value << "}" << std::endl;
////        using namespace std::literals;
////        std::this_thread::sleep_for(1s);
//    } while (token.type != Token::END);

    return Program{
        begin(),
        declarations(),
        operations(),
        end(),
    };
}

Node *Parser::begin()
{
    Token token = lexer.getNextToken();
    return new Node{token};
}

std::vector<Node *> Parser::declarations()
{
    return {};
}

std::vector<Node *> Parser::operations()
{
    return {};
}

Node *Parser::end()
{
    Token token = lexer.getNextToken();
    return new Node{token};
}
