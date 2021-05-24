QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = AstraP.pro

CONFIG += c++11
CONFIG   += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    captation.cpp \
    demarrage.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
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

DISTFILES += \
    ../base_images/WIN_20210401_11_11_25_Pro.jpg \
    ../base_images/WIN_20210401_11_12_10_Pro.jpg \
    ../base_images/WIN_20210401_11_12_13_Pro.jpg \
    ../base_images/WIN_20210401_11_12_16_Pro.jpg \
    ../base_images/WIN_20210401_11_12_18_Pro.jpg \
    ../base_images/WIN_20210401_11_12_27_Pro.jpg \
    ../base_images/WIN_20210401_11_12_29_Pro.jpg \
    ../base_images/WIN_20210401_11_12_31_Pro.jpg \
    ../base_images/WIN_20210401_11_12_38_Pro.jpg \
    ../base_images/WIN_20210401_11_12_40_Pro.jpg \
    ../base_images/WIN_20210401_11_12_43_Pro.jpg \
    ../base_images/WIN_20210401_11_12_45_Pro.jpg \
    ../base_images/WIN_20210401_11_12_47_Pro.jpg \
    ../base_images/WIN_20210401_11_12_50_Pro.jpg \
    ../base_images/WIN_20210401_11_12_52_Pro.jpg \
    ../base_images/WIN_20210401_11_12_56_Pro.jpg \
    ../base_images/WIN_20210401_11_13_39_Pro.jpg \
    ../base_images/WIN_20210401_11_13_42_Pro.jpg \
    ../base_images/WIN_20210401_11_13_45_Pro.jpg \
    ../base_images/WIN_20210401_11_13_51_Pro.jpg \
    ../base_images/WIN_20210401_11_13_54_Pro.jpg \
    ../base_images/WIN_20210401_11_14_45_Pro.jpg \
    ../base_images/WIN_20210401_11_14_53_Pro.jpg \
    ../base_images/WIN_20210401_11_14_56_Pro.jpg \
    ../base_images/WIN_20210401_11_14_59_Pro.jpg \
    ../base_images/WIN_20210401_11_15_04_Pro.jpg \
    ../base_images/WIN_20210401_11_15_07_Pro.jpg \
    ../base_images/WIN_20210401_11_15_10_Pro.jpg \
    ../base_images/WIN_20210401_11_15_12_Pro.jpg \
    ../base_images/WIN_20210401_11_15_14_Pro.jpg \
    ../base_images/WIN_20210401_11_15_16_Pro.jpg \
    ../base_images/WIN_20210401_11_16_20_Pro.jpg \
    ../base_images/WIN_20210401_11_16_22_Pro.jpg \
    ../base_images/WIN_20210401_11_16_28_Pro.jpg \
    ../base_images/WIN_20210401_11_16_31_Pro.jpg \
    ../base_images/WIN_20210401_11_16_35_Pro.jpg \
    ../base_images/WIN_20210401_11_16_36_Pro.jpg \
    ../base_images/WIN_20210401_11_16_38_Pro.jpg \
    ../base_images/WIN_20210401_11_16_41_Pro.jpg \
    ../base_images/WIN_20210401_11_16_47_Pro.jpg \
    ../base_images/WIN_20210401_11_16_49_Pro.jpg \
    ../base_images/WIN_20210401_11_16_51_Pro.jpg \
    ../base_images/WIN_20210401_11_16_53_Pro.jpg \
    ../base_images/WIN_20210401_11_16_55_Pro.jpg \
    ../base_images/WIN_20210401_11_16_56_Pro.jpg \
    ../base_images/WIN_20210401_11_16_58_Pro.jpg \
    ../base_images/WIN_20210401_11_17_00_Pro.jpg \
    ../base_images/WIN_20210401_11_17_02_Pro.jpg \
    ../base_images/WIN_20210401_11_17_06_Pro.jpg \
    ../base_images/WIN_20210401_11_17_10_Pro.jpg \
    ../base_images/WIN_20210401_11_17_27_Pro.jpg \
    ../base_images/WIN_20210401_11_17_29_Pro.jpg \
    ../base_images/WIN_20210401_11_17_31_Pro.jpg \
    ../base_images/WIN_20210401_11_17_33_Pro.jpg \
    ../base_images/WIN_20210401_11_17_34_Pro.jpg \
    ../base_images/WIN_20210401_11_17_37_Pro.jpg \
    ../base_images/WIN_20210401_11_17_39_Pro.jpg \
    ../base_images/WIN_20210401_11_17_40_Pro.jpg \
    ../base_images/WIN_20210401_11_17_41_Pro.jpg \
    ../base_images/WIN_20210401_11_17_43_Pro.jpg \
    ../base_images/WIN_20210401_11_17_44_Pro.jpg \
    ../base_images/WIN_20210401_11_17_46_Pro.jpg \
    ../base_images/WIN_20210401_11_17_48_Pro.jpg \
    ../base_images/WIN_20210401_11_17_50_Pro.jpg \
    ../base_images/WIN_20210401_11_17_52_Pro.jpg \
    ../base_images/WIN_20210401_11_17_54_Pro.jpg \
    ../base_images/WIN_20210401_11_17_57_Pro.jpg \
    ../base_images/WIN_20210401_11_18_00_Pro.jpg \
    ../base_images/WIN_20210401_11_18_02_Pro.jpg \
    ../base_images/WIN_20210401_11_18_03_Pro.jpg \
    ../base_images/WIN_20210401_11_19_03_Pro.jpg \
    ../base_images/WIN_20210401_11_19_09_Pro.jpg \
    ../base_images/WIN_20210401_11_19_12_Pro.jpg \
    ../base_images/WIN_20210401_11_19_14_Pro.jpg \
    ../base_images/WIN_20210401_11_19_16_Pro.jpg \
    ../base_images/WIN_20210401_11_19_17_Pro.jpg \
    ../base_images/WIN_20210401_11_19_18_Pro.jpg \
    ../base_images/WIN_20210401_11_19_20_Pro.jpg \
    ../base_images/WIN_20210401_11_19_21_Pro.jpg \
    ../base_images/WIN_20210401_11_19_22_Pro.jpg \
    ../base_images/WIN_20210401_11_19_23_Pro.jpg \
    ../base_images/WIN_20210401_11_19_24_Pro.jpg \
    ../base_images/WIN_20210401_11_19_25_Pro.jpg \
    ../base_images/WIN_20210401_11_19_26_Pro.jpg \
    ../base_images/WIN_20210401_11_19_27_Pro.jpg \
    ../base_images/WIN_20210401_11_19_29_Pro.jpg \
    ../base_images/WIN_20210401_11_19_50_Pro.jpg \
    ../base_images/WIN_20210401_11_19_51_Pro.jpg \
    ../base_images/WIN_20210401_11_19_54_Pro.jpg \
    ../base_images/WIN_20210401_11_19_56_Pro.jpg \
    ../base_images/WIN_20210401_11_19_58_Pro.jpg \
    ../base_images/WIN_20210401_11_19_59_Pro.jpg \
    ../base_images/WIN_20210401_11_20_00_Pro.jpg \
    ../base_images/WIN_20210401_11_20_02_Pro.jpg \
    ../base_images/WIN_20210401_11_20_04_Pro.jpg \
    ../base_images/WIN_20210401_11_20_06_Pro.jpg \
    ../base_images/WIN_20210401_11_20_08_Pro.jpg \
    ../base_images/WIN_20210401_11_20_09_Pro.jpg \
    ../base_images/WIN_20210401_11_20_11_Pro.jpg \
    ../base_images/WIN_20210401_11_20_41_Pro.jpg \
    ../base_images/WIN_20210401_11_20_44_Pro.jpg \
    ../base_images/WIN_20210401_11_20_46_Pro.jpg \
    ../base_images/WIN_20210401_11_20_55_Pro.jpg \
    ../base_images/WIN_20210401_11_20_56_Pro.jpg \
    ../base_images/WIN_20210401_11_20_57_Pro.jpg \
    ../base_images/WIN_20210401_11_20_58_Pro.jpg \
    ../base_images/WIN_20210401_11_20_59_Pro.jpg \
    ../base_images/WIN_20210401_11_20_60_Pro.jpg \
    ../base_images/WIN_20210401_11_21_38_Pro.mp4

