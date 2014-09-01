#ifndef CHRISTMASPACKET_H
#define CHRISTMASPACKET_H

#include <SFML/Network/Packet.hpp>
#include <inttypes.h>

typedef uint32_t uInt32;

typedef struct {
    unsigned char type;
    char *data;
    uInt32 dataSize;
} Message;

class ChristmasPacket : public sf::Packet
{
    // Ne pas utiliser ces fonctions pour compresser automatiquement
    // cela pose plusieurs problèmes d'allocations mémoire.
    virtual const void* onSend(std::size_t &size);
    virtual void onReceive(const void *data, std::size_t size);

private:

public:
    void setCompressionLevel(int level);

    // Only Store this with this instance!
    void appendData(Message m);

    // Only read this with this instance!
    void readData(Message &m);

};

#endif // CHRISTMASPACKET_H
