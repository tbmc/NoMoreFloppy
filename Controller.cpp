#include "Controller.h"

using namespace sf;

Controller::Controller()
{
}

Controller::~Controller()
{
}

STATUT Controller::connect(const char *ip, uShort port)
{
    socket.disconnect();
    if(socket.connect(ip, port) != Socket::Done)
        return Error_socket;
    return Ok;
}

STATUT Controller::serverWaitConnection(uShort port)
{
    socket.disconnect();
    TcpListener listener;
    if(listener.listen(port) != Socket::Done)
        return Error_port;
    if(listener.accept(socket) != Socket::Done)
        return Error_socket;
    return Ok;
}

void Controller::disconnect()
{
    socket.disconnect();
}

STATUT Controller::sendFile(const char *file, uInt32 packetSize, int compression_level)
{
    if(compress.setCompressionLevel(compression_level) != NP)
        return Error;
    FILE * f = NULL;
    f = fopen(file, "rb");
    if(f == NULL)
        return Error_file;
    COMP_S outComp;
    Socket::Status statsend;
    size_t readSize;
    ChristmasPacket packet;
    Message message;
    // Envoie du nom du fichier
    message.type = PACKET_INFORMATION;
    const char *na = strrchr(file, '/');
    if(na == NULL)
        na = file;
    else
        na++;
    message.data = (char*) na;
    message.dataSize = strlen(na);
    packet.appendData(message);
    statsend = socket.send(packet);
    if(statsend != Socket::Done)
    {
        delete message.data;
        return Error_socket;
    }

    char *temp = new char(packetSize);
    message.data = new char(packetSize * 2);
    message.type = PACKET_DATA;

    while((readSize = fread(temp, 1, packetSize, f)) > 0)
    {
        outComp = compress.compress_char_array(temp, readSize, message.data, packetSize * 2, &(message.dataSize));
        if(outComp != NP)
            break;
        packet.clear();
        packet.appendData(message);
        statsend = socket.send(packet);
        if(statsend != Socket::Done)
            break;
    }

    delete temp;
    delete message.data;
    fclose(f);
    if(outComp != NP)
        return Error;
    if(statsend != Socket::Done)
        return Error;
    return Ok;
}

STATUT Controller::receiveFile(const char *folderpath, uInt32 packetSize)
{
    FILE * f = NULL;
//    f = fopen(file, "wb");
//    if(f == NULL)
//        return Error_file;
    ChristmasPacket packet;
    Socket::Status status = socket.receive(packet);
    if(status != Socket::Done)
    {
        return Error_socket;
    }
    char *temp = new char(packetSize);
    Message message;
    message.data = new char(packetSize * 2);
    packet.readData(message);


    delete temp;
    delete message.data;
    fclose(f);
    return Ok;
}

STATUT Controller::sendFile(const char *file, uInt32 packetSize, int compression_level)
{
    return ERROR_BUFFEROVERFLOW;
}
