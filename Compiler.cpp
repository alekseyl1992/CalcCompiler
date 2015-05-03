#include "Compiler.h"
#include "Lexer.h"
#include "Parser.h"

Compiler::Compiler()
{

}

Program Compiler::compile(std::wstringstream &code)
{
    Parser parser(code);
    return parser.parse();
}

