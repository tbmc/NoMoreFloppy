#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Network.hpp>
#include <inttypes.h>

#define DEFAULT_PORT 25666
#define DEFAULT_IP "127.0.0.1"

typedef unsigned short uShort;

enum STATUT {
    Ok,
    ERROR_PORT,
    ERROR_SOCKET,
    ERROR_ALREADY_CONNECTED
};

class Controller {

private:
    sf::TcpSocket socket;

public:
    Controller();
    STATUT connect(const char *ip, uShort port = DEFAULT_PORT);
    STATUT serverWaitConnection(uShort port = DEFAULT_PORT);
    void disconnect();

    void sendData(const char *in, uint64_t inSize);

};

#endif // CONTROLLER_H
