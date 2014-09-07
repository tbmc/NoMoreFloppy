#include "compress.h"

// zlib
#include "miniz.c"

Compress::Compress()
{
}

COMP_S Compress::setCompressionLevel(int level)
{
    if(!((MIN_COMPRESSION_LEVEL <= level &&
         level <= MAX_COMPRESSION_LEVEL) ||
         level == DEFAULT_COMPRESSION_LEVEL))
        return Error_P;
    compression_level = level;
    return NP;
}

COMP_S Compress::compress_char_array(const char *in, uInt inSize,
        char *out, uInt outMaxSize, uInt *outSize)
{
    int outDef;
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = (uInt) inSize;
    defstream.next_in = (Bytef *) in;
    defstream.avail_out = (uInt) outMaxSize;
    defstream.next_out = (Bytef *) out;

    outDef = deflateInit(&defstream, compression_level);
    if(outDef < 0)
        return Error_P;
    outDef = deflate(&defstream, Z_FINISH);
    if(outDef < 0)
        return Error_P;
    outDef = deflateEnd(&defstream);
    if(outDef < 0)
        return Error_P;

    *outSize = defstream.total_out;

    return NP;
}

COMP_S Compress::uncompress_char_array(const char *in, uInt inSize,
        char *out, uInt outMaxSize, uInt *outSize)
{
    int outInf;
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;

    infstream.avail_in = (uInt) inSize;
    infstream.next_in = (Bytef *) in;
    infstream.avail_out = (uInt) outMaxSize;
    infstream.next_out = (Bytef *) out;

    outInf = inflateInit(&infstream);
    if(outInf < 0)
        return Error_P;
    outInf = inflate(&infstream, Z_NO_FLUSH);
    if(outInf < 0)
        return Error_P;
    outInf = inflateEnd(&infstream);
    if(outInf < 0)
        return Error_P;

    *outSize = infstream.total_out;
    return NP;
}





