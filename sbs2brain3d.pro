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

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

include(../smartphonebrainscanner2-core/src/sbs2_binary_decryptor.pri)

HEADERS += \
    colordata.h \
    mainwindow.h \
    glwidget.h \
    glm.h \
    model.h \
    mycallback.h


RESOURCES += \
    resources.qrc


INCLUDEPATH += $$PWD/../decryptor_libraries
DEPENDPATH += $$PWD/../decryptor_libraries

macx: LIBS += -L$$PWD/../decryptor_libraries/ -lsbs2emotivdecryptor
android: LIBS += -L$$PWD/../decryptor_libraries/ -lsbs2emotivdecryptor_android
linux-g++-64: LIBS += -L$$PWD/../decryptor_libraries/ -lsbs2emotivdecryptor_linux-g++-64

macx: PRE_TARGETDEPS += $$PWD/../decryptor_libraries/libsbs2emotivdecryptor.a
android: PRE_TARGETDEPS += $$PWD/../decryptor_libraries/libsbs2emotivdecryptor_android.a
linux-g++-64: PRE_TARGETDEPS += $$PWD/../decryptor_libraries/libsbs2emotivdecryptor_linux-g++-64.a


OTHER_FILES += \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/values-es/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/layout/splash.xml \
    android/res/values/strings.xml \
    android/res/values/libs.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/drawable-mdpi/icon.png \
    android/res/values-nl/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable/icon.png \
    android/res/values-ja/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-pl/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/version.xml \
    android/AndroidManifest.xml \
    android/res/layout/splash.xml \
    android/res/values/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/version.xml \
    android/AndroidManifest.xml \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values/libs.xml \
    android/res/values-de/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/drawable-mdpi/icon.png \
    android/res/values-es/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-fr/strings.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable/icon.png \
    android/res/values-ja/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/drawable-ldpi/icon.png \
    android/version.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/AndroidManifest.xml

