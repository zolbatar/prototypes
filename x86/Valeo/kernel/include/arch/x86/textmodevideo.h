#ifndef __ARCH_X86_CONSOLE_H__
#define __ARCH_X86_CONSOLE_H__

#define TEXTCOLOUR_BLACK 0
#define TEXTCOLOUR_BLUE 1
#define TEXTCOLOUR_GREEN 2
#define TEXTCOLOUR_CYAN 3
#define TEXTCOLOUR_RED 4
#define TEXTCOLOUR_PURPLE 5
#define TEXTCOLOUR_BROWN 6
#define TEXTCOLOUR_WHITE 7
#define TEXTCOLOUR_GREY 8
#define TEXTCOLOUR_LBLUE 9
#define TEXTCOLOUR_LGREEN 10
#define TEXTCOLOUR_LCYAN 11
#define TEXTCOLOUR_LRED 12
#define TEXTCOLOUR_LPURPLE 13
#define TEXTCOLOUR_YELLOW 14
#define TEXTCOLOUR_LWHITE 15

// Text mode frame buffer
extern volatile unsigned char *g_pVideo;

void TextModeVideo_Init( void );
void TextModeVideo_PostMMInit( void );
void TextModeVideo_Cls( void );
void TextModeVideo_ChangeColour( uchar nColour );
void TextModeVideo_WriteChar( uchar nColour );
void TextModeVideo_DeleteChar ( void );
void TextModeVideo_WriteString( char *pszString );

#endif // __ARCH_X86_CONSOLE_H__

