
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE      = app
HEADERS       = cell.h \
                finddialog.h \
                gotocelldialog.h \
                mainwindow.h \
                sortdialog.h \
                spreadsheet.h \
                scanworkpiecedialog.h \
    setdatabaseandtabledialog.h \
    infomationmanagerofserialnumber.h \
    getdatafrommysqldialog.h \
    generateqrcodedialog.h \
    qrencode.h \
    qrencodepri.h \
    qrencodepublic.h
SOURCES       = cell.cpp \
                finddialog.cpp \
                gotocelldialog.cpp \
                main.cpp \
                mainwindow.cpp \
                sortdialog.cpp \
                spreadsheet.cpp \
                scanworkpiecedialog.cpp \
    setdatabaseandtabledialog.cpp \
    infomationmanagerofserialnumber.cpp \
    getdatafrommysqldialog.cpp \
    generateqrcodedialog.cpp \
    qrencodepri.cpp \
    qrencodepublic.cpp
FORMS         = gotocelldialog.ui \
                sortdialog.ui     \
                scanworkpiecedialog.ui \
    setdatabaseandtabledialog.ui \
    getdatafrommysqldialog.ui \
    generateqrcodedialog.ui
RESOURCES     = spreadsheet.qrc

LIBS += -LE:/temp/ -lqrencode
