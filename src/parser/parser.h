#ifndef parser_h
#define parser_h

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "scene.h"
#include "utility/constants.h"

class Parser {
public:
    virtual bool load(std::string filename, Scene& scene) = 0;
};

#endif /* parser_h */
