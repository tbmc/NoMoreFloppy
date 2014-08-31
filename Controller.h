#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Network.hpp>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#include "compress.h"

#define DEFAULT_PORT (25666)
#define DEFAULT_IP "127.0.0.1"

#define PACKET_DATA (0)
#define PACKET_INFORMATION (1)
#define PACKET_FUCKER (3)

typedef unsigned short uShort;
typedef u_int32_t uInt32;
#define MAX_PACKET_SIZE (67108864)
#define DEFAULT_PACKET_SIZE (1048576)

enum STATUT {
    Ok,
    ERROR_PORT,
    ERROR_SOCKET,
    ERROR_BUFFEROVERFLOW
};

class Controller {

private:
    sf::TcpSocket socket;
    Compress compress;
    char *temp = 0;
    uInt32 tempSize = 0;

public:
    Controller();
    ~Controller();

    // Contrôle de la connection
    STATUT connect(const char *ip, uShort port = DEFAULT_PORT);
    STATUT serverWaitConnection(uShort port = DEFAULT_PORT);
    void disconnect();

    // Envoie et recéption de data
    STATUT sendData(const char *data, uInt32 size);
    STATUT receiveData(char *data, uInt32 &size);

    //Envoie et réception de fichier
    STATUT sendFile(const char *file, uInt32 packetSize = DEFAULT_PACKET_SIZE,
                    int compression_level = DEFAULT_COMPRESSION_LEVEL);






















};

#endif // CONTROLLER_H
