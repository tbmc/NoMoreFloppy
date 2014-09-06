#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Network.hpp>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

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

enum STATUS
{
    Ok,                     // Si aucune erreur ne s'est produite
    Error,
    Error_port,
    Error_socket,
    Error_bufferoverflow,
    Error_file,
    File_refused
};

class Fichier {
public:
    FILE * file;
    uInt32 filesize;
    char * name;
    char * path;
    ~Fichier();
};

class Answer
{
public:
    virtual bool acceptFile(const char *filename, uInt32 filesize) = 0;
};

class Controller {

private:
    sf::TcpSocket socket;
    Compress compress;
    Fichier *fichier = NULL;

public:
    Controller();
    ~Controller();

    // Contrôle de la connection
    STATUS connect(const char *ip, uShort port = DEFAULT_PORT, uInt32 timeout = DEFAULT_TIMEOUT);
    STATUS serverWaitConnection(uShort port = DEFAULT_PORT);
    void disconnect();

    //Demande d'envoie de fichier
    STATUS sendFileRequest(const char *path);
    STATUS receiveFileRequest(const char *folderpath, Answer &answer);

    //Envoie et réception de fichier
    STATUS sendFile(const char *file, uInt32 packetSize = DEFAULT_PACKET_SIZE,
                    int compression_level = DEFAULT_COMPRESSION_LEVEL);
    STATUS receiveFile(const char *folderpath, uInt32 packetSize = DEFAULT_PACKET_SIZE);

};
























#endif // CONTROLLER_H
