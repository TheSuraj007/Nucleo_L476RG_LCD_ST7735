
#ifndef __FONTS_H__
#define __FONTS_H__

#include <stdint.h>

typedef struct
{
    const uint8_t width;
    uint8_t height;
    const uint8_t column;
    const uint8_t offset;
    const uint8_t *data;
} FontDef;

extern FontDef Font_extra_Small;
extern FontDef Font_Num_Small;
extern FontDef Font_Small;
extern FontDef Font_Medium;

#endif // __FONTS_H__