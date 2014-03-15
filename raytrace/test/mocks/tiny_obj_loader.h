#ifndef _TINY_OBJ_LOADER_H_
#define _TINY_OBJ_LOADER_H_

#include <vector>

#include <string>

namespace tinyobj {

  typedef struct {
    std::string name;

    float ambient[3];
    float diffuse[3];
    float specular[3];
    float transmittance[3];
    float emission[3];
    float shininess;
    float ior;                // index of refraction

    std::string ambient_texname;
    std::string diffuse_texname;
    std::string specular_texname;
    std::string normal_texname;

  } material_t;

  typedef struct
  {
    std::vector<float>          positions;
    std::vector<float>          normals;
    std::vector<float>          texcoords;
    std::vector<unsigned int>   indices;
  } mesh_t;

  typedef struct {
    std::string  name;
    material_t   material;
    mesh_t       mesh;

  } shape_t;

  std::string LoadObj(std::vector<shape_t>, std::string, std::string);

};

#endif /* _TINY_OBJ_LOADER_H_ */
