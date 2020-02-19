#ifndef __ASMMACROS_H__
#define __ASMMACROS_H__

#define	ENTER_INTERRUPT	        \
	cli;			\
	cld;			\
	push  %ds;		\
	push  %es;		\
	push  %fs;		\
	push  %gs;		\
	pushl %eax;             \
	pushl %ebx;             \
	pushl %ecx;             \
	pushl %edx;             \
	pushl %ebp;             \
	pushl %esi;             \
	pushl %edi;             \
	pushl %ss;		\
	pushl %esp;		\
	pushl %esp;

#define EXIT_INTERRUPT 		\
	addl $4, %esp;		\
	lss (%esp), %esp;	\
	addl $4, %esp;		\
	popl %edi;              \
	popl %esi;              \
	popl %ebp;              \
	popl %edx;              \
	popl %ecx;              \
	popl %ebx;              \
	popl %eax;              \
	pop   %gs;	        \
	pop   %fs;	        \
	pop   %es;	        \
	pop   %ds;	        \
	sti;  			\
	iret

#define EXIT_SYSCALL 		\
	addl $4, %esp;		\
	lss (%esp), %esp;	\
	addl $4, %esp;		\
	popl %edi;              \
	popl %esi;              \
	popl %ebp;              \
	popl %edx;              \
	popl %ecx;              \
	popl %ebx;              \
	addl $4, %esp;		\
	pop   %gs;	        \
	pop   %fs;	        \
	pop   %es;	        \
	pop   %ds;	        \
	sti;  			\
	iret

#define	ENTEREXCEPTION 	\
	cld;			\
	push  %ds;		\
	push  %es;		\
	push  %fs;		\
	push  %gs;              \
	pushl %eax;             \
	pushl %ebx;             \
	pushl %ecx;             \
	pushl %edx;             \
	pushl %ebp;             \
	pushl %esi;             \
	pushl %edi;             \

#define EXITEXCEPTION_WITHERROR\
	popl %edi;              \
	popl %esi;              \
	popl %ebp;              \
	popl %edx;              \
	popl %ecx;              \
	popl %ebx;              \
	popl %eax;              \
	pop   %gs;	        \
	pop   %fs;	        \
	pop   %es;	        \
	pop   %ds;	        \
	addl  $4, %esp;		\
	iret

#define EXITEXCEPTION		\
	popl %edi;              \
	popl %esi;              \
	popl %ebp;              \
	popl %edx;              \
	popl %ecx;              \
	popl %ebx;              \
	popl %eax;              \
	pop   %gs;	        \
	pop   %fs;	        \
	pop   %es;	        \
	pop   %ds;	        \
	iret

#endif // __ASMMACROS_H__
