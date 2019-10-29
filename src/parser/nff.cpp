#include "nff.h"

bool NFFParser::load(std::string filename, Scene& scene){
    const char * path = filename.c_str();
    FILE * file;
    
    if(!(file = fopen(path, "r"))){
        printf("Could not open NFF file: %s\n", path);
        return false;
    }
    
    if(!parse_nff(file, scene)){
        printf("Error while parsing NFF file\n");
        return false;
    }
    
    fclose(file);
    
    return true;
}

bool NFFParser::parse_nff(FILE * file, Scene& scene){
    int cursor;
    
    while((cursor = getc(file)) != EOF){
        switch (cursor) {
            case ' ':
            case '\n':
            case '\t':
            case '\f':
            case '\r': continue;
                
            case '#':
                parseComment(file);
                break;
            case 'b':
                parseBackgroundColor(file, scene);
                break;
            case 'v':
                parseViewpoint(file, scene);
                break;
            case 'l':
                parseLight(file, scene);
                break;
            case 'f':
                parseFill(file, scene);
                break;
            case 'p':
            {
                int next = getc(file);
                switch (next) {
                    case ' ':
                        parsePolygon(file, scene);
                        break;
                    case 'p':
                        parsePolygonPatch(file, scene);
                        break;
                    case 'l':
                        parsePlane(file, scene);
                        break;
                    default:
                        break;
                }
            }
                break;
            case 'c':
                parseConeCylinder(file, scene);
                break;
            case 's':
                parseSphere(file, scene);
                break;
            default:
                printf("Unknown NFF primitive code: %c\n", cursor);
                exit(1);
        }
    }
    return true;
}

void NFFParser::parsingError(std::string m){
    const char * message = m.c_str();
    std::cout << "Parsing error: " << message << std::endl;
    exit(1);
}

void NFFParser::parseBackgroundColor(FILE * file, Scene& scene){
    
    if ((fscanf(file, "%f %f %f", &scene.background.r, &scene.background.g, &scene.background.b ) != 3)) {
        parsingError("Background color.");
    }
}

void NFFParser::parseViewpoint(FILE *file, Scene& scene){
    Vec3 eye(0,0,0), at(0,0,0), up(0,0,0);
    float angle;
    float hither;
    int x, y;
    
    // Parse eye vector
    if((fscanf(file, " from %lf %lf %lf", &eye.x, &eye.y, &eye.z ) != 3)){
        parsingError("Viewpoint eye vector.");
    }
    // Parse at vector
    if((fscanf(file, " at %lf %lf %lf", &at.x, &at.y, &at.z ) != 3)){
        parsingError("Viewpoint at vector.");
    }
    // Parse up vector
    if((fscanf(file, " up %lf %lf %lf", &up.x, &up.y, &up.z ) != 3)){
        parsingError("Viewpoint up vector.");
    }
    // Parse angle
    if((fscanf(file, " angle %f", &angle) != 1)){
        parsingError("Viewpoint angle.");
    }
    // Parse hither
    if((fscanf(file, " hither %f", &hither ) != 1)){
        parsingError("Viewpoint hither.");
    }
    // Parse resolution
    if((fscanf(file, " resolution %d %d", &x, &y) != 2)){
        parsingError("Viewpoint resolution.");
    }

    (&scene)->camera = new Camera(eye, at, up, x, y, angle, hither);
}

void NFFParser::parseLight(FILE *file, Scene& scene){
    Vec3 position(0.0, 0.0, 0.0);
    Color color(0.0, 0.0, 0.0);
    
    if(fscanf(file, "%lf %lf %lf", &position.x, &position.y, &position.z) != 3){
        parsingError("Light position.");
    }
    
    int option = fscanf(file, "%f %f %f",&color.r, &color.g, &color.b);
    switch (option) {
        case 0:
            color = Color(1.0, 1.0, 1.0);
            break;
        case 3:
            break;
        default:
            parsingError("Light color.");
    }
    scene.lights.push_back(new Light(position, color));
}

