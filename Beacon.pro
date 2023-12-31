QT += core network \
    widgets
QT += serialport
QT += core gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controlbeacon.cpp \
        hydroacoustics.cpp \
        json_parser.cpp \
        logger.cpp \
        main.cpp \
        nmea0183.cpp \
        protocol/protocol_bort.cpp \
        protocol/protocol_pc.cpp \
        widget.cpp



HEADERS += \
    controlbeacon.h \
    hydroacoustics.h \
    json_parser.h \
    logger.h \
    nmea0183.h \
    protocol/pc_protocol.h \
    protocol/protocol.h \
    protocol/protocol_bort.h \
    protocol/protocol_pc.h \
    protocol/udp_protocol.h \
    widget.h

DISTFILES +=

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
