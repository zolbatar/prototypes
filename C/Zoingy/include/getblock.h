#ifndef getblock_h
#define getblock_h

unsigned int get_u1(unsigned char *data, unsigned int *pos);
unsigned int get_u2(unsigned char *data, unsigned int *pos);
unsigned int get_u4(unsigned char *data, unsigned int *pos);
unsigned char *get_utf8(unsigned char *data, unsigned int *pos, size_t length);
void *get_data(unsigned char *data, unsigned int *pos, size_t length);

#endif