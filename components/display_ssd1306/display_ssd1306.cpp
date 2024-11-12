/***********************************************************************************************
* FILENAME       : display_ssd1306.cpp
 * VERSION        : 0.0.1
 * DESCRIPTION    : This code runs the menu on the ssd1306 display
 *
 * PUBLIC FUNCTIONS:
 *    - mode_task()
 *    - uart_task()
 *    - app_main()
 *
 * NOTES:
 *    Prefixes denote variable or return types:
 *    - "c" for char, "s" for short, "v" for void, "u" for unsigned, and "x" for non-standard types.
 *
 * AUTHOR         : Tjark Ziehm
 * START DATE     : July 6, 2024
 * COPYRIGHT      : © 2024 Tjark Ziehm
 * LICENCE        : CC BY-NC-ND 4.0
 * VERSION FORMAT : <major>.<minor>.<patch>
 *
 * Contributors   :
 *
 * CHANGE LOG:
 *    - v0.0.1:
 *    - v0.0.2:
 *    - v0.1.0:
 *    - v1.0.0:
 ***********************************************************************************************/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"


#include "display_ssd1306.h"

#include "../display_api/ssd1306.h"
#include "../display_api/font8x8_basic.h"

/*
 You have to set this config value with menuconfig
 CONFIG_INTERFACE

 for i2c
 CONFIG_MODEL
 CONFIG_SDA_GPIO
 CONFIG_SCL_GPIO
 CONFIG_RESET_GPIO

 for SPI
 CONFIG_CS_GPIO
 CONFIG_DC_GPIO
 CONFIG_RESET_GPIO
*/

#define TAG "SSD1306"

