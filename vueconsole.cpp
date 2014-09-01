#include "vueconsole.h"

VueConsole::VueConsole()
{
    int ask;
    std::cout << "1 - Client\n2 - serveur"<< std::endl;
    while (ask != 1 || ask != 2)
    {
        std::cin >> ask;
    }

    if (ask == 1)
    {
        char ip[500];
        std::string cheminFichier;
        do
        {
            std::cout << "Veuillez entrer l'ip du serveur : " << std::endl;
            std::cin >> ip;
        } while(!this->isIpCorrect(ip));
        std::cout << "Chemin du fichier à envoyer :" << std::endl;
        std::cin >> cheminFichier;
        //this->correctionCheminFichier(cheminFichier);

        std::cout << "Connexion au serveur " << ip << std::endl;
    }
    else
    {
        std::cout << "Attente du fichier" << std::endl;
    }

}

bool VueConsole::isIpCorrect(char ip[])
{
    bool isCorrect = true;
    bool isCorrect2 = true;
    int pointsNumber = 0;
    int verif = 0;
    int i = 0;
    while (ip[i] != '\0')
    {
        if (ip[i] == '.')
        {
            if (verif > 3)
            {
                isCorrect = false;
            }
            verif = 0;
            pointsNumber++;
            if ('0' > ip[i+1] || ip[i+1] > '9')
            {
                isCorrect = false;
            }
            if (i == 0)
            {
                isCorrect = false;
            }
            else if ('0' > ip[i-1] || ip[i-1] > '9')
            {
                isCorrect = false;
            }
        }
        else if ('0' > ip[i] || ip[i] > '9')
        {
                isCorrect2 = false;
        }
        else
        {
            verif++;
        }
        i++;
    }
    if (pointsNumber != 3 || isCorrect2 == false || i<4)
    {
        isCorrect = false;
    }
    return isCorrect;
}
/*
void VueConsole::correctionCheminFichier(std::string chemin)
{
    std::replace(chemin.begin(), chemin.end(), '\\', '/');
}
*/
