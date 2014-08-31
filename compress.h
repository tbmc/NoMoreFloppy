#ifndef COMPRESS_H
#define COMPRESS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int uInt;

void setCompressionLevel(int level);

void compress_char_array(const char *in, uInt inSize,
              char *out, uInt outMaxSize, uInt *outSize);

void uncompress_char_array(const char *in, uInt inSize,
              char *out, uInt outMaxSize, uInt *outSize);

#ifdef __cplusplus
}
#endif


#endif // COMPRESS_H
