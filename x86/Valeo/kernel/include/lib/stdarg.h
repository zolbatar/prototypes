#ifndef __LIB_STDARG_H__
#define __LIB_STDARG_H__

typedef __builtin_va_list __gnuc_va_list;
#define va_start(v,l)	__builtin_stdarg_start((v),l)
#define va_end		__builtin_va_end
#define va_arg		__builtin_va_arg
#define va_copy(d,s)	__builtin_va_copy((d),(s))
typedef __gnuc_va_list va_list;

#endif // __LIB_STDARG_H__


