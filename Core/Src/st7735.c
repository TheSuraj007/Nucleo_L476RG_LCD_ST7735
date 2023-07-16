#include "stm32l4xx_hal.h"
#include "st7735.h"
#include "GUI_images.h"

#define DELAY 0x80
int32_t Ymax, Ymin, X;        // X goes from 0 to 127
int32_t Yrange; //YrangeDiv2;
int TimeIndex;
uint16_t PlotBGColor;
void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	// print_uart("X_start: %d\n", x0);
	// print_uart("y_start: %d\n\n", y0);

	// print_uart("X_end: %d\n", x1);
	// print_uart("y_end: %d\n\n", y1);

	lcd7735_sendCmd(ST7735_CASET);        // Column addr set
	lcd7735_sendData(0x00);               // XS15 ~ XS8
	lcd7735_sendData(x0 + ST7735_XSTART); // XSTART       XS7 ~ XS0
	lcd7735_sendData(0x00);               // XE15 ~ XE8
	lcd7735_sendData(x1 + ST7735_XSTART); // XEND         XE7 ~ XE0

	lcd7735_sendCmd(ST7735_RASET); // Row addr set
	lcd7735_sendData(0x00);
	lcd7735_sendData(y0 + ST7735_YSTART); // YSTART
	lcd7735_sendData(0x00);
	lcd7735_sendData(y1 + ST7735_YSTART); // YEND

	lcd7735_sendCmd(ST7735_RAMWR);
}
void ST7735_Init() {
	//ST7735_Select();
	LCD_CS0
	;
	//ST7735_Reset();
	LCD_RST0
	;
	HAL_Delay(7);
	LCD_RST1
	;

	//ST7735_ExecuteCommandList(init_cmds1);
	ST7735_Init_Command1();
	//ST7735_ExecuteCommandList(init_cmds2);
	ST7735_Init_Command2();
	//ST7735_ExecuteCommandList(init_cmds3);
	ST7735_Init_Command3();

	//ST7735_Unselect();
	LCD_CS1
	;
}

