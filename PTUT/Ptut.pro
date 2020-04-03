TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Node.cpp \
        Proposal.cpp \
        Tree.cpp \
        infix2postfix.cpp \
        main.cpp

HEADERS += \
    Proposal.h \
    Node.h \
    Tree.h
