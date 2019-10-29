#ifndef factory_h
#define factory_h

#include "parser.h"
#include "nff.h"
#include "ply.h"
#include "obj.h"

#define NFF "nff"
#define PLY "ply"
#define OBJ "obj"

class ParserFactory {
public:
    static Parser * getParser(std::string filename){
        std::string delimiter = ".";
        std::string type = filename.substr(filename.find(delimiter) + 1, filename.length() - filename.find(delimiter));
                
        if (type == NFF) {
            return new NFFParser;
        } else if (type == PLY){
            return new PLYParser;
        } else {
            printf("Could not find suitable parser.\n");
            exit(1);
        }
        return NULL;
    }
};

#endif /* factory_h */
