#ifndef VUECONSOLE_H
#define VUECONSOLE_H

#include <iostream>
#include <string>
#include <algorithm>
#include "Controller.h"

class VueConsole
{
private:
    Controller controller;

public:
    void init();
    VueConsole();
    static bool isIpCorrect(char ip[]);
    static void correctionCheminFichier(std::string fichier);
};

#endif // VUECONSOLE_H
