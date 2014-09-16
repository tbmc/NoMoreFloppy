#ifndef CHRISTMASPACKET_H
#define CHRISTMASPACKET_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <SFML/Network/Packet.hpp>
#include <inttypes.h>
#include <string>

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

    //Doivent être utilisé une seule fois par instance à chaque appel de clear()
    ChristmasPacket& operator <<(Message &message)
    {
        appendData(message);
    }
    ChristmasPacket& operator <<(uInt32 i)
    {
        Packet::operator <<(i);
    }
    ChristmasPacket& operator <<(std::string &str)
    {
        Packet::operator <<(str);
    }
    ChristmasPacket& operator <<(bool b)
    {
        Packet::operator <<(b);
    }

    ChristmasPacket& operator >>(Message &message)
    {
        readData(message);
    }
    ChristmasPacket& operator >>(uInt32 &i)
    {
        Packet::operator >>(i);
    }
    ChristmasPacket& operator >>(std::string &str)
    {
        Packet::operator >>(str);
    }
    ChristmasPacket& operator >>(bool &b)
    {
        Packet::operator >>(b);
    }







};




























#endif // CHRISTMASPACKET_H