void ST7735_Init_Command1(void) {
	lcd7735_sendCmd(ST7735_SWRESET);		//  1: Software reset
	HAL_Delay(150);
	lcd7735_sendCmd(ST7735_SLPOUT);			//  2: Out of sleep mode
	HAL_Delay(500);
	lcd7735_sendCmd(ST7735_FRMCTR1);		//  3: Frame rate ctrl - normal mode
	lcd7735_sendData(0x00);			//     Rate = fosc/(1x2+40) * (LINE+2C+2D)
	lcd7735_sendData(0x01);
	lcd7735_sendData(0x01);
	lcd7735_sendCmd(ST7735_FRMCTR2);	//  4: Frame rate control - idle mode
	lcd7735_sendData(0x00);				//  Rate = fosc/(1x2+40) * (LINE+2C+2D)
	lcd7735_sendData(0x01);
	lcd7735_sendData(0x01);
	lcd7735_sendCmd(ST7735_FRMCTR3);	//  5: Frame rate ctrl - partial mode
	lcd7735_sendData(0x00);							//     Dot inversion mode
	lcd7735_sendData(0x01);
	lcd7735_sendData(0x01);
	lcd7735_sendData(0x00);							//     Line inversion mode
	lcd7735_sendData(0x01);
	lcd7735_sendData(0x01);
	lcd7735_sendCmd(ST7735_INVCTR);			//  6: Display inversion ctrl
	lcd7735_sendData(0x07);							//     No inversion
	lcd7735_sendCmd(ST7735_PWCTR1);			//  7: Power control
	lcd7735_sendData(0xA2);
	lcd7735_sendData(0x02);							//     -4.6V
	lcd7735_sendData(0x84);							//     AUTO mode
	lcd7735_sendCmd(ST7735_PWCTR2);			//  8: Power control
	lcd7735_sendData(0xC5);		//     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
	lcd7735_sendCmd(ST7735_PWCTR3);			//  9: Power control
	lcd7735_sendData(0x0A);							//     Opamp current small
	lcd7735_sendData(0x00);							//     Boost frequency
	lcd7735_sendCmd(ST7735_PWCTR4);			// 10: Power control
	lcd7735_sendData(0x8A);		//     BCLK/2, Opamp current small & Medium low
	lcd7735_sendData(0x2A);
	lcd7735_sendCmd(ST7735_PWCTR5);			// 11: Power control
	lcd7735_sendData(0x8A);
	lcd7735_sendData(0xEE);
	lcd7735_sendCmd(ST7735_VMCTR1);			// 12: Power control
	lcd7735_sendData(0x0E);

//	lcd7735_sendCmd(ST7735_MADCTL);			// 14: Memory access control (directions)

	// ST7735R Gamma Sequence
	lcd7735_sendCmd(0xe0);
	lcd7735_sendData(0x0f);
	lcd7735_sendData(0x1a);
	lcd7735_sendData(0x0f);
	lcd7735_sendData(0x18);
	lcd7735_sendData(0x2f);
	lcd7735_sendData(0x28);
	lcd7735_sendData(0x20);
	lcd7735_sendData(0x22);
	lcd7735_sendData(0x1f);
	lcd7735_sendData(0x1b);
	lcd7735_sendData(0x23);
	lcd7735_sendData(0x37);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x07);
	lcd7735_sendData(0x02);
	lcd7735_sendData(0x10);

	lcd7735_sendCmd(0xe1);
	lcd7735_sendData(0x0f);
	lcd7735_sendData(0x1b);
	lcd7735_sendData(0x0f);
	lcd7735_sendData(0x17);
	lcd7735_sendData(0x33);
	lcd7735_sendData(0x2c);
	lcd7735_sendData(0x29);
	lcd7735_sendData(0x2e);
	lcd7735_sendData(0x30);
	lcd7735_sendData(0x30);
	lcd7735_sendData(0x39);
	lcd7735_sendData(0x3f);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x07);
	lcd7735_sendData(0x03);
	lcd7735_sendData(0x10);

	lcd7735_sendCmd(0x2a);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x7f);

	lcd7735_sendCmd(0x2b);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x9f);

	lcd7735_sendCmd(0xF0); // Enable test command
	lcd7735_sendData(0x01);

	lcd7735_sendCmd(0xF6); // Disable ram power save mode
	lcd7735_sendData(0x00);

	lcd7735_sendCmd(ST7735_INVOFF);    // 13: Don't invert display
//	  lcd7735_sendCmd(ST7735_INVON); // 13: ON invert display

	lcd7735_sendCmd(ST7735_MADCTL);    // 14: Memory access control (directions)
	lcd7735_sendData(ST7735_ROTATION); //     row addr/col addr, bottom to top refresh

	lcd7735_sendCmd(ST7735_COLMOD); // 65k mode ->16-bit color
	lcd7735_sendData(0x05);

	lcd7735_sendCmd(0x29); // Display on
}

void ST7735_Init_Command2(void) {
	lcd7735_sendCmd(ST7735_CASET);			//  1: Column addr set
	lcd7735_sendData(0x00);							//     XSTART = 0
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);							//     XEND = 127
	lcd7735_sendData(0x7F);
	lcd7735_sendCmd(ST7735_RASET);			//  2: Row addr set
	lcd7735_sendData(0x00);							//     XSTART = 0
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);							//     XEND = 127
	lcd7735_sendData(0x7F);
}

void ST7735_Init_Command3(void) {
	lcd7735_sendCmd(ST7735_GMCTRP1);  //  1: Magical unicorn dust
	lcd7735_sendData(0x02);
	lcd7735_sendData(0x1C);
	lcd7735_sendData(0x07);
	lcd7735_sendData(0x12);
	lcd7735_sendData(0x37);
	lcd7735_sendData(0x32);
	lcd7735_sendData(0x29);
	lcd7735_sendData(0x2D);
	lcd7735_sendData(0x29);
	lcd7735_sendData(0x25);
	lcd7735_sendData(0x2B);
	lcd7735_sendData(0x39);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x01);
	lcd7735_sendData(0x03);
	lcd7735_sendData(0x10);
	lcd7735_sendCmd(ST7735_GMCTRN1);  //  2: Sparkles and rainbows
	lcd7735_sendData(0x03);
	lcd7735_sendData(0x1D);
	lcd7735_sendData(0x07);
	lcd7735_sendData(0x06);
	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x2C);
	lcd7735_sendData(0x29);
	lcd7735_sendData(0x2D);
	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x2E);
	lcd7735_sendData(0x37);
	lcd7735_sendData(0x3F);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x00);
	lcd7735_sendData(0x02);
	lcd7735_sendData(0x10);
	lcd7735_sendCmd(ST7735_NORON);
	HAL_Delay(10);
	lcd7735_sendCmd(ST7735_DISPON);
	HAL_Delay(100);
}

