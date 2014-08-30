TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

OTHER_FILES += \
    .gitignore


win32
{
    !contains(QMAKE_TARGET.arch, x86_64)
    {
        LIBS += -L"libs/SFML-2.1/vc32bits"
    }

    contains(QMAKE_TARGET.arch, x86_64)
    {
        LIBS += -L"libs/SFML-2.1/vc64bits"
    }
}

linux-g++-32
{
    LIBS += -L"libs/SFML-2.1/linuxgcc32bits"
}

linux-g++-64
{
    LIBS += -L"libs/SFML-2.1/linuxgcc64bits"
}

    LIBS += -lsfml-system
    LIBS += -lsfml-network

    INCLUDEPATH += "/libs/SFML-2.1/include"
