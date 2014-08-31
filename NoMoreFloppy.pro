TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

OTHER_FILES += \
    .gitignore

    INCLUDEPATH += "libs/SFML-2.1/include"

win32
{
    !contains(QMAKE_HOST.arch, x86_64)
    {
        LIBS += -L"libs/SFML-2.1/vc32bits"
    }

    contains(QMAKE_HOST.arch, x86_64)
    {
        LIBS += -L"libs/SFML-2.1/vc64bits"
    }
}

linux-g++
{
    !contains(QMAKE_HOST.arch, x86_64)
    {
       LIBS += -L"libs/SFML-2.1/linuxgcc32bits"
    }

    contains(QMAKE_HOST.arch, x86_64)
    {
        LIBS += -L"libs/SFML-2.1/linuxgcc64bits"
    }
}
    LIBS += -lsfml-system
    LIBS += -lsfml-network
