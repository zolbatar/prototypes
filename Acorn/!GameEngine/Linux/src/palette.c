#include <stdlib.h>
#include <stdio.h>
#include "types.h"

UINT mix_colour(BYTE r, BYTE g, BYTE b, BYTE mr, BYTE mg, BYTE mb, float ratio)
{
    // Mix in other colour
    if (ratio > 1.0)
        ratio = 1.0;
    else if (ratio < 0.0)
        ratio = 0.0;
    float iRatio = 1.0 - ratio;

    BYTE rc = ((r * iRatio) + (mr * ratio));
    BYTE gc = ((g * iRatio) + (mg * ratio));
    BYTE bc = ((b * iRatio) + (mb * ratio));
    return (bc << 16) + (gc << 8) + rc;
}
