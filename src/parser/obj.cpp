
/*#include "obj.h"

bool OBJParser::load(std::string filename, Scene &scene){
    Assimp::Importer importer;
    const aiScene * loaded_scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    
    if (!loaded_scene) {
        printf("Error reading .obj file: %s\n", filename.c_str());
        return false;
    }
    
    
    if (loaded_scene->HasMeshes()){
        printf("Number of meshes: %d.\n", loaded_scene->mNumMeshes);
        aiMesh ** meshes = loaded_scene->mMeshes;
        
        
        for (int i = 0; i < loaded_scene->mNumMeshes; i++) {
            printf("Importing mesh %s\n",meshes[i]->mName.C_Str());
            printf("Number of vertices: %d\n", meshes[i]->mNumVertices);
            printf("Number of faces: %d\n", meshes[i]->mNumFaces);
            printf("Material index: %d\n", meshes[i]->mMaterialIndex);
            
            // FIXME: Load material.
            Material m = Material(Color(0.5,0.5,0.8), 0.9, 0.0, 3.0827, 0.0, 1);
            //aiMaterial * mat = loaded_scene->mMaterials[meshes[i]->mMaterialIndex];
            
            for (int j = 0; j < meshes[i]->mNumFaces; j++) {
                aiVector3D vec1 = meshes[i]->mVertices[meshes[i]->mFaces[j].mIndices[0]];
                aiVector3D vec2 = meshes[i]->mVertices[meshes[i]->mFaces[j].mIndices[1]];
                aiVector3D vec3 = meshes[i]->mVertices[meshes[i]->mFaces[j].mIndices[2]];
                
                Vec3 v1 = Vec3(vec1.x, vec1.y, vec1.z);
                Vec3 v2 = Vec3(vec2.x, vec2.y, vec2.z);
                Vec3 v3 = Vec3(vec3.x, vec3.y, vec3.z);

                // Get face vertices
                scene.objects.push_back(new Triangle(v1,v2,v3, m));
            }
        }
    }
    
    if(!loaded_scene->HasCameras()){
        scene.camera = new Camera(Vec3(0, 1.1, 1), Vec3(0,0,0), Vec3(0,1,0), 512, 512, 45, 0.01);
    } else {
        printf("Create camera.\n");
    }
    
    if (!loaded_scene->HasLights()){
        // FIXME: Load lights properly
        scene.lights.push_back(new Light(Vec3(0.2300, 2, -0.2200), Color(1.0,1.0,1.0)));
        scene.lights.push_back(new Light(Vec3(0.2300, 2, 0.1600), Color(1.0,1.0,1.0)));
        scene.lights.push_back(new Light(Vec3(-0.2400, 2, 0), Color(1.0,1.0,1.0)));
        scene.lights.push_back(new Light(Vec3(-0.2400, 2, 0.2200), Color(1.0,1.0,1.0)));

    } else {
        printf("Create lights.\n");
    }

    
    if (loaded_scene->HasMaterials())
        printf("Create materials.\n");
    
    if (loaded_scene->HasTextures())
        printf("Create textures.\n");
    
    return true;
}
*/