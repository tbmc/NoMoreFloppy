#ifndef VUECONSOLE_H
#define VUECONSOLE_H

#include <iostream>
#include <string>
#include <algorithm>

class VueConsole
{
public:
    VueConsole();
    static bool isIpCorrect(char ip[]);
    static void correctionCheminFichier(std::string fichier);
};

#endif // VUECONSOLE_H
