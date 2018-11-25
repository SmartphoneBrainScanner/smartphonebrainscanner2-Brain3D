QT += opengl
QT += core 
QT += widgets
QT += network
QT += concurrent

SOURCES += main.cpp \
    mainwindow.cpp \
    glwidget.cpp \
    glm.cpp \
    model.cpp \
    mycallback.cpp

include(../smartphonebrainscanner2-core/src/sbs2.pri)

HEADERS += \
    colordata.h \
    mainwindow.h \
    glwidget.h \
    glm.h \
    model.h \
    mycallback.h


RESOURCES += \
    resources.qrc

win32:LIBS += opengl32.lib
target.path = /bin/
INSTALLS += target
win32:RC_ICONS += brain.ico
