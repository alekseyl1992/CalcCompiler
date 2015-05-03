#include <iostream>
#include <QtWidgets/QPushButton>
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
    QObject::connect(ui->compileButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onCompileClick);

    varsModel = new QStandardItemModel(this);
    ui->varsTableView->setModel(varsModel);

    ui->statusbar->showMessage("Готово");
}

void MainWindow::onCompileClick() {
    std::stringstream codeStream;
    std::string code = ui->codeEdit->document()->toPlainText().toUtf8().toStdString();
    codeStream << code;

    try {
        ui->statusbar->showMessage("Компиляция...");
        Compiler compiler;
        Program program = compiler.compile(codeStream);
        ui->statusbar->showMessage("Компиляция завершена");


        ui->statusbar->showMessage("Выполнение...");
        VM vm;
        auto vars = vm.execute(program);

        varsModel->clear();
        varsModel->setHorizontalHeaderLabels({"Переменная", "Значение"});
        for (auto &var: vars) {
            QStandardItem *varNameItem = new QStandardItem(var.first.c_str());
            QStandardItem *varValueItem = new QStandardItem(to_hex_str(var.second).c_str());

            varsModel->appendRow({varNameItem, varValueItem});
        }
        ui->varsTableView->repaint();

        ui->statusbar->showMessage("Выполнение завершёно успешно");

    } catch (ParserException &e) {
        ui->statusbar->showMessage(QString("Синтаксическая ошибка: ") + e.what());
    } catch (std::string &e) {
        ui->statusbar->showMessage(QString("Синтаксическая ошибка: ") + e.c_str());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
