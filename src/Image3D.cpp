#define cimg_display 0
#include "include/CImg.h"
#include "Image3D.hpp"


void Image3DXYC::init(uint w, uint a, uint c) {
    width = w;
    height = a;
    channels = c;
    if (width*height*channels == 0) return;

    buff = new pixel_unit **[width];
    for (uint c = 0; c < width; c++) {
        buff[c] = new pixel_unit *[height];
        for (uint i = 0; i < height; i++)
            buff[c][i] = new pixel_unit[channels];
    }
}


Image3DXYC::Image3DXYC(uint width, uint height, uint channels) {
    init(width, height, channels);
}


Image3DXYC::Image3DXYC(const char *file, bool forceDefaultChannels) {
    cimg_library::CImg<pixel_unit> image(file);
    init(image.width(), image.height(), forceDefaultChannels ? 3 : image.spectrum());

    cimg_forXYC(image,x,y,c) {
        if (c < int(channels)) {
            at(x, y, c) = image(x,y,c);
        }
    }
}


Image3DXYC::~Image3DXYC() {
    if (width*height*channels == 0) return;

    for (uint c = 0; c < width; c++) {
        for (uint i = 0; i < height; i++)
            delete[] (buff[c][i]);
        delete[] buff[c];
    }
    delete[] buff;
}



void Image3DXYC::save(const char *const file) const {
    cimg_library::CImg<pixel_unit> image(width, height, 1, channels);
    cimg_forXYC(image,x,y,c) {
        image(x,y,c) = at(x, y, c);
    }
    image.save(file);
}


void Image3DXYC::print() const {
    //printf("lxa: %ux%u\n", i2d->width, i2d->height);
    for (uint x = 0; x < width; x++) {
        for (uint y = 0; y < height; y++) {
            printf("(");
            for (uint c = 0; c < channels; c++) {
                printf(c == 0 ? "%02hhX" : ",%02hhX", at(x, y, c));
            }
            printf(") ");
        }
        printf("\n");
    }
    printf("\n");
}
