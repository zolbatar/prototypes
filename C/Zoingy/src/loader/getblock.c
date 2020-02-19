#include <stdlib.h>
#include <string.h> 
#include "classfile_structs.h"
#include "classfile_consts.h"
#include "getblock.h"

/* Get bytes out of header */
unsigned int get_u1(unsigned char *data, unsigned int *pos)
{
    unsigned int value = (unsigned char)data[*pos];
    *pos += 1;
    return value;
}

unsigned int get_u2(unsigned char *data, unsigned int *pos)
{
    unsigned int value = ((unsigned char)data[*pos] << 8) + (unsigned char)data[*pos + 1];
    *pos += 2;
    return value;
}

unsigned int get_u4(unsigned char *data, unsigned int *pos)
{
    unsigned int value = ((unsigned char)data[*pos] << 24) + ((unsigned char)data[*pos + 1] << 16) + ((unsigned char)data[*pos + 2] << 8) + (unsigned char)data[*pos + 3];
    *pos += 4;
    return value;
}

unsigned char *get_utf8(unsigned char *data, unsigned int *pos, size_t length)
{
    unsigned char *string = malloc(length);
    memcpy(string, &data[*pos], length);
    *pos += length;
    return string;
}

void *get_data(unsigned char *data, unsigned int *pos, size_t length)
{
    void *data_out = malloc(length);
    memcpy(data_out, &data[*pos], length);
    *pos += length;
    return data_out;
}
