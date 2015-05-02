#include "VM.h"
#include <cmath>

VM::VM() {

}

std::map<std::string, double> VM::execute(Program &program) {
    auto operations = program.operations;
    for (auto &operation: operations) {
        ExpNode *root = findExpRoot(operation);
        calculate(root);

        vars[operation->operands[0]->token.value] = root->value;
    }

    return vars;
}

ExpNode *VM::findExpRoot(Node *operation) {
    return (ExpNode *) operation->operands[0]->operands[0];
}

void VM::calculate(ExpNode *node) {
    if (node->left() != nullptr && !node->left()->isLeaf())
        calculate(node->left());
    if (node->right() != nullptr && !node->right()->isLeaf())
        calculate(node->right());

    switch (node->token.type) {
    case Token::Type::PLUS:
        node->value = evaluate(node->left()) + evaluate(node->right());
        break;
    case Token::Type::MINUS:
        node->value = evaluate(node->left()) - evaluate(node->right());
        break;
    case Token::Type::MULTIPLY:
        node->value = evaluate(node->left()) * evaluate(node->right());
        break;
    case Token::Type::DIVIDE:
        node->value = evaluate(node->left()) / evaluate(node->right());
        break;
    case Token::Type::POWER:
        node->value = std::pow(evaluate(node->left()), evaluate(node->right()));
        break;
    case Token::Type::AND:
        node->value = evaluate(node->left()) && evaluate(node->right());
        break;
    case Token::Type::OR:
        node->value = evaluate(node->left()) || evaluate(node->right());
        break;
    case Token::Type::VARIABLE:
    case Token::Type::NUMBER:
        node->value = evaluate(node);
    }
}

double VM::evaluate(ExpNode *node) {
    if (node->token.type == Token::VARIABLE) {
        auto var = vars.find(node->token.value);
        if (var != vars.end()) {
            if (node->isNegative) {
                node->value = -var->second;
            }

            return node->value;
        }

        if (node->isNegative)
            return -node->value;
        else
            return node->value;
    } else if (node->token.type == Token::NUMBER) {
        node->value = std::stod(std::string("0x") + node->token.value);
        if (node->isNegative)
            node->value = -node->value;


        return node->value;
    } else {
        // already evaluated from childs
        return node->value;
    }
}
