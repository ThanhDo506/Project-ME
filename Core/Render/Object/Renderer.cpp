#include "Renderer.h"

Renderer::Renderer(GameObject* gameObject, Material* material, Shader* shader, std::vector<Mesh*> meshes) : Component(gameObject, "Renderer")
{
	_material = material;
	_shader = shader;
	_meshes = meshes;
}

void Renderer::update_shader()
{
}

void Renderer::Render()
{
	_shader->Active();
	for (auto mesh : _meshes) {
		mesh->Draw();
	}
}

Shader* Renderer::get_shader()
{
	return _shader;
}

void Renderer::set_shader(Shader* shader)
{
	_shader = shader;
}

Material* Renderer::get_material()
{
	return _material;
}

void Renderer::set_material(Material* material)
{
	_material = material;
}
