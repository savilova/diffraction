#-------------------------------------------------
#
# Project created by QtCreator 2017-05-12T20:40:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diffraction
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    cpp/demo_window.cpp \
    cpp/diff_system.cpp \
    cpp/main_window.cpp \
    cpp/obstacle.cpp \
    cpp/single_slit.cpp \
    cpp/temp_setting.cpp

HEADERS  += \
    h/demo_window.h \
    h/diff_system.h \
    h/main_window.h \
    h/obstacle.h \
    h/single_slit.h \
    h/temp_setting.h

FORMS    += \
    graphics/demo_window.ui \
    graphics/main_window.ui \
    graphics/temp_setting.ui

RC_ICONS = img\icon.ico


INCLUDEPATH += H:\opencv-build\install\include
LIBS += -LH:\opencv-build\install\x86\mingw\lib \
    -lopencv_core320.dll \
    -lopencv_highgui320.dll \
    -lopencv_imgcodecs320.dll \
    -lopencv_imgproc320.dll \
    -lopencv_features2d320.dll \
    -lopencv_calib3d320.dll \


DISTFILES += \
    diffraction.pro.user \
    img\scheme.jpg \
    img\icon.ico \
    README.md \
