#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include "Parser.h"
#include "Lexer.h"
#include "ParserException.h"

Parser::Parser(std::wstringstream& str)
    : lexer(str)
{

}

Program Parser::parse() {
    return Program{
        begin(),
        declarations(),
        operations(),
        end(),
        varList
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
    if (token.type != Token::Type::BEGIN)
        throw ParserException(token, {Token::BEGIN});

    return new Node{token};
}

std::vector<Node *> Parser::declarations()
{
    std::vector<Node *> declarations;
    for (Node *node = declaration(); node; node = declaration()) {
        declarations.push_back(node);
    }

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
    case Token::END:
        // too far
        stepBack = true;
        return nullptr;
    default:
        throw ParserException(typeToken, {Token::ARRAY, Token::STRING, Token::LABEL, Token::END});
    }

    while (true) {
        Token operandToken = getNextToken();

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
    for (Node *node = operation(); node; node = operation()) {
        operations.push_back(node);
    }

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

    Token assignToken = getNextToken();
    if (assignToken.type != Token::Type::ASSIGN)
        throw ParserException(assignToken, {Token::ASSIGN});

    return new Node{variableToken, {expression()}};
}

Node *Parser::expression() {
    int priorityModifier = 0;
    bool isNegative = false; //for unary -
    bool lastTokenWasOperation = true;

    ExpNode *tree = nullptr;

    while (!stepBack) {
        Token token = getNextToken();

        switch (token.type) {
            case Token::LBRACE:
                priorityModifier += 10;
                break;
            case Token::RBRACE:
                priorityModifier -= 10;
                break;
            case Token::PLUS:
            case Token::MINUS:
            case Token::MULTIPLY:
            case Token::DIVIDE:
            case Token::POWER:
            case Token::AND:
            case Token::OR: {
                if (lastTokenWasOperation) { //it's unary -
                    isNegative = true;
                    break;
                }
                lastTokenWasOperation = true;

                ExpNode *node = new ExpNode();

                while (tree->parent != nullptr
                       && getPriority(token.type) + priorityModifier <= tree->parent->priority) {
                    tree = tree->parent;
                }

                node->left(tree);
                if (tree->parent != nullptr)
                    tree->parent->right(node);

                node->parent = tree->parent;
                tree->parent = node;

                tree = node;

                tree->token = token;
                tree->priority = getPriority(token.type) + priorityModifier;
                tree->type = Node::Type::OPERATION;
                break;
            }
        case Token::VARIABLE:
            if (std::find(varList.begin(), varList.end(), token.value) == varList.end())
                throw std::wstring(L"Неизвестная переменная: ") + token.value;
        case Token::NUMBER: {
            lastTokenWasOperation = false;

            ExpNode *node = new ExpNode();

            if (tree != nullptr)
                tree->right(node);

            node->parent = tree;
            tree = node;

            if (isNegative) {
                tree->isNegative = true;
                isNegative = false;
            }

            tree->token = token;
            tree->type = Node::Type::OPERAND;
            break;
        }
        default:
            stepBack = true;
            break;
        }
    }

    while (tree->parent != nullptr)
        tree = tree->parent;

    return tree;
}

int Parser::getPriority(Token::Type operation) {
    switch (operation) {
        case Token::PLUS:
        case Token::MINUS:
            return 0;
        case Token::MULTIPLY:
        case Token::DIVIDE:
            return 1;
        case Token::POWER:
            return 2;
        case Token::OR:
            return 3;
        case Token::AND:
            return 4;
        default:
            return -1;
    }
}

Node *Parser::end()
{
    stepBack = true;
    Token token = skipEmptyLines();
    if (token.type != Token::Type::END)
        throw ParserException(token, {Token::END});

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
