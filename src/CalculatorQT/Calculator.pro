QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Calc_C/SmartCalc_C.c \
    ../Calc_C/check.c \
    ../Calc_C/credit.c \
    ../Calc_C/deposit.c \
    ../Calc_C/stack.c \
    main.cpp \
    qcustomplot.cpp \
    mainwindow.cpp

HEADERS += \
    ../Calc_C/SmartCalc_C.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

ICON = icon.png

# QMAKE_CXXFLAGS += -Wa,-mbig-obj

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icon.PNG
