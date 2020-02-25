TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Node.cpp \
        Proposition.cpp \
        Tree.cpp \
        infix2postfix.cpp \
        main.cpp

HEADERS += \
    Node.h \
    Proposition.h \
    Tree.h
