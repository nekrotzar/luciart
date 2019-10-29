#include "ply.h"

bool PLYParser::load(std::string filename, Scene &scene){
    try {
        // Read the file and create a std::istringstream suitable
        // for the lib -- tinyply does not perform any file i/o.
        std::ifstream ss(filename, std::ios::binary);
        
        if (ss.fail())
        {
            throw std::runtime_error("failed to open " + filename);
        }
        
        tinyply::PlyFile file;
        
        file.parse_header(ss);
        
        std::cout << "================================================================\n";
        
        for (auto c : file.get_comments()) std::cout << "Comment: " << c << std::endl;
        
        for (auto e : file.get_elements())
        {
            std::cout << "element - " << e.name << " (" << e.size << ")" << std::endl;
            for (auto p : e.properties)
            {
                std::cout << "\tproperty - " << p.name << " (" << tinyply::PropertyTable[p.propertyType].str << ")" << std::endl;
            }
        }
        
        std::cout << "================================================================\n";
        
        // Tinyply 2.0 treats incoming data as untyped byte buffers. It's now
        // up to users to treat this data as they wish. See below for examples.
        std::shared_ptr<tinyply::PlyData> vertices, normals, colors, faces, texcoords;
        
        // The header information can be used to programmatically extract properties on elements
        // known to exist in the file header prior to reading the data. For brevity of this sample, properties
        // like vertex position are hard-coded:
        try { vertices = file.request_properties_from_element("vertex", { "x", "y", "z" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }
        
        try { normals = file.request_properties_from_element("vertex", { "nx", "ny", "nz" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }
        
        try { colors = file.request_properties_from_element("vertex", { "red", "green", "blue", "alpha" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }
        
        try { faces = file.request_properties_from_element("face", { "vertex_indices" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }
        
        try { texcoords = file.request_properties_from_element("face", { "texcoord" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }
        
        std::chrono::high_resolution_clock c;
        
        std::chrono::time_point<std::chrono::high_resolution_clock> before =  c.now();
        file.read(ss);
        std::chrono::time_point<std::chrono::high_resolution_clock> after = c.now();
        
        // Good place to put a breakpoint!
        std::cout << "Parsing took " << (double)std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count() << " ms: " << std::endl;
        if (vertices) std::cout << "\tRead " << vertices->count << " total vertices "<< std::endl;
        if (normals) std::cout << "\tRead " << normals->count << " total vertex normals " << std::endl;
        if (colors) std::cout << "\tRead " << colors->count << " total vertex colors "<< std::endl;
        if (faces) std::cout << "\tRead " << faces->count << " total faces (triangles) " << std::endl;
        if (texcoords) std::cout << "\tRead " << texcoords->count << " total texcoords " << std::endl;
        
        
        // Example: type 'conversion' to your own native types - Option A
        /* TODO: Only reads triangles */

        const size_t numVerticesBytes = vertices->buffer.size_bytes();
        struct float3 { float x, y, z; };
        std::vector<float3> temp(vertices->count);
        std::memcpy(temp.data(), vertices->buffer.get(), numVerticesBytes);
        std::vector<Vec3> verts;
        
        for (auto v : temp) {
            verts.push_back(Vec3(v.x, v.y, v.z));
        }
        
        const size_t numFacesBytes = faces->buffer.size_bytes();
        struct index3 {int a, b, c;};
        std::vector<index3> tempo(faces->count);
        std::memcpy(tempo.data(), faces->buffer.get(), numFacesBytes);
        
        scene.background = Color(0.078,0.361,0.753);
        Material m = Material(Color(0.2,0.8,0.2), 0.5, 0.01, 30, 0.0, 1);
        
        for (auto f : tempo) {
            scene.objects.push_back(new Triangle(verts[f.c], verts[f.b], verts[f.a], m));
        }

        scene.lights.push_back(new Light(Vec3(-0.1, 0.2, 0.1), Color(1.0,1.0,1.0)));
        scene.lights.push_back(new Light(Vec3(1, -4, 4), Color(1.0,1.0,1.0)));
        scene.lights.push_back(new Light(Vec3(-3, 1, 5), Color(1.0,1.0,1.0)));

        (&scene)->camera = new Camera(Vec3(-0.3, 0.3, 0.3), Vec3(0, 0, 0), Vec3(0, 1, 0), 512, 512, 45, 0.01);
	
        return true;
    }
    catch (const std::exception & e)
    {
        std::cerr << "Caught tinyply exception: " << e.what() << std::endl;
        return false;
    }
}
