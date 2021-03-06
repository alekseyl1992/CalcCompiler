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
    std::wstringstream codeStream;
    std::wstring code = ui->codeEdit->document()->toPlainText().toStdWString();
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
            QStandardItem *varNameItem = new QStandardItem(
                        QString::fromStdWString(var.first));

            QStandardItem *varValueItem = new QStandardItem(
                        QString::fromStdString(to_hex_str(var.second)));

            varsModel->appendRow({varNameItem, varValueItem});
        }
        ui->varsTableView->repaint();
        ui->varsTableView->resizeColumnsToContents();

        ui->statusbar->showMessage("Выполнение завершёно успешно");

    }  catch (ParserExprException &e) {
        varsModel->clear();
        ui->varsTableView->repaint();

        ui->statusbar->showMessage(
                    QString("Ошибка: ")
                    + QString::fromStdWString(e.what()));

        // select error-substring
        auto endPos = e.getFrom();
        auto startPos = e.getTo();

        QTextCursor c = ui->codeEdit->textCursor();
        c.setPosition(startPos);
        c.setPosition(endPos, QTextCursor::KeepAnchor);
        ui->codeEdit->setTextCursor(c);
        ui->codeEdit->setFocus();
    } catch (ParserException &e) {
        varsModel->clear();
        ui->varsTableView->repaint();

        ui->statusbar->showMessage(
                    QString("Ошибка: ")
                    + QString::fromStdWString(e.what()));

        // select error-token
        const Token &token = e.getToken();
        auto endPos = token.pos;
        auto startPos = endPos - token.value.size();

        QTextCursor c = ui->codeEdit->textCursor();
        c.setPosition(startPos);
        c.setPosition(endPos, QTextCursor::KeepAnchor);
        ui->codeEdit->setTextCursor(c);
        ui->codeEdit->setFocus();

    } catch (std::wstring &e) {
        ui->statusbar->showMessage(
                    QString("Ошибка: ")
                    + QString::fromStdWString(e));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
