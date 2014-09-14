#include <iostream>
#include "vueconsole.h"
#include <QApplication>
#include "vuegui.h"
#define _CRT_SECURE_NO_WARNINGS

#include "compress.h"
#include <string.h>

int main(int argc, char *argv[])
{

//    Compress compress;
//    const char a[] = "test test test test test test";
//    char b[500];
//    char c[500];
//    uInt e, f;
//    compress.compress_char_array(a, strlen(a), b, 500, &e);
//    compress.uncompress_char_array(b, e, c, 500, &f);
//    printf("%d %d %d\n\n", strlen(a), e, f);

//    VueConsole vue;
//    vue.init();

    QApplication app(argc, argv);

    VueGUI v;
    v.show();

    return app.exec();
//    return 0;
}
