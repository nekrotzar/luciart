#ifndef obj_h
#define obj_h

#include "parser.h"
#include "geometry/triangle.h"
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>


class OBJParser : public Parser {
    
public:
    /**
     * Load scene attributes from an OBJ files.
     * @param filename Name of the file to parse.
     * @return Returns true if file is loaded and parsed sucessfully, false otherwise.
     */
    bool load(std::string filename, Scene& scene);
};

#endif /* obj_h */
