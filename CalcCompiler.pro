#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T19:53:58
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = CalcCompiler
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp \
    Lexer.cpp \
    Parser.cpp \
    Compiler.cpp \
    VM.cpp \
    MainWindow.cpp

HEADERS += \
    Lexer.h \
    Parser.h \
    Compiler.h \
    VM.h \
    Program.h \
    Token.h \
    Node.h \
    ParserException.h \
    util.h \
    MainWindow.h

FORMS += \
    MainWindow.ui
