#ifndef NODE_H
#define NODE_H
#include <string>
#include <assert.h>
#include "token.h"

struct Node {
    enum Type {
        NONE, OPERATION, OPERAND
    };

    Token token = {Token::TOKEN_TYPES_COUNT, ""};
    std::vector<Node *> operands;
    Type type = NONE;

    Node(Token token=Token(), std::vector<Node *> operands={}, Type type=NONE)
        : token(token), operands(operands), type(type) {

    }

    virtual bool isLeaf() {
        return operands.size() == 0;
    }
};

struct ExpNode : public Node {
    ExpNode() : Node() {
        operands.resize(2);  //left and right children
	operands[0] = nullptr;
	operands[1] = nullptr;
    }

    ExpNode *left() {
	assert(operands.size() == 2);
        return (ExpNode *) operands[0];
    }

    void left(Node *p) {
	assert(operands.size() == 2);
        operands[0] = p;
    }

    ExpNode *right() {
	assert(operands.size() == 2);
        return (ExpNode *) operands[1];
    }

    void right(Node *p) {
	assert(operands.size() == 2);
        operands[1] = p;
    }

    virtual bool isLeaf() override {
	assert(operands.size() == 2);
        return operands[0] == nullptr && operands[1] == nullptr;
    }

    ExpNode *parent = nullptr;
    int priority = 0;
    double value = 0;
    bool isNegative = false;
};

#endif // NODE_H

