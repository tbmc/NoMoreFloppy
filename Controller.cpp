#include "Controller.h"

using namespace sf;
using namespace std;

Fichier::~Fichier()
{
    delete file;
    delete name;
    delete path;
}


Controller::Controller()
{
}

Controller::~Controller()
{

    delete fichier;

}

STATUS Controller::connect(const char *ip, uShort port, uInt32 timeout)
{
    socket.disconnect();
    if(socket.connect(ip, port, milliseconds(timeout)) != Socket::Done)
        return Error_socket;
    return Ok;
}

STATUS Controller::serverWaitConnection(uShort port)
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

STATUS Controller::sendFileRequest(const char *path)
{
    // Stockage du nom, du chemin et de la taille du fichier
    if(fichier == NULL)
        delete fichier;
    fichier = new Fichier;
    fichier->file = fopen(path, "rb");
    if(fichier->file == NULL)
        return Error_file;
    fseek(fichier->file, 0, SEEK_END);
    fichier->filesize = ftell(fichier->file);
    fclose(fichier->file);
    fichier->path = new char(strlen(path) + 1);
    strcpy(fichier->path, path);
    const char *na = strrchr(path, '/');
    if(na == NULL)
        na = path;
    else
        na++;
    fichier->name = new char(strlen(na) + 1);
    strcpy(fichier->name, na);

    // Envoie de la demande
    ChristmasPacket paquet;
    paquet << fichier->filesize << string(fichier->name);

    Socket::Status statsend;
    statsend = socket.send(paquet);
    if(statsend != Socket::Done)
        return Error_socket;

    // Réception de la réponse
    SocketSelector selector;
    selector.add(socket);
    if(!selector.wait(milliseconds(DEFAULT_TIMEOUT)))
        return Error_socket;
    paquet.clear();
    statsend = socket.receive(paquet);
    if(statsend != Socket::Done)
        return Error_socket;
    bool accept;
    paquet >> accept;
    if(accept)
        return Ok;
    else
        return File_refused;
}

STATUS Controller::receiveFileRequest(const char *folderpath, Answer &answer)
{
    Socket::Status stat;
    ChristmasPacket paquet;

    // Réception de la demande
    stat = socket.receive(paquet);
    if(stat != Socket::Done)
        return Error_socket;
    if(fichier == NULL)
        delete fichier;

    // Parsing de la demande
    string name, chemin("");
    uInt32 filesize;
    paquet >> filesize;
    paquet >> name;

    // Demande si l'utilisateur veut recevoir le fichier
    bool response = answer.acceptFile(name.c_str(), filesize);

    // Envoie de la réponse de l'utilisateur
    paquet.clear();
    paquet << response;
    if(!response)
        return File_refused;
    stat = socket.send(paquet);
    if(stat != Socket::Done)
        return Error_socket;

    // Stockage du fichier à recevoir
    fichier = new Fichier;
    fichier->filesize = filesize;
    fichier->name = new char(name.length() + 1);
    strcpy(fichier->name, name.c_str());
    chemin = folderpath;
    if(chemin[chemin.length() - 1] != '/')
        chemin.push_back('/');
    chemin.append(name);
    fichier->path = new char(chemin.length() + 1);
    strcpy(fichier->path, chemin.c_str());

    return Ok;
}

STATUS Controller::sendFile(const char *file, uInt32 packetSize, int compression_level)
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

    char *temp = new char(packetSize * 5);
    message.data = new char(packetSize * 5);
    message.type = PACKET_DATA;

    while((readSize = fread(temp, 1, packetSize, f)) > 0)
    {
        printf("%ld %ld\n", readSize, packetSize);
        outComp = compress.compress_char_array(temp, readSize, message.data,
                                               packetSize * 2, &(message.dataSize));
        printf("%ld\n\n", message.dataSize);
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

STATUS Controller::receiveFile(const char *folderpath, uInt32 packetSize)
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
    name = new char(message.dataSize + strlen(folderpath) + 10);
    name[0] = '\0';
    strcat(name, folderpath);
    int len = strlen(name);
    if(name[len - 1] != '/')
    {
        name[len] = '/';
        name[len+1] = '\0';
    }
    strcat(name, message.data);
    printf("FICHIER : '%s'\n", name);
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
































