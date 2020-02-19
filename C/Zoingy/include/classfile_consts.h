#ifndef classfile_consts_h
#define classfile_consts_h

#define get_block_h

#define false 0
#define true 1

#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1

#define ACC_PUBLIC 0x0001 /* Declared public; may be accessed from outside its package.*/
#define ACC_FINAL 0x0010 /* Declared final; no subclasses allowed. */
#define ACC_SUPER 0x0020 /* Treat superclass methods specially when invoked by the invokespecial instruction. */
#define ACC_INTERFACE 0x0200 /* Is an interface, not a class. */
#define ACC_ABSTRACT 0x0400

#define METHOD_ATTR_OTHER 0
#define METHOD_ATTR_CODE 1

#endif