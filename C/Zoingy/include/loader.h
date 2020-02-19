#ifndef loader_h
#define loader_h

int decode_class_header(unsigned char *header, unsigned int length, class_file *class);
void delete_class(class_file *class);

#endif