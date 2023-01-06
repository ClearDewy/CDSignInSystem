QT       += core gui sql



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountwnd.cpp \
    backend.cpp \
    getdata.cpp \
    homewnd.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    sql.cpp \
    timewnd.cpp \
    train.cpp \
    user.cpp \
    userwnd.cpp

HEADERS += \
    accountwnd.h \
    homewnd.h \
    login.h \
    mainwindow.h \
    backend.h \
    getdata.h \
    sql.h \
    timewnd.h \
    train.h \
    user.h \
    userwnd.h

FORMS += \
    accountwnd.ui \
    homewnd.ui \
    login.ui \
    mainwindow.ui \
    backend.ui \
    getdata.ui \
    timewnd.ui \
    userwnd.ui

INCLUDEPATH += D:\Environment\OpenCV\include
LIBS += D:\Environment\OpenCV\x64\mingw\lib\libopencv_*.a


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

