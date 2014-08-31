#include "vueconsole.h"

VueConsole::VueConsole()
{
    char *ip = 0;
    ip = new char[15];
    std::cout << "Veuillez entrer l'ip du serveur : " << std::endl;
    std::cin >> ip;
    std::cout << "Connexion au serveur " << ip << std::endl;
    delete[] ip;
}

bool VueConsole::isIpCorrect(char ip[])
{
    bool isCorrect = false;
    return isCorrect;
}
