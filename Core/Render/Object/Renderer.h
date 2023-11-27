#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "../../common.h"
#include "../../Components/Component.h"
#include "Material.h"
#include "Mesh.h"

class Material;

class Renderer : public Component {
public:
	Renderer(Material* material, std::vector<Mesh*> meshes);
	void update_shader();
	void Render();

	Material*	get_material();
	void		set_material(Material* material);

	__declspec(property(get = get_material, 
						put = set_material))	Material* material;

private:
	Material*					_material;
	std::vector<Mesh*>			_meshes;
};

#endif
