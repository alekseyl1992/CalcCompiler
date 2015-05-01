#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <sstream>
#include "Node.h"
#include "Program.h"
#include "Lexer.h"

class Parser
{
public:
    Parser(std::stringstream& str);

    Program parse();

    Token skipEmptyLines();

    Node *begin();
    std::vector<Node*> declarations();
    Node *declaration();

    std::vector<Node*> operations();
    Node *operation();
    Node *variable();
    Node *expression();

    Node *end();

private:
    Token getNextToken();

    Token prevToken;
    bool stepBack = false;

    Lexer lexer;
    std::vector<std::string> varList;
};

#endif // PARSER_H
