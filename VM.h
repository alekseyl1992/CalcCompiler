#ifndef VM_H
#define VM_H
#include <map>
#include <string>
#include "Program.h"

class VM
{
public:
    VM();
    std::map<std::wstring, double> execute(Program& program);

private:
    ExpNode *findExpRoot(Node *operation);
    void calculate(ExpNode *node);
    double evaluate(ExpNode *node);

    std::map<std::wstring, double> vars;
};

#endif // VM_H
