#include "ws2812-rpi.h"
#include <unordered_map>
#include <iostream>

void setColor(NeoPixel* n, Color_t c);

Color_t Color(unsigned char r, unsigned char g, unsigned char b);

int main (int argc, char* argv[]) {
    std::unordered_map<std::string, Color_t> colors = {{"red", Color(255, 0, 0)}, {"blue", Color(0, 0, 255)}, 
                                            {"green", Color(0, 255, 0)}, {"orange", Color(255, 35, 0)}, {"white", Color(255, 255, 255)}, {"warm", Color(255, 50, 10)}};
    NeoPixel* n = new NeoPixel(168);
    if (argc > 1) {
        if (strcmp(argv[1], "clear") == 0) {
            n->clear();
            n->show();
        } else {
            setColor(n, colors[argv[1]]);
        }
    } else {
        std::cout << "No color set" << std::endl;
    }
    delete n;
    return 0;
}

void setColor(NeoPixel* n, Color_t c) {
    for (unsigned int i=0; i < n->numPixels(); ++i) {
        n->setPixelColor(i, c);
        n->show();
        usleep(1.0);
    }
}

Color_t Color(unsigned char r, unsigned char g, unsigned char b) {
    return Color_t (r, g, b);
}


