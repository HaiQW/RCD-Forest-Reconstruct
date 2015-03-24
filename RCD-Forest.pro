TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/data_process.cpp \
    src/file.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    header/data_struct.h \
    header/easylogging++.h \
    header/data_process.h \
    header/file.h \
    header/utility.h




