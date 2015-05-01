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

    Node *begin();
    std::vector<Node*> declarations();
    std::vector<Node*> operations();
    Node *end();

private:
    Lexer lexer;
};

#endif // PARSER_H
