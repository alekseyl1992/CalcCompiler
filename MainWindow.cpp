#include <iostream>
#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Compiler.h"
#include "VM.h"
#include "ParserException.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::onCompileClick() {
    std::stringstream code;
    code << R"(
            begin
            array a1 a2 a3
            string s1
            10: a1 = 10 + 2*5
            20: a2 = a1 + 10
            30: a3 = a2 + 0.1
            40: a4 = 1 || 0
            50: a5 = 1 && 0
            60: a6 = -1A
            70: a7 = -a6
            end
            )";


    try {
        std::cout << "Compiling..." << std::endl;
        Compiler compiler;
        Program program = compiler.compile(code);
        std::cout << "Compiled" << std::endl << std::endl;


        std::cout << "Executing..." << std::endl;
        VM vm;
        auto vars = vm.execute(program);

        for (auto &var: vars) {
            std::cout << var.first << " = " << to_hex_str(var.second) << std::endl;
        }

        std::cout << "Executed" << std::endl;

    } catch (ParserException &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::string &e) {
        std::cerr << e << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
