#ifndef COMPRESS_H
#define COMPRESS_H

#define DEFAULT_COMPRESSION_LEVEL (-1)
#define MIN_COMPRESSION_LEVEL (0)
#define MAX_COMPRESSION_LEVEL (10)

typedef unsigned int uInt;

class Compress {

private:
    int compression_level = DEFAULT_COMPRESSION_LEVEL;

public:
    Compress();
    void setCompressionLevel(int level);

    void compress_char_array(const char *in, uInt inSize,
                  char *out, uInt outMaxSize, uInt *outSize);

    void uncompress_char_array(const char *in, uInt inSize,
                  char *out, uInt outMaxSize, uInt *outSize);

};






#endif // COMPRESS_H
