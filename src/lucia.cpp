#include "lucia.h"

// Points defined by 2 attributes: positions which are stored in vertices array and colors which are stored in colors array
float *colors;
float *vertices;

int size_vertices;
int size_colors;

Scene * scene = NULL;
Tracer * tracer = NULL;

int RES_X, RES_Y;

int WindowHandle = 0;

bool USE_GRID                   = false;
bool USE_ANTI_ALIASING          = false;
bool USE_DOF                    = false;
bool USE_SOFT_SHADOWS           = false;
bool USE_GLOSSY_REFLECTION      = false;

Grid * grid;

void printRenderProgress(float percentage){
    printf ("\r[%.2f%%]", percentage * 100.0);
    fflush(stdout);
}

void renderScene(std::string filename)
{
    // Record rendering start time.
    auto render_start = std::chrono::high_resolution_clock::now();
    
    int index_pos=0;
    int index_col=0;
    
    for (int y = 0; y < RES_Y; y++)
    {
        for (int x = 0; x < RES_X; x++)
        {
            Color color = tracer->color_pixel(x, y);
            
            vertices[index_pos++]= (float)x;
            vertices[index_pos++]= (float)y;
            colors[index_col++]= color.r;
            colors[index_col++]= color.g;
            colors[index_col++]= color.b;
        }
        
        printRenderProgress((float) y / (float) RES_Y);
    
    }
    printf("\rRender complete!\n");
    auto render_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> render_time = render_end - render_start;
    
    // Save rendering information to file.
    std::ofstream stats_file;
    stats_file.open(filename + ".txt");
    stats_file << "Render info:\n\n";
    stats_file << "FILE NAME         : " << filename << "\n" ;
    stats_file << "RESOLUTION        : " << RES_X << "x" << RES_Y << "\n";
    stats_file << "RENDERING TIME    : " << render_time.count() << " (s)\n";
    stats_file << "OBJECTS           : " << scene->GetObjects().size() << "\n";
    stats_file << "LIGHTS            : " << scene->GetLights().size() << "\n";
    stats_file << "MAXIMUM DEPTH     : " << MAX_DEPTH << "\n";
    stats_file << "SAMPLES PER PIXEL : " << 1 << "\n";
    stats_file.close();
    
    // Save render to file

    if(!write_tga(filename, colors, RES_X, RES_Y))
        printf("Error writing to file.\n");
    
    printf("\rRender sucessfully written as an image.\n" );
    printf("ELASPED TIME: %f (s)\n",render_time.count());

}


int main(int argc, char* argv[])
{
    // Set random seed.
    set_seed((int) time(NULL));
    
    // Create new scene.
    scene = new Scene();
    std::string filename = argv[1];
    

    // Parse scene into scene object
    Parser* parser = ParserFactory::getParser(filename);
    if (!(parser->load(filename, *scene))){
        int wait = 0;
        std::cin >> wait;
        return 0;
    }
    // Intialize grid
    grid = new Grid();
    grid->objects = scene->objects;
    grid->setup_cells();
    
    // Setup new tracer.
    tracer = new DistributedTracer(scene);
    
    // Turn on acceleration grid
    scene->grid = grid;
    tracer->set_aliasing_sampler(new Adaptive());

    // Use depth of field
    if (USE_DOF) {
        scene->camera = new LensCamera(scene->camera->eye, scene->camera->at, scene->camera->up, scene->camera->resX, scene->camera->resY,scene->camera->angle, scene->camera->hither, LENS_RADIUS, FOCAL_DISTANCE, ZOOM);
        scene->camera->set_lens_type(LENS_TYPE);
        scene->camera->set_dof_sampler(new Random(64));
    } else {
        scene->camera = new PinholeCamera(scene->camera->eye, scene->camera->at, scene->camera->up, scene->camera->resX, scene->camera->resY,scene->camera->angle, scene->camera->hither);
        scene->camera->set_lens_type(LENS_TYPE);
        scene->camera->set_dof_sampler(NULL);
    }

    // Use softshadows
    if (USE_SOFT_SHADOWS) {
        for(Light * light: scene->GetLights())
            light->set_area(new geometry::Rectangle(light->position, Vec3(0.6,0,0), Vec3(0,0.6,0), new Jittered(3*3)));
    } else {
        for(Light * light: scene->GetLights())
            light->set_area(new geometry::Rectangle(light->position, Vec3(0.6,0,0), Vec3(0,0.6,0), new Regular(1)));
    }

    if(USE_GLOSSY_REFLECTION)
        tracer->set_reflection_sampler(new Jittered(3*3));
    else        
        tracer->set_reflection_sampler(NULL);


	RES_X = scene->camera->GetResX();
	RES_Y = scene->camera->GetResY();

    size_vertices = 2 * RES_X * RES_Y * sizeof(float);
    size_colors = 3 * RES_X * RES_Y * sizeof(float);
    printf("DRAWING MODE: WRITE RENDER TO FILE\n");
    printf("Render resolution: %dx%d\n", RES_X, RES_Y);
    
    
    vertices = (float*)malloc(size_vertices);
    if (vertices==NULL) exit (1);
    
    colors = (float*)malloc(size_colors);
    if (colors==NULL) exit (1);
    
    renderScene(filename);

    exit(EXIT_SUCCESS);
}
///////////////////////////////////////////////////////////////////////
