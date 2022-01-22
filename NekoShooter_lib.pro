QT += widgets

TEMPLATE = lib
DEFINES += NEKOSHOOTER_LIB_LIBRARY

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
INCLUDEPATH += Colori \ Giti \ Karta \ Ansky \
    Colori/ColoriCore \
    Colori/ColoriColor \
    Giti/GitiCore \
    Karta/KartaCore \
    Karta/KartaMecanismo \
    Ansky/AnskyCore \
    Ansky/AnskyTrazo


SOURCES += \
    Ansky/AnskyCore/AnskyEsenciales.cpp \
    Ansky/AnskyCore/anskybasic.cpp \
    Ansky/AnskyCore/anskymath.cpp \
    Ansky/AnskyTrazo/anskytrazo.cpp \
    Ansky/AnskyUtiles/AnskyBG.cpp \
    Ansky/AnskyUtiles/AnskyShorts.cpp \
    Ansky/AnskyUtiles/AnskyTrazado.cpp \
    Colori/ColoriCore/ColoriBasic.c \
    Colori/ColoriColor/ColoriColor.cpp \
    Colori/ColoriCore/ColoriMath.c \
    Colori/ColoriColor/ColoriRGB.cpp \
    Colori/ColoriCore/Colori__rgb__.c \
    Colori/ColoriUtiles/ColoriUtiles.c \
    Giti/GitiCore/GitiBits.c \
    Karta/KartaCore/kartacoor.cpp \
    Karta/KartaCore/kartamath.cpp \
    Karta/KartaMecanismo/KSonda.cpp \
    Karta/KartaMecanismo/kcelda.cpp

HEADERS += \
    Ansky/AnskyCore/AnskyEsenciales.h \
    Ansky/AnskyCore/anskybasic.h \
    Ansky/AnskyCore/anskymath.h \
    Ansky/AnskyTrazo/anskytrazo.h \
    Ansky/AnskyUtiles/AnskyBG.h \
    Ansky/AnskyUtiles/AnskyShorts.h \
    Ansky/AnskyUtiles/AnskyTrazado.h \
    Colori/ColoriCore/ColoriBasic.h \
    Colori/ColoriColor/ColoriColor.h \
    Colori/ColoriCore/ColoriMath.h \
    Colori/ColoriColor/ColoriRGB.h \
    Colori/ColoriCore/Colori__rgb__.h \
    Colori/ColoriCore/__COLORICONST__.h \
    Colori/ColoriUtiles/ColoriUtiles.h \
    Giti/GitiCore/GitiBits.h \
    Giti/GitiCore/__GITICONST__.h \
    Karta/KartaCore/__KARTACONST__.h \
    Karta/KartaCore/kartacoor.h \
    Karta/KartaCore/kartamath.h \
    Karta/KartaMecanismo/KSonda.h \
    Karta/KartaMecanismo/kcelda.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
