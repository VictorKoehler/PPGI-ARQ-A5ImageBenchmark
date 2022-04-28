#pragma once
#include <cassert>
#include <string>

#define RED 0
#define GREEN 1
#define BLUE 2
#define ALPHA 3

typedef unsigned char default_pixel_unit;

#define __I3D__obj_assert(f, s, t) assert(f < width); assert(s < height); assert(t < channels);

struct Image3DXYC {
    typedef default_pixel_unit pixel_unit;
   protected:
    uint width, height, channels;
    pixel_unit*** buff;
    
    void init(uint w, uint h, uint c);

   public:
    /**
     * Cria um buffer de imagem não inicializado.
     */
    Image3DXYC(uint width, uint height, uint channels = 3);

    Image3DXYC() : Image3DXYC(0, 0, 0) {}

    /**
     * Cria um buffer de uma imagem existente.
     * forceDefaultChannels: Força o uso da quantidade padrão de channels.
     */
    Image3DXYC(const char *file, bool forceDefaultChannels);

    /**
     * Cria um buffer de uma imagem existente.
     */
    Image3DXYC(const char *const file) : Image3DXYC(file, false) { }

    ~Image3DXYC();


    constexpr inline         pixel_unit& at(uint x, uint y, uint c)       { __I3D__obj_assert(x, y, c) return buff[x][y][c]; }
    constexpr inline const   pixel_unit& at(uint x, uint y, uint c) const { __I3D__obj_assert(x, y, c) return buff[x][y][c]; }
    constexpr inline       auto& operator()(uint x, uint y, uint c)       { return at(x, y, c); }
    constexpr inline const auto& operator()(uint x, uint y, uint c) const { return at(x, y, c); }


    uint getWidth() const { return width; }
    uint getHeight() const { return height; }
    uint getChannels() const { return channels; }

    void print() const;

    void save(const char *const file) const;

    static const std::string __implementation_type() {
        return "Pointers@XYC";
    }
};

typedef Image3DXYC Image3D;
