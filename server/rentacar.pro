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
    car.cpp \
    car_edit.cpp \
    chatting.cpp \
    main.cpp \
    mainwindow.cpp \
    member_add.cpp \
    member_edit.cpp \
    memberlist.cpp \
    payment.cpp \
    reserv_add.cpp \
    reserv_edit.cpp \
    reservation.cpp \
    server.cpp \
    sight.cpp \
    sight_add.cpp \
    sight_edit.cpp \
    thread.cpp

HEADERS += \
    car.h \
    car_edit.h \
    chatting.h \
    database.h \
    mainwindow.h \
    member_add.h \
    member_edit.h \
    memberlist.h \
    payment.h \
    reserv_add.h \
    reserv_edit.h \
    reservation.h \
    server.h \
    sight.h \
    sight_add.h \
    sight_edit.h \
    thread.h

FORMS += \
    car.ui \
    car_edit.ui \
    chatting.ui \
    mainwindow.ui \
    member_add.ui \
    member_edit.ui \
    memberlist.ui \
    payment.ui \
    reserv_add.ui \
    reserv_edit.ui \
    reservation.ui \
    sight.ui \
    sight_add.ui \
    sight_edit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
