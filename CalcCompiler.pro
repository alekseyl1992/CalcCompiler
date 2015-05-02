#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T19:53:58
#
#-------------------------------------------------

QT       -= gui
QMAKE_CXXFLAGS += -std=c++14

TARGET = CalcCompiler
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Lexer.cpp \
    Parser.cpp \
    Compiler.cpp \
    VM.cpp

HEADERS += \
    Lexer.h \
    Parser.h \
    Compiler.h \
    VM.h \
    Program.h \
    Token.h \
    Node.h \
    ParserException.h \
    util.h
