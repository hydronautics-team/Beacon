QT += core network
QT += serialport

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        control.cpp \
        controlbeacon.cpp \
        hydroacoustics.cpp \
        json_parser.cpp \
        logger.cpp \
        main.cpp \
        nmea0183.cpp \
        protocol/protocol_bort.cpp \
        protocol/protocol_pc.cpp



HEADERS += \
    control.h \
    controlbeacon.h \
    hydroacoustics.h \
    json_parser.h \
    logger.h \
    nmea0183.h \
    protocol/pc_protocol.h \
    protocol/protocol.h \
    protocol/protocol_bort.h \
    protocol/protocol_pc.h \
    protocol/udp_protocol.h

DISTFILES +=


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