void ST7735_PlotPoint(int32_t data1, uint16_t color1) {
	data1 = ((data1 - Ymin) * 100) / Yrange;
	if (data1 > 98) {
		data1 = 98;
		color1 = ST7735_RED;
	}
	if (data1 < 0) {
		data1 = 0;
		color1 = ST7735_RED;
	}
	ST7735_DrawPixel(TimeIndex + 11, 116 - data1, color1);
	ST7735_DrawPixel(TimeIndex + 11, 115 - data1, color1);
}

void ST7735_PlotIncrement(void) {
	TimeIndex = TimeIndex + 1;
	if (TimeIndex > 99) {
		TimeIndex = 0;
	}
	ST7735_DrawFastVLine(TimeIndex + 11, 17, 100, PlotBGColor);
}

void ST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
	if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
		return;

	LCD_CS0
	;

	ST7735_SetAddressWindow(x, y, x + 1, y + 1);
	// uint8_t data[2];
	// data[0] = color >> 8;
	// data[1] = color & 0xFF;
	lcd7735_sendData((uint8_t) (color >> 8)); // no need to allocate an array since the operation can be inlined
	lcd7735_sendData((uint8_t) (color & 0xFF));

	LCD_CS1
	; // unselect
}

uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor) {
	uint32_t count = 0;
	if (y > 15)
		return 0;
	while (*pt) {
		ST7735_DrawCharS(x * 6, y * 10, *pt, textColor, ST7735_BLACK, 1);
		pt++;
		x = x + 1;
		if (x > 20)
			return count; // number of characters printed
		count++;
	}
	return count; // number of characters printed
}

void ST7735_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor,
		int16_t bgColor, uint8_t size) {
	uint8_t line;
	int32_t i, j;
	if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT) || ((x + 5 * size - 1) < 0)
			|| ((y + 8 * size - 1) < 0))
		return;

	for (i = 0; i < 6; i++) {
		if (i == 5)
			line = 0x0;
		else
			line = Font[(c * 5) + i];
		for (j = 0; j < 8; j++) {
			if (line & 0x1) {
				if (size == 1)
					ST7735_DrawPixel(x + i, y + j, textColor);
				else {
					ST7735_FillRectangle(x + (i * size), y + (j * size), size,
							size, textColor);
				}
			} else if (bgColor != textColor) {
				if (size == 1) // default size
					ST7735_DrawPixel(x + i, y + j, bgColor);
				else { // big size
					ST7735_FillRectangle(x + i * size, y + j * size, size, size,
							bgColor);
				}
			}
			line >>= 1;
		}
	}
}

void ST7735_Drawaxes(uint16_t axisColor, uint16_t bgColor, char *xLabel,
		char *yLabel1, uint16_t label1Color, char *yLabel2,
		uint16_t label2Color, int32_t ymax, int32_t ymin) {
	int i;

	Ymax = ymax;
	Ymin = ymin;
	Yrange = Ymax - Ymin;
	TimeIndex = 0;
	PlotBGColor = bgColor;
	LCD_CS0
	;
	ST7735_FillRectangle(0, 0, 128, 160, bgColor);
	ST7735_DrawFastHLine(10, 140, 101, axisColor);
	ST7735_DrawFastVLine(10, 17, 124, axisColor);
	for (i = 20; i <= 110; i = i + 10) {
		ST7735_DrawPixel(i, 141, axisColor);
	}
	for (i = 17; i < 120; i = i + 10) {
		ST7735_DrawPixel(9, i, axisColor);
	}
	i = 50;
	while ((*xLabel) && (i < 100)) {
		ST7735_DrawCharS(i, 145, *xLabel, axisColor, bgColor, 1);
		i = i + 6;
		xLabel++;
	}
	if (*yLabel2) { // two labels
		i = 26;
		while ((*yLabel2) && (i < 50)) {
			ST7735_DrawCharS(0, i, *yLabel2, label2Color, bgColor, 1);
			i = i + 8;
			yLabel2++;
		}
		i = 82;
	} else { // one label
		i = 42;
	}
	while ((*yLabel1) && (i < 120)) {
		ST7735_DrawCharS(0, i, *yLabel1, label1Color, bgColor, 1);
		i = i + 8;
		yLabel1++;
	}
	LCD_CS1
	;
}

