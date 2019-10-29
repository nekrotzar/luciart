#ifndef ply_h
#define ply_h

#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>

#include "tinyply.h"
#include "parser.h"
#include "camera/lens.h"
#include "camera/pinhole.h"
#include "geometry/triangle.h"


class PLYParser : public Parser {
    
public:
    /**
     * Load scene attributes from an PLY files.
     * @param filename Name of the file to parse.
     * @return Returns true if file is loaded and parsed sucessfully, false otherwise.
     */
    bool load(std::string filename, Scene& scene);
};

#endif /* ply_h */
