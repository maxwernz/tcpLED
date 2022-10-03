#include "led.h"

void led(Color_t color) {
    std::unordered_map<const char*, Color_t> colors = {{"red", Color(255, 0, 0)}, {"blue", Color(0, 0, 255)}, {"green", Color(0, 255, 0)}, {"orange", Color(255, 35, 0)}, {"white", Color(255, 255, 255)}, {"warm", Color(255, 50, 10)}};
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


