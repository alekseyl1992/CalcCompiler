#ifndef VM_H
#define VM_H
#include "Program.h"

class VM
{
public:
    VM();
    void execute(const Program& program);
};

#endif // VM_H
