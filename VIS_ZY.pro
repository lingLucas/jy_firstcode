QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cameramanager.cpp \
    camerause.cpp \
    hkcamera.cpp \
    imageprocess.cpp \
    imageview.cpp \
    loggerfunc.cpp \
    loggerworker.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cameramanager.h \
    camerause.h \
    hkcamera.h \
    imageprocess.h \
    imageview.h \
    loggerfunc.h \
    loggerworker.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += D:/alllib/opencv/build/include \
               "D:/soft/MVS/MVS/Development/Includes"

LIBS += -L"D:/alllib/opencv/build/x64/vc16/lib"
CONFIG(debug, debug|release) {
    LIBS += -lopencv_world4110d
} else {
    LIBS += -lopencv_world4110
}

LIBS += -L"D:/soft/MVS/MVS/Development/Libraries/win64" \
        -lMvCameraControl


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

QMAKE_PROJECT_DEPTH = 0
