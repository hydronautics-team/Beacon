QT += core
QT += serialport

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        control.cpp \
        hydroacoustics.cpp \
        json_parser.cpp \
        logger.cpp \
        main.cpp \
        nmea0183.cpp



HEADERS += \
    control.h \
    hydroacoustics.h \
    json_parser.h \
    logger.h \
    nmea0183.h

DISTFILES +=


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
