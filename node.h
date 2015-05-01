#ifndef NODE_H
#define NODE_H
#include "token.h"

struct Node {
    Token token;
    std::vector<Node*> operands;
};

#endif // NODE_H

