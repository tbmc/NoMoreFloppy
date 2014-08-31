TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    miniz.c \
    compress.cpp

OTHER_FILES += \
    .gitignore

    INCLUDEPATH += "libs/SFML-2.1/include"

win32
{
    equals(QMAKE_HOST.arch, "x86")
    {
        LIBS += -L"libs/SFML-2.1/vc32bits"
    }

    equals(QMAKE_HOST.arch, "x86_64")
    {
        LIBS += -L"libs/SFML-2.1/vc64bits"
    }
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
    compress.h