void ST7735_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	uint8_t hi = color >> 8, lo = color;

	LCD_CS0
	;
	// Rudimentary clipping
	if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
		return;
	if ((x + w - 1) >= ST7735_WIDTH)
		w = ST7735_WIDTH - x;
	ST7735_SetAddressWindow(x, y, x + w - 1, y);

	while (w--) {
		lcd7735_sendData(hi);
		lcd7735_sendData(lo);
	}
	LCD_CS1
	;
}

void ST7735_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	uint8_t hi = color >> 8, lo = color;
	LCD_CS0
	;

	// Rudimentary clipping
	if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT))
		return;
	if ((y + h - 1) >= ST7735_HEIGHT)
		h = ST7735_HEIGHT - y;
	ST7735_SetAddressWindow(x, y, x, y + h - 1);

	while (h--) {
		lcd7735_sendData(hi);
		lcd7735_sendData(lo);
	}
	LCD_CS1
	;
}

void ST7735_FillRectangle(uint8_t x_start, uint8_t y_start, uint8_t width,
		uint8_t height, uint16_t color) {
	// clipping
	if ((x_start >= ST7735_WIDTH) || (y_start >= ST7735_HEIGHT))
		return;
	if ((x_start + width - 1) >= ST7735_WIDTH)
		width = ST7735_WIDTH - x_start;
	if ((y_start + height - 1) >= ST7735_HEIGHT)
		height = ST7735_HEIGHT - y_start;

	LCD_CS0
	;

	ST7735_SetAddressWindow(x_start, y_start, (x_start + width - 1),
			(y_start + height - 1));

	for (y_start = height; y_start > 0; y_start--) {
		for (x_start = width; x_start > 0; x_start--) {
			lcd7735_sendData(color >> 8);
			lcd7735_sendData(color);
		}
	}

	LCD_CS1
	; // Unselect

	return;
}

void ST7735_FillRectangleByPixel(uint16_t x_start, uint16_t y_start,
		uint16_t width, uint16_t height, uint16_t color) {
	// clipping
	if ((x_start >= ST7735_WIDTH) || (y_start >= ST7735_HEIGHT))
		return;
	if ((x_start + width - 1) >= ST7735_WIDTH)
		width = ST7735_WIDTH - x_start;
	if ((y_start + height - 1) >= ST7735_HEIGHT)
		height = ST7735_HEIGHT - y_start;

	for (uint16_t i = 0; i < height; i++) {
		for (uint16_t j = 0; j < width; j++) {
			print_uart(" x val %d y val %d \n", x_start + j, y_start + i);
			ST7735_DrawPixel(x_start + j, y_start + i, color);
		}
	}

	return;
}

void ST7735_FillScreen(uint16_t color) {
	ST7735_FillRectangle(0, 0, ST7735_WIDTH, ST7735_HEIGHT, color);
}

