#include "ws2812-rpi.h"
#include <unordered_map>
#include <iostream>

void led(Color_t color);

void led_off();

void setColor(NeoPixel* led, Color_t c);

Color_t Color(unsigned char r, unsigned char g, unsigned char b);


