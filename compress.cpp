#include "compress.h"

// zlib
#include "miniz.c"

Compress::Compress()
{

}

void Compress::setCompressionLevel(int level)
{
    if(!((MIN_COMPRESSION_LEVEL <= level &&
         level <= MAX_COMPRESSION_LEVEL) ||
         level == DEFAULT_COMPRESSION_LEVEL))
        return;
    compression_level = level;
}

void Compress::compress_char_array(const char *in, uInt inSize,
        char *out, uInt outMaxSize, uInt *outSize)
{
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = (uInt) inSize;
    defstream.next_in = (Bytef *)in;
    defstream.avail_out = (uInt) outMaxSize;
    defstream.next_out = (Bytef *) out;

    deflateInit(&defstream, compression_level);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);

    *outSize = defstream.total_out;
}

void Compress::uncompress_char_array(const char *in, uInt inSize,
        char *out, uInt outMaxSize, uInt *outSize)
{
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;

    infstream.avail_in = (uInt) inSize;
    infstream.next_in = (Bytef *) in;
    infstream.avail_out = (uInt) outMaxSize;
    infstream.next_out = (Bytef *) out;

    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);

    *outSize = infstream.total_out;
}