void ST7735_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		const uint16_t *data) {
	//	int16_t skipC = 0;
	//	int16_t originalWidth = w;
	//	int i = w*(h - 1);
	int m = 0;

	//  if((x >= ST7735_WIDTH) || ((y - h + 1) >= ST7735_HEIGHT) || ((x + w) <= 0) || (y < 0)){  // OLD
	//    return;
	//  }

	if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT) || ((x + w) <= 0)
			|| (y < 0)) { // NEW
		return;
	}
	if ((w > ST7735_WIDTH) || (h > ST7735_HEIGHT)) {

		return;
	}
	/*
	 if((x + w - 1) >= ST7735_WIDTH){
	 skipC = (x + w) - ST7735_WIDTH;
	 w = ST7735_WIDTH - x;
	 }

	 if((y - h + 1) < 0){
	 i = i - (h - y - 1)*originalWidth;
	 h = y + 1;
	 }

	 if(x < 0){
	 w = w + x;
	 skipC = -1*x;
	 i = i - x;
	 x = 0;
	 }
	 if(y >= ST7735_HEIGHT){
	 h = h - (y - ST7735_HEIGHT + 1);
	 y = ST7735_HEIGHT - 1;
	 }
	 */
	LCD_CS0
	; // Select

	// ST7735_SetAddressWindow(x, y-h+1, x+w-1, y); // OLD
	ST7735_SetAddressWindow(x, y, x + w - 1, y + h - 1); // NEW

	for (y = 0; y < h; y = y + 1) {
		for (x = 0; x < w; x = x + 1) {

			lcd7735_sendData((uint8_t) (data[m] >> 8));

			lcd7735_sendData((uint8_t) data[m]);
			m++;
			//    i = i + 1;
		}
		//    i = i + skipC;
		//    i = i - 2*originalWidth;
	}
	LCD_CS1
	; // Unselect
}
//===================================================================================================
void ST7735_InvertColors(bool invert) {
	// ST7735_Select();
	LCD_CS0
	;
	// ST7735_WriteCommand(invert ? ST7735_INVON : ST7735_INVOFF);
	lcd7735_sendCmd(invert ? ST7735_INVON : ST7735_INVOFF);
	LCD_CS1
	; // Unselect
}

void lcd7735_sendCmd(uint8_t cmd) {          // uint8_t       //unsigned char
	LCD_DC0; // Set DC low

	lcd7735_senddata(cmd);
	// flush_to_spi();
}

void lcd7735_sendData(uint8_t data) {  //uint8_t      //unsigned char
	LCD_DC1;  //Set DC HIGH
	lcd7735_senddata(data);
}

void lcd7735_senddata(uint8_t data) {
	HAL_SPI_Transmit(&hspi1, &data, sizeof(data), 0x1);
}

uint32_t ST7735_WriteString(uint16_t x, uint16_t y, const char *stringData,FontDef font, int16_t textColor, int16_t backgroundColor,	int16_t fontSize) {
	uint32_t count = 0;
	if (y > 15)
		return 0;
	while (*stringData) {
		ST7735_WriteCharS(x * (font.width - font.offset),y * (font.height - font.offset), *stringData, font, textColor,backgroundColor, fontSize);
		stringData++;
		x = x + 1;
		if (x > 20)
			return count; // number of characters printed
		count++;
	}
	return count; // number of characters printed
}

void ST7735_WriteCharS(int16_t x, int16_t y, char c, FontDef font,
		int16_t textColor, int16_t bgColor, uint8_t size) {
	uint16_t line;
	int32_t i, j, k = 0;
	int32_t x_start = 0;
	int32_t y_start = 0;
	int32_t fontPosition = 0;
	int16_t width_By_Column = 0;
	//	if ((x >= ST7735_WIDTH) || (y >= ST7735_HEIGHT) || ((x + 5 * size - 1) < 0)
	//			|| ((y + 8 * size - 1) < 0))
	//		return;
	for (i = 0; i < font.height + 1; i++) { // <== Height
		if (fontPosition == font.height * font.column)
			line = 0x0;
		else {
			x_start = 0;

			for (k = 0; k < font.column; k++) { // <== 3
				line = font.data[((c - 32) * font.height * font.column)
						+ fontPosition];

				width_By_Column = font.width / font.column;

				for (j = 0; j < width_By_Column; j++) { // <== Width 8 Bits
					if (line & 0x1) {
						if (size == 1)
							ST7735_DrawPixel(x + x_start, y + y_start,
									textColor);
						else {
							ST7735_FillRectangle(x + (j * size), y + (i * size),
									size, size, textColor);
						}
					} else if (bgColor != textColor) {
						if (size == 1) // default size
							ST7735_DrawPixel(x + x_start, y + y_start, bgColor);
						else { // big size
							ST7735_FillRectangle(x + j * size, y + i * size,
									size, size, bgColor);
						}
					}
					line >>= 1;
					x_start++;
				}
				fontPosition++;
			}
			y_start++;
		}
	}
}