void NFFParser::parseFill(FILE *file, Scene& scene){
    if ((fscanf(file, "%f %f %f", &scene.fill.color.r, &scene.fill.color.g, &scene.fill.color.b) != 3)) {
        parsingError("Fill material color.");
    }
    if ((fscanf(file, "%f %f %f %f %f", &scene.fill.diffuse, &scene.fill.specular, &scene.fill.shininess, &scene.fill.transmittance, &scene.fill.ior) != 5)) {
        parsingError("Fill material component.");
    }
}

void NFFParser::parsePlane(FILE *file, Scene& scene){
    Vec3 point1, point2, point3;
    
    if ((fscanf(file, "%lf %lf %lf", &point1.x, &point1.y, &point1.z) != 3)) {
        parsingError("Plane first point.");
    }
    if ((fscanf(file, "%lf %lf %lf", &point2.x, &point2.y, &point2.z) != 3)) {
        parsingError("Plane second point.");
    }
    if ((fscanf(file, "%lf %lf %lf", &point3.x, &point3.y, &point3.z) != 3)) {
        parsingError("Plane third point.");
    }
    scene.objects.push_back(new Plane(point1, point2, point3, scene.fill));
}

void NFFParser::parseSphere(FILE *file, Scene& scene){
    Vec3 center;
    double radius;
    
    if ((fscanf(file, "%lf %lf %lf %lf", &center.x, &center.y, &center.z, &radius) != 4)) {
        parsingError("Sphere.");
    }
    scene.objects.push_back(new Sphere(center, radius, scene.fill));
}

void NFFParser::parseConeCylinder(FILE * file, Scene& scene){
    Vec3 base, apex;
    double baseRadius, apexRadius;
    
    if (fscanf(file, "%lf %lf %lf %lf %lf %lf %lf %lf", &base.x, &base.y, &base.z, &baseRadius, &apex.x, &apex.y, &apex.z, &apexRadius) != 8){
        parsingError("Cone/cylinder.");
    }
    
    if (baseRadius == apexRadius) {
        scene.objects.push_back(new Cylinder(base, apex, baseRadius, apexRadius, scene.fill));
    } else {
        scene.objects.push_back(new Cone(base, apex, baseRadius, apexRadius, scene.fill));
    }
}

void NFFParser::parsePolygon(FILE * file, Scene& scene){
    int numVertices;
    
    if (fscanf(file, " %d", &numVertices) != 1) {
        parsingError("Polygon vertex number.");
    }
    
    std::vector<Vec3> vertices;
    Vec3 vertex_t;
    
    for (int v = 0; v < numVertices; v++) {
        if (fscanf(file, "%lf %lf %lf", &vertex_t.x, &vertex_t.y, &vertex_t.z ) != 3) {
            parsingError("Polygon vertex.");
        }
        vertices.push_back(vertex_t);
    }
    
   if (numVertices == 3) {
     scene.objects.push_back(new Triangle(vertices[0], vertices[1], vertices[2], scene.fill));
   } else {
      scene.objects.push_back(new Polygon(numVertices, vertices, scene.fill));
    }
}

void NFFParser::parsePolygonPatch(FILE * file, Scene& scene){
    int numVertices;
    
    if (fscanf(file, " %d", &numVertices) != 1) {
        parsingError("Polygon patch vertex number.");
    }
    
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    Vec3 vertex_t, normal_t;
    
    for (int v = 0; v < numVertices; v++) {
        if (fscanf(file, "%lf %lf %lf %lf %lf %lf", &vertex_t.x, &vertex_t.y, &vertex_t.z, &normal_t.x, &normal_t.y, &normal_t.z ) != 6) {
            parsingError("Polygon patch vertex or normal.");
        }
        vertices.push_back(vertex_t);
        normals.push_back(normal_t);
    }
    scene.objects.push_back(new PolygonPatch(numVertices, vertices, normals, scene.fill));
}

void NFFParser::parseComment(FILE *file){
    const int comment_size = 1000;
    char line[comment_size];
    fgets(line, comment_size, file);
}
