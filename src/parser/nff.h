#ifndef nff_h
#define nff_h

#include "parser.h"

#include "camera/lens.h"
#include "camera/pinhole.h"
#include "geometry/sphere.h"
#include "geometry/polygon.h"
#include "geometry/plane.h"
#include "geometry/triangle.h"
#include "geometry/patch.h"
#include "geometry/cone.h"
#include "geometry/cylinder.h"


class NFFParser : public Parser {

public:
    /**
     * Load scene attributes from an NFF files.
     * @param filename Name of the file to parse.
     * @return Returns true if file is loaded and parsed sucessfully, false otherwise.
     */
    bool load(std::string filename, Scene& scene);

private:
    /**
     * Parse scene attributes from a file.
     * @param file File to be parsed.
     * @return Returns true if file is parsed sucessfully.
     */
    bool parse_nff(FILE * file, Scene& scene);
    
    /**
     * Parse scene background color.
     * @param file File to be parsed.
     */
    void parseBackgroundColor(FILE * file, Scene& scene);
    
    /**
     * Parse scene camera attributes.
     * @param file File to be parsed.
     */
    void parseViewpoint(FILE * file, Scene& scene);
    
    /**
     * Parse light.
     * @param file File to be parsed.
     */
    void parseLight(FILE * file, Scene& scene);
    
    /**
     * Parse current fill material.
     * @param file File to be parsed.
     */
    void parseFill(FILE * file, Scene& scene);
    
    /**
     * Parse plane.
     * @param file File to be parsed.
     */
    void parsePlane(FILE * file, Scene& scene);
    
    /**
     * Parse sphere.
     * @param file File to be parsed.
     */
    void parseSphere(FILE * file, Scene& scene);
    
    /**
     * Parse cone or cylinder.
     * @param file File to be parsed.
     */
    void parseConeCylinder(FILE * file, Scene& scene);
    
    /**
     * Parse polygon.
     * @param file File to be parsed.
     */
    void parsePolygon(FILE * file, Scene& scene);
    
    /**
     * Parse polygon patch.
     * @param file File to be parsed.
     */
    void parsePolygonPatch(FILE * file, Scene& scene);
    
    /**
     * Parse comment.
     * @param file File to be parsed.
     */
    void parseComment(FILE * file);
    
    /**
     * Display parsing error.
     * @param m Error message.
     */
    void parsingError(std::string m);
};

#endif /* nff_h */
