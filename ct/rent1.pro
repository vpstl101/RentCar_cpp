QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    carsearch.cpp \
    chat.cpp \
    join.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    myinfo.cpp \
    pay.cpp \
    reservasion.cpp \
    reservasion_add.cpp \
    reservasion_edit.cpp \
    trip.cpp \
    withdraw.cpp

HEADERS += \
    carsearch.h \
    chat.h \
    database.h \
    join.h \
    mainwindow.h \
    menu.h \
    myinfo.h \
    pay.h \
    reservasion.h \
    reservasion_add.h \
    reservasion_edit.h \
    trip.h \
    withdraw.h

FORMS += \
    carsearch.ui \
    chat.ui \
    join.ui \
    mainwindow.ui \
    menu.ui \
    myinfo.ui \
    pay.ui \
    reservasion.ui \
    reservasion_add.ui \
    reservasion_edit.ui \
    trip.ui \
    withdraw.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
