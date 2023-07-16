

#include "fonts.h"
#include "Background_image.h"
#include "display.h"
#include "st7735.h"
#include "GUI_images.h"
#define VOL_CTRL_L 0x2C // Register address in codac
#define VOL_CTRL_R 0x2D // Register address in codac

// #define RED_LED_ON 1
// #define GREEN_LED_ON 2
// #define OFF_LED 3

void Display_Init()
{
    ST7735_Init();
    // ST7735_FillScreen(ST7735_BLACK);
    // ST7735_DrawImage(0, 0, 130, 130, gImage_spanda_130x130);
    // ST7735_DrawPixel(4, 14, ST7735_BLACK);

    ST7735_draw_color_image(0, 0, &spanda_logo);
    MXC_Delay(2000000); // 100 micro-seconds
    // ST7735_draw_monochrome_vector_image(110, 0, &battery_image_18, ST7735_BLACK, ST7735_WHITE);
    // ST7735_draw_color_image_bckg(0, 0, &background);
    // ST7735_DrawImage(0, 0, 130, 130, Background_130x130);
    ST7735_draw_monochrome_vector_image_bckg(0, 0, &background, ST7735_BLACK, ST7735_WHITE);
    ST7735_draw_monochrome_vector_image_bckg(2, 0, &bledisconnected_image_18, ST7735_LIGHTGREY, ST7735_WHITE);
    ST7735_draw_monochrome_vector_image_bckg(110, 0, &battery_image_18, ST7735_BLACK, ST7735_WHITE);
}
