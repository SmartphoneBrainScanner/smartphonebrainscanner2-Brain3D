# Add more folders to ship with the application, here
#folder_01.source = qml/sbs2brain3d
#folder_01.target = qml
#DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xEF0833B6
QT += opengl
QT += core 
QT += widgets
QT += network
QT += concurrent

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
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
