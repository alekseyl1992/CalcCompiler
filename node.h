#ifndef NODE_H
#define NODE_H
#include <string>
#include "token.h"

struct Node {
    enum Type {
        NONE, OPERATION, OPERAND
    };

    Token token;
    std::vector<Node *> operands;
    Type type;

    Node(Token token=Token(), std::vector<Node *> operands={}, Type type=NONE)
        : token(token), operands(operands), type(type) {

    }

    virtual bool isLeaf() {
        return operands.size() == 0;
    }
};

struct ExpNode : public Node {
    ExpNode() {
        operands.resize(2);  //left and right children
    }

    ExpNode *left() {
        return (ExpNode *) operands[0];
    }

    void left(Node *p) {
        operands[0] = p;
    }

    ExpNode *right() {
        return (ExpNode *) operands[1];
    }

    void right(Node *p) {
        operands[1] = p;
    }

    virtual bool isLeaf() override {
        return operands[0] == nullptr && operands[1] == nullptr;
    }

    ExpNode *parent;
    int priority;
    double value = 0;
    bool isNegative = false;
};

#endif // NODE_H

