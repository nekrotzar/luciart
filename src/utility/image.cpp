#include "image.h"

bool write_tga(const std::string& name, float * colors, const int width, const int height){
    /**
     * TGA file format
     * http://www.paulbourke.net/dataformats/tga/
     */
    
    FILE * image;
    std::string filename = name;
    filename.append(".tga");
    image = fopen(filename.c_str(), "w");
    
    if (!image)
        return false;
    
    // Image header
    unsigned char header[18] = { 0 };
    header[  2 ] = 2;  // truecolor
    header[ 12 ] =  width        & 0xFF;
    header[ 13 ] = (width  >> 8) & 0xFF;
    header[ 14 ] =  height       & 0xFF;
    header[ 15 ] = (height >> 8) & 0xFF;
    header[ 16 ] = 24;
    
    // Write header
    fwrite(header, 1, 18, image);
    
    // Write pixel colors
    int index;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            index = x + y * width;

            putc(int(colors[index * 3 + 2] * 255), image);   // Blue
            putc(int(colors[index * 3 + 1] * 255), image);   // Green
            putc(int(colors[index * 3 + 0] * 255), image);   // Red
        }
    }
    fclose(image);
    return true;
}

bool write_ppm(const std::string& name, float * colors, const int width, const int height){
    FILE * image;
    
    std::string filename = name;
    filename.append(".ppm");
    
    image = fopen(filename.c_str(), "wb");
    
    if (!image)
        return false;
    
    // Write header
    fprintf(image,"P6\n");
    fprintf(image,"%d %d\n", width, height);
    fprintf(image,"255\n");
    
    // Write pixel colors
    int index;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            index = x + ((height - 1) - y) * width;
            
            static unsigned char color [3];
            color[0] = char(int(colors[index * 3 + 0] * 255));   // Red
            color[1] = char(int(colors[index * 3 + 1] * 255));   // Green
            color[2] = char(int(colors[index * 3 + 2] * 255));   // Blue
            
            fwrite(color, 1, 3, image);
        }
    }

    fwrite(colors, 1, width * height * 3, image);
    
    fclose(image);
    return true;
}
