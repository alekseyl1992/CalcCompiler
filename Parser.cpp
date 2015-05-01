#include <iostream>
#include <chrono>
#include <thread>
#include "Parser.h"
#include "Lexer.h"
#include "ParserException.h"

Parser::Parser(std::stringstream& str)
    : lexer(str)
{

}

Program Parser::parse() {
    return Program{
        begin(),
        declarations(),
        operations(),
        end(),
    };
}

Token Parser::skipEmptyLines()
{
    Token token;
    while ((token = getNextToken()).type == Token::LINE_BREAK)
    { }

    return token;
}

Node *Parser::begin()
{
    Token token = skipEmptyLines();

    return new Node{token};
}

std::vector<Node *> Parser::declarations()
{
    std::vector<Node *> declarations;
    Node *node = declaration();
    do {
        declarations.push_back(node);
        node = declaration();
    } while (node);

    return declarations;
}

Node *Parser::declaration()
{
    Node *node = new Node();

    Token typeToken = skipEmptyLines();
    switch (typeToken.type) {
    case Token::ARRAY:
    case Token::STRING:
        node->token = typeToken;
        break;
    case Token::LABEL:
        // too far
        stepBack = true;
        return nullptr;
    default:
        throw ParserException(typeToken, {Token::ARRAY, Token::STRING, Token::LABEL});
    }

    while (true) {
        Token operandToken = lexer.getNextToken();

        switch (operandToken.type) {
        case Token::VARIABLE:
            node->operands.push_back(new Node{operandToken});
            break;
        case Token::LINE_BREAK:
            return node;
        default:
            throw ParserException(operandToken, {Token::VARIABLE, Token::LINE_BREAK});
        }
    }
}

std::vector<Node *> Parser::operations()
{
    std::vector<Node *> operations;
    Node *node = operation();
    do {
        operations.push_back(node);
        node = operation();
    } while (node);

    return operations;
}

Node *Parser::operation()
{
    Token labelToken = skipEmptyLines();
    switch (labelToken.type) {
    case Token::LABEL:
        break;
    case Token::END:
        return nullptr;
    default:
        throw ParserException(labelToken, {Token::LABEL, Token::END});
    }

    Node *node = new Node{
        labelToken, {variable()}
    };

    return node;
}

Node *Parser::variable() {
    Token variableToken = getNextToken();
    switch (variableToken.type) {
    case Token::VARIABLE:
        varList.push_back(variableToken.value);
        break;
    default:
        throw ParserException(variableToken, {Token::VARIABLE});
    }

    return new Node{variableToken, {expression()}};
}

Node *Parser::expression() {
    //TODO: build actual expr tree
    return nullptr;
}

Node *Parser::end()
{
    Token token = getNextToken();
    return new Node{token};
}

Token Parser::getNextToken()
{
    if (stepBack) {
        stepBack = false;
        return prevToken;
    } else {
        prevToken = lexer.getNextToken();
        return prevToken;
    }
}
