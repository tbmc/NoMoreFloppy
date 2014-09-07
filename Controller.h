#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Network.hpp>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "compress.h"
#include "ChristmasPacket.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define DEFAULT_PORT (25666)
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_TIMEOUT (5000)

#define PACKET_DATA (0)
#define PACKET_INFORMATION (1)
#define PACKET_FUCKER (3)
#define PACKET_END (4)

typedef unsigned short uShort;
typedef uint32_t uInt32;
//#define MAX_PACKET_SIZE (67108864)
#define MAX_PACKET_SIZE (1024)
#define DEFAULT_PACKET_SIZE (1048576)

enum STATUT
{
    Ok,
    Error,
    Error_port,
    Error_socket,
    Error_bufferoverflow,
    Error_file
};

class Controller {

private:
    sf::TcpSocket socket;
    Compress compress;

public:
    Controller();
    ~Controller();

    // Contrôle de la connection
    STATUT connect(const char *ip, uShort port = DEFAULT_PORT, sf::Int32 timeout = DEFAULT_TIMEOUT);
    STATUT serverWaitConnection(uShort port = DEFAULT_PORT);
    void disconnect();

    //Envoie et réception de fichier
    STATUT sendFile(const char *file, uInt32 packetSize = DEFAULT_PACKET_SIZE,
                    int compression_level = DEFAULT_COMPRESSION_LEVEL);
    STATUT receiveFile(const char *folderpath, uInt32 packetSize = DEFAULT_PACKET_SIZE);

};

#endif // CONTROLLER_H
