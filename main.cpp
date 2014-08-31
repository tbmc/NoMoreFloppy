#include <SFML/System.hpp>
#include <iostream>

void func()
{
    // cette fonction démarre lorsque thread.launch() est appelé

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm thread number one" << std::endl;
}

int main()
{
    // crée un thread avec la fonction func() comme point d'entrée
    sf::Thread thread(&func);

    // exécute le thread
    thread.launch();

    // le thread principal continue à tourner...

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm the main thread" << std::endl;

    return 0;
}