uint8_t menu_on[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
0xff, 0xff, 0xff, 0x00, 0x30, 0x00, 0x00, 0x01, 0x00, 0x30, 0x00, 0x00, 0x01, 0x00, 0x30, 0x00,
0x00, 0x01, 0x00, 0x30, 0x00, 0x00, 0x01, 0x00, 0x30, 0x00, 0x00, 0x01, 0x00, 0x30, 0x00, 0x00,
0x01, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t menu_off[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff,
0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff,
0xff, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// https://www.mischianti.org/2021/07/14/ssd1306-oled-display-draw-images-splash-and-animations-2/
uint8_t logo_mini[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x07, 0xe1, 0xf0, 0x00,
0x01, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x1e, 0x06, 0x00, 0x38, 0x3e, 0x07, 0x00,
0x70, 0x1e, 0x07, 0x00, 0x71, 0x1c, 0x63, 0x80, 0x63, 0x8c, 0x63, 0x80, 0x63, 0x8c, 0x73, 0x80,
0xe3, 0x8c, 0xf1, 0x80, 0xe3, 0x8c, 0xf1, 0x80, 0x63, 0x8c, 0x71, 0x80, 0x63, 0x8c, 0x63, 0x80,
0x71, 0x1c, 0x63, 0x80, 0x70, 0x1e, 0x03, 0x00, 0x38, 0x3e, 0x07, 0x00, 0x38, 0x3e, 0x06, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0xf0, 0x00, 0x03, 0xff, 0xe0, 0x00,
0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t ball[] = {
// 'ball', 10x11px
0x18, 0x7c, 0x7e, 0xfe, 0xfe, 0x7e, 0x7c, 0x18
};

uint8_t logo_21x21[] = {
0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x07, 0xff, 0xc0, 0x07, 0x81, 0xe0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x38, 0x7c, 0x1c, 0x70, 0x3c, 0x0c, 0x73, 0x38, 0x8e, 0x63, 0x18, 0xc6, 0x63, 0x19,
0xc6, 0xe7, 0x99, 0xc6, 0xe7, 0x99, 0xc6, 0x63, 0x19, 0xc6, 0x63, 0x18, 0xc6, 0x73, 0x38, 0x8e,
0x70, 0x3c, 0x0c, 0x38, 0x7c, 0x1c, 0x00, 0x18, 0x08, 0x00, 0x00, 0x00, 0x07, 0x81, 0xe0, 0x07,
0xff, 0xc0, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00
};

uint8_t logo_16x16[] = {
0x01, 0x80, 0x0f, 0xf0, 0x0c, 0x30, 0x00, 0x00, 0x63, 0xc6, 0x41, 0x86, 0xc9, 0xb2, 0xcd, 0xb3,
0xcd, 0xb2, 0xc9, 0xb2, 0x49, 0x86, 0x63, 0xc6, 0x00, 0x00, 0x08, 0x30, 0x0f, 0xf0, 0x03, 0xc0
};

uint8_t logo_19x19[] = {
0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x07, 0xff, 0xc0, 0x07, 0x81, 0xe0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x38, 0x7c, 0x1c, 0x70, 0x3c, 0x0c, 0x73, 0x38, 0x8e, 0x63, 0x18, 0xc6, 0x63, 0x19,
0xc6, 0xe7, 0x99, 0xc6, 0xe7, 0x99, 0xc6, 0x63, 0x19, 0xc6, 0x63, 0x18, 0xc6, 0x73, 0x38, 0x8e,
0x70, 0x3c, 0x0c, 0x38, 0x7c, 0x1c, 0x00, 0x18, 0x08, 0x00, 0x00, 0x00, 0x07, 0x81, 0xe0, 0x07,
0xff, 0xc0, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00
};

uint8_t pos_logo[1024] = {
// 'B_0622_POS_Logo(1)(1)', 128x32px
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xf0, 0x01, 0x80, 0x0e, 0x3f, 0xe0, 0x03, 0x1f, 0xc4, 0x7c, 0x07, 0xc7, 0xf0, 0x7e, 0x3f, 0x1f,
0xf0, 0x00, 0x80, 0x0e, 0x3f, 0xe0, 0x03, 0x1f, 0x84, 0x38, 0x03, 0x87, 0xc0, 0x1e, 0x1f, 0x1f,
0xf0, 0x01, 0x80, 0x0e, 0x3f, 0xe0, 0x03, 0x0f, 0x8c, 0x30, 0x01, 0xc7, 0xff, 0xfe, 0x0f, 0x1f,
0xff, 0x1f, 0x8f, 0xfe, 0x3f, 0xe3, 0xff, 0x0f, 0x8c, 0x31, 0xe1, 0xc7, 0xf1, 0xe6, 0x0f, 0x1f,
0xff, 0x1f, 0x8f, 0xfe, 0x3f, 0xe3, 0xff, 0x8f, 0x0c, 0x31, 0xf3, 0xc6, 0x71, 0xe6, 0x07, 0x1f,
0xff, 0x1f, 0x8f, 0xfe, 0x3f, 0xe3, 0xff, 0x87, 0x1c, 0x30, 0x3f, 0xc6, 0xd9, 0x26, 0x03, 0x1f,
0xff, 0x1f, 0x80, 0x0e, 0x3f, 0xe0, 0x03, 0xc7, 0x1c, 0x38, 0x07, 0xc6, 0xc9, 0x32, 0x03, 0x1f,
0xff, 0x1f, 0x80, 0x0e, 0x3f, 0xe0, 0x03, 0xc6, 0x1c, 0x3c, 0x03, 0xc6, 0xc9, 0x32, 0x21, 0x1f,
0xff, 0x1f, 0x87, 0xfe, 0x3f, 0xe1, 0xff, 0xc2, 0x3c, 0x3f, 0x01, 0xc6, 0xc9, 0x32, 0x31, 0x1f,
0xff, 0x1f, 0x8f, 0xfe, 0x3f, 0xe3, 0xff, 0xe2, 0x3c, 0x3f, 0xe1, 0xc6, 0xd9, 0x26, 0x30, 0x1f,
0xff, 0x1f, 0x8f, 0xfe, 0x3f, 0xe3, 0xff, 0xe0, 0x3c, 0x21, 0xf1, 0xc6, 0x71, 0xe6, 0x38, 0x1f,
0xff, 0x1f, 0x8f, 0xfe, 0x3f, 0xe3, 0xff, 0xe0, 0x7c, 0x31, 0xf1, 0xc6, 0x71, 0xc6, 0x3c, 0x1f,
0xff, 0x1f, 0x80, 0x0e, 0x00, 0x60, 0x03, 0xf0, 0x7c, 0x30, 0x01, 0xc7, 0xff, 0x8e, 0x3c, 0x1f,
0xff, 0x1f, 0x80, 0x0e, 0x00, 0x60, 0x01, 0xf0, 0xfc, 0x38, 0x03, 0xc7, 0x80, 0x1e, 0x3e, 0x1f,
0xff, 0x1f, 0x80, 0x0e, 0x00, 0x60, 0x03, 0xf0, 0xfc, 0x7c, 0x07, 0xc7, 0xc0, 0x7e, 0x3e, 0x1f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0x1f, 0xc3, 0xf1, 0xff, 0xc7, 0xfb, 0xff, 0xf7, 0xf7, 0xff, 0xff, 0x1f, 0xfd, 0xf6, 0xff,
0xff, 0x5f, 0xbb, 0xf3, 0xff, 0xef, 0x3b, 0x9d, 0xf7, 0x77, 0x1c, 0xfe, 0x7c, 0x1c, 0x76, 0xff,
0xff, 0x7f, 0xbb, 0xf9, 0xff, 0xee, 0x1b, 0x0d, 0x76, 0x77, 0x5d, 0x7e, 0x6d, 0x4d, 0x30, 0xff,
0xff, 0x7f, 0x9b, 0xfc, 0xff, 0xee, 0x7b, 0x3e, 0x77, 0x37, 0x5d, 0x7f, 0x6d, 0x4d, 0x76, 0xff,
0xff, 0x7f, 0xc7, 0xb9, 0xff, 0xef, 0x3b, 0x9e, 0xff, 0x7f, 0xbf, 0x7f, 0x8d, 0xfc, 0x76, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

SSD1306_t dev;
bool button_pressed = false;

void display_button_response(){
    if(button_pressed){
       ssd1306_bitmaps(&dev, 120, 3, ball, 8, 8, false);
    }else{
        ssd1306_clear_screen(&dev, false);
    }
}

void display_Settings(){
    ssd1306_clear_screen(&dev, false);
    int bitmapWidth = 2*8;
	int width = ssd1306_get_width(&dev);
	int xpos = width / 2; // center of width
	xpos = xpos - bitmapWidth/2;
	int ypos = 16;
	ESP_LOGD(TAG, "width=%d xpos=%d", width, xpos);

	ssd1306_bitmaps(&dev, 0, 0, logo_16x16, 16, 16, false);
    ssd1306_display_text_box1(&dev, 0, 30, "Settings", 9, 9, false, 0);
    ssd1306_display_text_box1(&dev, 3, 0, "1/8", 4, 4, false, 0);
    ssd1306_display_text_box1(&dev, 1, 30, "Firmware", 8, 8, false, 0);
    ssd1306_display_text_box1(&dev, 3, 30, "0009", 4, 4, false, 0);
    ssd1306_bitmaps(&dev, 120, 3, ball, 8, 8, false);
    ssd1306_bitmaps(&dev, 120, 13, ball, 8, 8, false);
    ssd1306_bitmaps(&dev, 120, 23, ball, 8, 8, false);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void display_MainMenu(){
    ssd1306_clear_screen(&dev, false);
    int bitmapWidth = 2*8;
	int width = ssd1306_get_width(&dev);
	int xpos = width / 2; // center of width
	xpos = xpos - bitmapWidth/2;
	int ypos = 16;
	ESP_LOGD(TAG, "width=%d xpos=%d", width, xpos);
	ssd1306_clear_screen(&dev, false);
	ssd1306_bitmaps(&dev, 0, 5, logo_19x19, 24, 24, false);

    ssd1306_display_text_box1(&dev, 0, 30, "1478 ", 5, 5, false, 0);
    ssd1306_display_text_box1(&dev, 0, 70, "Watt", 4, 4, false, 0);

    ssd1306_display_text_box1(&dev, 3, 30, "0009", 4, 4, false, 0);
    ssd1306_display_text_box1(&dev, 3, 60, "|", 1, 1, false, 0);
    ssd1306_display_text_box1(&dev, 3, 70, "0001", 4, 4, false, 0);

    ssd1306_bitmaps(&dev, 120, 3, ball, 8, 8, false);
    ssd1306_bitmaps(&dev, 120, 13, ball, 8, 8, false);
    ssd1306_bitmaps(&dev, 120, 23, ball, 8, 8, false);

    ssd1306_bitmaps(&dev, 110, 3, ball, 8, 8, false);
    ssd1306_bitmaps(&dev, 110, 13, ball, 8, 8, false);
    ssd1306_bitmaps(&dev, 110, 23, ball, 8, 8, false);

	vTaskDelay(2000 / portTICK_PERIOD_MS);
}



void display_DebugMenu(){

}

void display_BootMenu0(){
    ssd1306_clear_screen(&dev, false);
    int bitmapWidth = 4*8;
	int width = ssd1306_get_width(&dev);
	int xpos = width / 2; // center of width
	xpos = xpos - bitmapWidth/2;
	int ypos = 16;
	ESP_LOGD(TAG, "width=%d xpos=%d", width, xpos);
	ssd1306_clear_screen(&dev, false);
	ssd1306_bitmaps(&dev, 0, 0, pos_logo, 128, 32, false);
	vTaskDelay(2000 / portTICK_PERIOD_MS);


#if CONFIG_SSD1306_128x64
	ssd1306_clear_screen(&dev, false);
	ssd1306_bitmaps(&dev, 0, 0, pos_logo, 128, 64, false);
	vTaskDelay(2000 / portTICK_PERIOD_MS);

	for(int i=0;i<64;i++) {
		ssd1306_wrap_arround(&dev, SCROLL_UP, 0, 127, 0);
	}
	vTaskDelay(2000 / portTICK_PERIOD_MS);

	ssd1306_clear_screen(&dev, false);
	ssd1306_bitmaps(&dev, 0, 0, pos_logo, 128, 64, false);
	vTaskDelay(2000 / portTICK_PERIOD_MS);
#endif // CONFIG_SSD1306_128x64
}

void display_BootMenu1(void){
        ssd1306_clear_screen(&dev, false);
        ssd1306_display_text_box1(&dev, 0, 0, "Ver.", 7, 7, false, 100);
    	ssd1306_display_text_box1(&dev, 0, 40, "01.02.03", 8, 8, false, 100);
		//ssd1306_display_text_box1(&dev, 0, 60, "01.02.03", 4, 26, false, 2);
        ssd1306_display_text_box1(&dev, 2, 0, "Time", 4, 4, false, 100);
    	ssd1306_display_text_box1(&dev, 2, 40, "09:45", 5, 5, false, 100);
		//ssd1306_display_text_box1(&dev, 0, 60, "09:45", 8, 26, false, 2);
        ssd1306_display_text_box1(&dev, 3, 0, "Date", 4, 4, false, 100);
    	ssd1306_display_text_box1(&dev, 3, 40, "23.11.2024", 10, 10, false, 100);
		//ssd1306_display_text_box1(&dev, 0, 60, "23.11.2024", 12, 26, false, 2);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void display_LoadMenu(){
    ssd1306_clear_screen(&dev, false);
    int bitmapWidth = 4*8;
	int width = ssd1306_get_width(&dev);
	int xpos = width / 2; // center of width
	xpos = xpos - bitmapWidth/2;
	int ypos = 16;
	ESP_LOGD(TAG, "width=%d xpos=%d", width, xpos);
	ssd1306_clear_screen(&dev, false);
	ssd1306_bitmaps(&dev, 50, 5, logo_mini, 32, 26, false);
	vTaskDelay(2000 / portTICK_PERIOD_MS);

	for(int i=0;i<128;i++) {
		ssd1306_wrap_arround(&dev, SCROLL_RIGHT, 0, 3, 0);
	}
	vTaskDelay(2000 / portTICK_PERIOD_MS);

}


void activate_display(void)
{

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is i2c");
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
	dev._flip = true;
	ESP_LOGW(TAG, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
	ESP_LOGI(TAG, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGI(TAG, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
#endif // CONFIG_SSD1306_128x32

	ssd1306_contrast(&dev, 0xff);


#if 0
	// for test code
	int srcBits = 7;
	int dstBits = 0;
	for (int i=0;i<8;i++) {
		uint8_t dst = 0;
		dst = ssd1306_copy_bit(0xf0, srcBits, dst, dstBits);
		ESP_LOGI(TAG, "dst=%02x", dst);
		srcBits--;
		dstBits++;
	}
	srcBits = 7;
	dstBits = 0;
	for (int i=0;i<8;i++) {
		uint8_t dst = 0;
		dst = ssd1306_copy_bit(0x0f, srcBits, dst, dstBits);
		ESP_LOGI(TAG, "dst=%02x", dst);
		srcBits--;
		dstBits++;
	}
#endif

	while(1) {
        //display_BootMenu0();
        //display_BootMenu1();
        //display_LoadMenu();
        //display_MainMenu();
        display_Settings();
	}
}
