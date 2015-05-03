#ifndef COMPILER_H
#define COMPILER_H

#include <sstream>
#include "Parser.h"
#include "Program.h"

class Compiler
{
public:
    Compiler();

    Program compile(std::wstringstream &code);

private:
};

#endif // COMPILER_H
