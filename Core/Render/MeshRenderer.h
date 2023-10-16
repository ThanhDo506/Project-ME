#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "Renderable.h"
#include "../common.h"
#include "Material.h"

enum CastShadowsMode {
	OFF,
	ON,
	BOTH_SIDE
};

class MeshRenderer : private Renderable {

private:
	CastShadowsMode caseShadows;
	bool contributeGloballIllumination;
	bool receiveShadows;

public:
	explicit MeshRenderer(std::vector<Vertex> vertices, std::vector<GLuint> indices, Shader* shader, Material* material, CastShadowsMode castShadows = CastShadowsMode::ON, bool contributeGloballIllumination = true, bool receiveShadows = true);
};

#endif
