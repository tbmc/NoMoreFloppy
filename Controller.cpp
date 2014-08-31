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
        return ERROR_SOCKET;
    return Ok;
}

STATUT Controller::serverWaitConnection(uShort port)
{
    socket.disconnect();
    TcpListener listener;
    if(listener.listen(port) != Socket::Done)
        return ERROR_PORT;
    if(listener.accept(socket) != Socket::Done)
        return ERROR_SOCKET;
    return Ok;
}

void Controller::disconnect()
{
    socket.disconnect();
}

STATUT Controller::sendData(const char *data, uInt32 size)
{
    if(size > MAX_PACKET_SIZE)
        return ERROR_BUFFEROVERFLOW;
    if(socket.send(data, size) != Socket::Done)
        return ERROR_SOCKET;
    return Ok;
}

STATUT Controller::receiveData(char *data, uInt32 &size)
{
    if(socket.receive(data, MAX_PACKET_SIZE, size) != Socket::Done)
        return ERROR_SOCKET;
    return Ok;
}

STATUT Controller::sendFile(const char *file, uInt32 packetSize, int compression_level)
{

}























