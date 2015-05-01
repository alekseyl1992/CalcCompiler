#include <iostream>
#include "Compiler.h"
#include "VM.h"
#include "ParserException.h"

int main(int argc, char *argv[])
{
    std::stringstream code;
    code << R"(
            begin
            array a1 a2 a3
            string s1
            10: a1 = 10 + 2*5
            20: a2 = a1 + 10
            end
            )";


    try {
        Compiler compiler;
        Program program = compiler.compile(code);

        VM vm;
        vm.execute(program);
    } catch (ParserException &e) {
        std::cerr << e.what() << std::endl;
    }
}
