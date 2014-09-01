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
    {
        printf("Erreur fichier null!\n");
        return Error_file;
    }
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
        printf("Erreur premier paquet!\n");
        return Error_socket;
    }

    char *temp = new char(packetSize);
    message.data = new char(packetSize * 2);
    message.type = PACKET_DATA;

    while((readSize = fread(temp, 1, packetSize, f)) > 0)
    {
        outComp = compress.compress_char_array(temp, readSize, message.data, packetSize * 2, &(message.dataSize));
        if(outComp != NP)
        {
            printf("Erreur outComp!\n");
            break;
        }
        packet.clear();
        packet.appendData(message);
        statsend = socket.send(packet);
        if(statsend != Socket::Done)
        {
            printf("Erreur envoie message!\n");
            break;
        }
    }

    packet.clear();
    message.type = PACKET_END;
    message.dataSize = 0;
    packet.appendData(message);
    socket.send(packet);

    delete temp;
    delete message.data;
    fclose(f);
    if(outComp != NP)
        return Error;
    if(statsend != Socket::Done)
        return Error;
    printf("NICE!\n");
    return Ok;
}

STATUT Controller::receiveFile(const char *folderpath, uInt32 packetSize)
{
    FILE * f = NULL;
    COMP_S outComp;
    uInt outSize;
    ChristmasPacket packet;
    Socket::Status status = socket.receive(packet);
    if(status != Socket::Done)
    {
        printf("Erreur premier packet\n");
        return Error_socket;
    }
    char *temp = new char(packetSize);
    char *name;
    Message message;
    message.data = new char(packetSize * 2);
    packet.readData(message);
    if(message.data[message.dataSize - 1] != '/')
    {
        message.data[message.dataSize] = '/';
        message.dataSize++;
        message.data[message.dataSize] = '\0';
    }
    name = new char(message.dataSize + strlen(folderpath) + 10);
    strcat(name, folderpath);
    strcat(name, message.data);
    f = fopen(name, "wb");
    if(f == NULL)
    {
        delete temp;
        delete message.data;
        delete name;
        printf("File == NULL!\n");
        return Error_file;
    }

    do
    {
        status = socket.receive(packet);
        if(status != Socket::Done)
        {
            printf("Erreur réception paquet!\n");
            break;
        }
        packet.readData(message);
        if(message.type == PACKET_DATA)
        {
            outComp = compress.uncompress_char_array(message.data, message.dataSize,
                                                     temp, packetSize, &outSize);
            if(outComp != NP)
            {
                printf("Erreur outComp!\n");
                break;
            }
            fwrite(temp, 1, outSize, f);
        }
    }while(message.type != PACKET_END);

    delete temp;
    delete message.data;
    delete name;
    fflush(f);
    fclose(f);
    if(status != Socket::Done)
        return Error;
    printf("NICE!\n");
    return Ok;
}
































