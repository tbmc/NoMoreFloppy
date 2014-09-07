TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    miniz.c \
    compress.cpp \
    Controller.cpp \
    ChristmasPacket.cpp \
    vueconsole.cpp

OTHER_FILES += \
    .gitignore

    INCLUDEPATH += "libs/SFML-2.1/include"

win32
{
    LIBS += -L"libs/SFML-2.1/vc64bits"
}

linux-g++
{
    equals(QMAKE_HOST.arch, "x86_64") {
        message("64 bits")
        LIBS += -L"libs/SFML-2.1/linuxgcc64bits"
    }
    equals(QMAKE_HOST.arch, "x86") {
        message("32 bits")
        LIBS += -L"libs/SFML-2.1/linuxgcc32bits"
    }

}
    LIBS += -lsfml-system
    LIBS += -lsfml-network

HEADERS += \
    compress.h \
    Controller.h \
    ChristmasPacket.h \
    vueconsole.h
