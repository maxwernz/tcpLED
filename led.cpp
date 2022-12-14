#include "led.h"

void led(int color) {
    std::unordered_map<int, Color_t> colors = {{1, Color(255, 0, 0)}, {2, Color(0, 0, 255)}, {3, Color(0, 255, 0)}, {4, Color(255, 35, 0)}, {5, Color(255, 255, 255)}, {6, Color(255, 50, 10)}};
    NeoPixel* led = new NeoPixel(168);
    setColor(led, colors[color]);
    
    delete led;
}

// char* color_picker(std::unordered_map<const char*, Color_t> colors) {
//     char* col;
//     puts("Wich Color do you want?");
//     for (auto& it : colors) {
//         puts(it.first);
//     }
//     std::cout << "Color: ";
//     std::cin >> col;
//     return col;
// }

void led_off() {
    NeoPixel* led = new NeoPixel(168);
    led->clear();
    led->show();
    delete led;
}

void setColor(NeoPixel* led, Color_t c) {
    for (unsigned int i=0; i < led->numPixels(); ++i) {
        led->setPixelColor(i, c);
        led->show();
        usleep(1.0);
    }
}

Color_t Color(unsigned char r, unsigned char g, unsigned char b) {
    return Color_t (r, g, b);
}


