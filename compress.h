#ifndef COMPRESS_H
#define COMPRESS_H

typedef unsigned int uInt;

class Compress {

private:
    int compression_level = -1;

public:
    Compress();
    void setCompressionLevel(int level);

    void compress_char_array(const char *in, uInt inSize,
                  char *out, uInt outMaxSize, uInt *outSize);

    void uncompress_char_array(const char *in, uInt inSize,
                  char *out, uInt outMaxSize, uInt *outSize);

};






#endif // COMPRESS_H
