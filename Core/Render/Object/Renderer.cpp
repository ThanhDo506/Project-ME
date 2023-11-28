#include "Renderer.h"

Renderer::Renderer(const Material& material, std::vector<Mesh*> meshes)
	: Component(nullptr)
	, _material(material)
	, _meshes(meshes)
{
	Rendering::add_renderer_to_registry(this);
}

Renderer::~Renderer()
{
	for (Mesh* mesh : _meshes) {
		delete mesh;
	}
	_meshes.clear();
	Rendering::remove_renderer_from_registry(this);
}

void Renderer::update_shader()
{
	if (!_gameObject->is_active() 
		|| !this->is_active() 
		|| !_material.is_must_update() 
		|| !_material.is_texture_changed())
		return;

	Shader* shader = material.shader;
	shader->Active();
	if (_material.is_texture_changed()) {
		shader->SetFloat2("_Material.tilling", _material.tilling);
		shader->SetFloat2("_Material.offset", _material.offset);

		_material.diffuseMap.		bind_texture_unit(0);
		shader->SetInt("_Material.diffuseMap"		, 0);

		_material.roughnessMap.	bind_texture_unit(1);
		shader->SetInt("_Material.roughnessMap"		, 1);

		_material.metallicMap.	bind_texture_unit(2);
		shader->SetInt("_Material.metallicMap"		, 2);

		_material.aoMap.			bind_texture_unit(3);
		shader->SetInt("_Material.aoMap"			, 3);

		_material.bumpMap.		bind_texture_unit(4);
		shader->SetInt("_Material.normalMap"		, 4);

		_material.emissionMap.	bind_texture_unit(5);
		shader->SetInt("_Material.emissionMap"		, 5);

		_material.heightMap.		bind_texture_unit(6);
		shader->SetInt("_Material.parallaxMap"		, 6);
		return;
	}
	
	shader->SetFloat("_Material.metallic", _material.metallic);
	shader->SetFloat("_Material.smoothness", _material.smoothness);
	shader->SetFloat("_Material.occolusionStrength", _material.aoStrength);
	shader->SetBool("_Material.useAlphaClipping", _material.useAlphaClipping);
	shader->SetFloat("_Material.alphaClippingThreshold", _material.alphaClippingThreshold);
	shader->SetVec4("_Material.reflectColor", _material.reflectColor);
	shader->SetBool("_Material.useEmission", _material.useEmissionMap);
	shader->SetBool("_Material.useMetallic", _material.useMetallicMap);
}

void Renderer::Render()
{
	// if game object is inactive, no render
	if (!_gameObject->is_active())
		return;

	this->_material.shader->Active();
	for (auto mesh : _meshes) {
		mesh->Draw();
	}
}

Material& Renderer::get_material()
{
	return _material;
}

void Renderer::set_material(const Material& material)
{
	_material = material;
}
