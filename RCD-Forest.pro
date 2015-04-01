TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/data_process.cpp \
    src/file.cpp \
    src/ctree.cpp \
    src/cforest.cpp \
    src/kdd.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    header/data_struct.h \
    header/easylogging++.h \
    header/data_process.h \
    header/file.h \
    header/utility.h \
    header/ctree.h \
    header/assert.h \
    header/cforest.h \
    header/kdd.h

INCLUDEPATH += /usr/include/libxml2

#LIBS += -lmlpack
#LIBS += -larmadillo
#include(deployment.pri)
#qtcAddDeployment()

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../download/lib/release/ -lmlpack
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../download/lib/debug/ -lmlpack
else:unix: LIBS += -L$$PWD/../download/lib/ -lmlpack



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/include/release/ -larmadillo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/include/debug/ -larmadillo
else:unix: LIBS += -L$$PWD/../../../../../usr/include/ -larmadillo

INCLUDEPATH += $$PWD/../../../../../usr/include
DEPENDPATH += $$PWD/../../../../../usr/include
