#ifndef tga_h
#define tga_h

#include <fstream>
#include <string>
#include <vector>

bool write_tga(const std::string& filename, float * colors, const int width, const int height);
bool write_ppm(const std::string& filename, float * colors, const int width, const int height);

#endif /* tga_h */
