QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = AstraP.pro

CONFIG += c++11
CONFIG   += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Utils-master/utils.cpp \
    captation.cpp \
    demarrage.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../Utils-master/utils.h \
    captation.h \
    demarrage.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core451 \
    -lopencv_highgui451 \
    -lopencv_imgproc451 \
    -lopencv_imgcodecs451 \
    -lopencv_videoio451 \
    -lopencv_features2d451 \
    -lopencv_calib3d451

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

