#include "ws2812-rpi.h"
#include <unordered_map>
#include <iostream>

void led();

char* color_picker(std::unordered_map<const char*, Color_t> colors);

void led_off();

void setColor(NeoPixel* led, Color_t c);

Color_t Color(unsigned char r, unsigned char g, unsigned char b);


