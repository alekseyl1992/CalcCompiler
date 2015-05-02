#ifndef PROGRAM_H
#define PROGRAM_H
#include <vector>
#include "node.h"

struct Program
{
    Node *begin;
    std::vector<Node*> declarations;
    std::vector<Node*> operations;
    Node *end;
    std::vector<std::string> varList;
};

#endif // PROGRAM_H
