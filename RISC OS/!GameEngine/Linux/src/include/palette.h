#ifndef H_PALETTE
#define H_PALETTE
#include "types.h"

UINT mix_colour(BYTE r, BYTE g, BYTE b, BYTE mr, BYTE mg, BYTE mb, float ratio);
void generate_palette();
void test_palette();
void test_palette_wide();

#endif
