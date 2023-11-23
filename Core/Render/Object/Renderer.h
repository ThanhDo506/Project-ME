#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"
#include "../../common.h"
#include "../../Components/Component.h"
#include "Material.h"
#include "Mesh.h"

class Shader;
class Material;
class Camera;

class Renderer{
public:
	Renderer(Material* material, Shader* shader, std::vector<Mesh*> meshes);
	void update_shader();
	void Render();

	Shader* get_shader();
	void	set_shader(Shader* shader);
	Material*	get_material();
	void		set_material(Material* material);

	__declspec(property(get = get_shader, put = set_shader)) Shader* shader;
	__declspec(property(get = get_material, put = set_material)) Material* material;
private:


private:
	Material*					_material;
	Shader*						_shader;
	std::vector<Mesh*>			_meshes;
};

#endif
