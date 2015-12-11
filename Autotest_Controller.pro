#-------------------------------------------------
#
# Project created by QtCreator 2015-12-08T20:01:41
#
#-------------------------------------------------

QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Autotest_Controller
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialogaddproject.cpp \
    dialogaddtest.cpp

HEADERS  += widget.h \
    connectdb.h \
    dialogaddproject.h \
    dialogaddtest.h

FORMS    += widget.ui \
    dialogaddproject.ui \
    dialogaddtest.ui
