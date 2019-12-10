QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    console.cpp \
    exp/expcompound.cpp \
    exp/expconst.cpp \
    exp/expid.cpp \
    exp/expression.cpp \
    highlighter.cpp \
    interpreter.cpp \
    main.cpp \
    mainwindow.cpp \
    stat/statement.cpp \
    stat/statend.cpp \
    stat/statgoto.cpp \
    stat/statif.cpp \
    stat/statinput.cpp \
    stat/statlet.cpp \
    stat/statprint.cpp \
    stat/statrem.cpp \
    token.cpp

HEADERS += \
    console.h \
    exp/expcompound.h \
    exp/expconst.h \
    exp/expid.h \
    exp/expression.h \
    highlighter.h \
    interpreter.h \
    mainwindow.h \
    stat/statement.h \
    stat/statend.h \
    stat/statgoto.h \
    stat/statif.h \
    stat/statinput.h \
    stat/statlet.h \
    stat/statprint.h \
    stat/statrem.h \
    token.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
