
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
    infomationmanagerofserialnumber.h
SOURCES       = cell.cpp \
                finddialog.cpp \
                gotocelldialog.cpp \
                main.cpp \
                mainwindow.cpp \
                sortdialog.cpp \
                spreadsheet.cpp \
                scanworkpiecedialog.cpp \
    setdatabaseandtabledialog.cpp \
    infomationmanagerofserialnumber.cpp
FORMS         = gotocelldialog.ui \
                sortdialog.ui     \
                scanworkpiecedialog.ui \
    setdatabaseandtabledialog.ui
RESOURCES     = spreadsheet.qrc
