#include "Renderer.h"

Renderer::Renderer(Material* material, Shader* shader, std::vector<Mesh*> meshes)
{
	_material = material;
	_shader = shader;
	_meshes = meshes;
}

void Renderer::update_shader()
{
	/*if (!_gameObject->isActive())
		return;
	if (!_material->is_must_update() || !_material->is_texture_changed() )
		return;
	_shader->Active();
	if (_material->is_texture_changed()) {
		_shader->SetFloat2("_Material.tilling", _material->tilling);
		_shader->SetFloat2("_Material.offset", _material->offset);

		_material->diffuseMap.	bindTextureUnit(0);
		_shader->SetInt("_Material.diffuseMap"	, 0);

		_material->roughnessMap.bindTextureUnit(1);
		_shader->SetInt("_Material.roughnessMap", 1);

		_material->metallicMap.	bindTextureUnit(2);
		_shader->SetInt("_Material.metallicMap"	, 2);

		_material->aoMap.		bindTextureUnit(3);
		_shader->SetInt("_Material.aoMap"		, 3);

		_material->bumpMap.		bindTextureUnit(4);
		_shader->SetInt("_Material.normalMap"	, 4);

		_material->emissionMap.	bindTextureUnit(5);
		_shader->SetInt("_Material.emissionMap"	, 5);

		_material->heightMap.	bindTextureUnit(6);
		_shader->SetInt("_Material.parallaxMap"	, 6);
		return;
	}
	
	_shader->SetFloat("_Material.metallic", _material->metallic);
	_shader->SetFloat("_Material.smoothness", _material->smoothness);
	_shader->SetFloat("_Material.occolusionStrength", _material->aoStrength);
	_shader->SetFloat("_Material.metallic", _material->metallic);
	_shader->SetFloat("_Material.metallic", _material->metallic);
	_shader->SetFloat("_Material.metallic", _material->metallic);
	_shader->SetFloat("_Material.metallic", _material->metallic);
	_shader->SetFloat("_Material.metallic", _material->metallic);
	_shader->SetFloat("_Material.metallic", _material->metallic);
	_shader->SetFloat("_Material.metallic", _material->metallic);*/
}

void Renderer::Render()
{
	//// if game object is inactive, no render
	//if (!_gameObject->isActive())
	//	return;

	//_shader->Active();
	//for (auto mesh : _meshes) {
	//	mesh->Draw();
	//}
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
