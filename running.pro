QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barrier.cpp \
    character.cpp \
    feibiao.cpp \
    gamesence.cpp \
    main.cpp \
    mainwindow.cpp \
    startscence.cpp

HEADERS += \
    barrier.h \
    character.h \
    feibiao.h \
    gamesence.h \
    mainwindow.h \
    startscence.h

FORMS += \
    mainwindow.ui \
    startscence.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    res/attack/fei_biao/Suriken1.png \
    res/attack/fei_biao/Suriken2.png \
    res/attack/fei_biao/Suriken3.png \
    res/attack/fei_biao/Suriken4.png \
    res/attack/fei_biao/Suriken5.png \
    res/attack/fei_biao/Suriken6.png \
    res/attack/fei_biao/Suriken7.png \
    res/attack/fei_biao/Suriken8.png \
    res/startscence/startbg.png
