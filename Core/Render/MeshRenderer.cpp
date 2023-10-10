#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material* material, CastShadowsMode castShadows, bool contributeGloballIllumination, bool receiveShadows) : Renderable(vertices, indices)
{

}
