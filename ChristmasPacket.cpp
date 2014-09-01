#include "ChristmasPacket.h"

const void* ChristmasPacket::onSend(std::size_t &size)
{
    size = getDataSize();
    return getData();
}

void ChristmasPacket::onReceive(const void *data, std::size_t size)
{
    append(data, size);
}


void ChristmasPacket::appendData(Message m) {
    *this << m.type << m.dataSize;
    append((m.data), m.dataSize);
}

void ChristmasPacket::readData(Message &m) {
    sf::Uint8 t;
    const void* in = getData();
    *this >> t; // Utile pour éviter la confusion du compilateur, ne pas changer.
    m.type = t;
    *this >> m.dataSize;
    uInt32 i;
    const int a = sizeof(m.type) + sizeof(m.dataSize);
    for(i = 0; i < m.dataSize; i++)
        (m.data)[i] = ((const char*)in)[a + i];
}
