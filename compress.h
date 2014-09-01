#ifndef COMPRESS_H
#define COMPRESS_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define DEFAULT_COMPRESSION_LEVEL (-1)
#define MIN_COMPRESSION_LEVEL (0)
#define MAX_COMPRESSION_LEVEL (10)

typedef unsigned int uInt;

enum COMP_S
{
    NP,
    Error_P
};

class Compress {

private:
    int compression_level = DEFAULT_COMPRESSION_LEVEL;

public:
    Compress();
    COMP_S setCompressionLevel(int level);

    COMP_S compress_char_array(const char *in, uInt inSize,
                  char *out, uInt outMaxSize, uInt *outSize);

    COMP_S uncompress_char_array(const char *in, uInt inSize,
                  char *out, uInt outMaxSize, uInt *outSize);

};






#endif // COMPRESS_H