void ST7735_draw_monochrome_vector_image(uint8_t x_start, uint8_t y_start,
		ImageMonochrome *image, uint16_t color, uint16_t background_color) {

	uint16_t i = 0;
	LCD_CS0;
	ST7735_SetAddressWindow(x_start, y_start, x_start + image->width - 1,
			y_start + image->height - 1);

	while (i < image->width * image->height) {
		if (image->data[i] == true) {
			lcd7735_sendData((uint8_t) (color >> 8));
			lcd7735_sendData((uint8_t) (color));
		} else {
			lcd7735_sendData((uint8_t) (background_color >> 8));
			lcd7735_sendData((uint8_t) (background_color));
		}

		i++;
	}

	LCD_CS1
	; // Unselect
	return;
}

void ST7735_draw_monochrome_vector_image_bckg(uint8_t x_start, uint8_t y_start,ImageColor *image, uint16_t color, uint16_t background_color)
{

	uint16_t i = 0;
	 LCD_CS0;
	ST7735_SetAddressWindow(x_start, y_start, x_start + image->width - 1,	y_start + image->height - 1);
	uint32_t count = 0;
	while (count < image->width * image->height)
	{
		for (uint8_t j = 0; j < image->data[i]; j++)
		{
			if (image->data[i + 1] == 1)
			{
				uint8_t data1 =  (color >> 8);
				uint8_t data2 = (color);

				lcd7735_sendData(data1);
				lcd7735_sendData(data2);
			} else {
				uint8_t data3 = (background_color >> 8);
				uint8_t data4 = (background_color);

				lcd7735_sendData(data3);
				lcd7735_sendData(data4);
			}
			count++;
		}
		i += 2;
	}

	LCD_CS1
	; // Unselect
	return;
}

void ST7735_draw_color_image(uint8_t x_start, uint8_t y_start,
		ImageColor *image) {
	int m = 0;
	int i = 0;
	LCD_CS0;
	ST7735_SetAddressWindow(x_start, y_start, x_start + image->width - 1,
			y_start + image->height - 1);

	uint32_t count = 0;
	while (count < image->width * image->height) {
		for (uint8_t j = 0; j < image->data[i]; j++) {
			lcd7735_sendData((uint8_t) (image->data[i + 1] >> 8));
			lcd7735_sendData((uint8_t) (image->data[i + 1]));

			count++;
		}
		i += 2;
	}

	LCD_CS1
	; // Unselect
	return;
}

void ST7735_draw_color_image_bckg(uint8_t x_start, uint8_t y_start,
		ImageColor *image) {
	int m = 0;
	int i = 0;
	LCD_CS0;
	ST7735_SetAddressWindow(x_start, y_start, x_start + image->width - 1,
			y_start + image->height - 1);

	// for (y_start = 0; y_start < image->height; y_start++)
	// {
	//   for (x_start = 0; x_start < image->width; x_start++)
	//   {

	//     lcd7735_sendData((uint8_t)(image->data[i] >> 8));
	//     lcd7735_sendData((uint8_t)(image->data[i]));
	//     m++;
	//     i++;
	//   }
	// }
	uint32_t count = 0;
	while (count < 33800) {
		for (uint8_t j = 0; j < image->data[i]; j++) {
			lcd7735_sendData((uint8_t) (image->data[i + 1] >> 8));
			lcd7735_sendData((uint8_t) (image->data[i + 1]));
			count++;
		}
		i += 2;
	}

	LCD_CS1
	; // Unselect
	return;
}

//void read_Display_ID(void)
//{
//	  uint8_t spiRxData[50] = {0};
//
//		LCD_CS0;
//		   LCD_DC0; //Set DC low
//		lcd7735_sendCmd(0x04);
//		  HAL_SPI_Receive(&hspi1, &spiRxData, 4, 0x1);
//		  HAL_UART_Transmit(&huart2, "\nHi: ", 2, 500);
//		  HAL_UART_Transmit(&huart2, spiRxData, 4, 500);
//	  LCD_CS1;  //Unselect
//}
