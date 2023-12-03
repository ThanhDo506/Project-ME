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

	Shader& shader = material.shader;
	shader.Active();
	if (_material.is_texture_changed()) {
		int c = 0;
		shader.SetFloat2("_Material.tilling", _material.tilling);
		shader.SetFloat2("_Material.offset", _material.offset);

		if (_material.diffuseMap) {
			_material.diffuseMap->bind_texture_unit(c);
			shader.SetInt("_Material.diffuseMap", c++);
		}

		if (_material.roughnessMap) {
			_material.roughnessMap->bind_texture_unit(c);
			shader.SetInt("_Material.roughnessMap", c++);
		}

		if (_material.metallicMap) {
			_material.metallicMap->bind_texture_unit(c);
			shader.SetInt("_Material.metallicMap", c++);
		}

		if (_material.aoMap) {
			_material.aoMap->bind_texture_unit(c);
			shader.SetInt("_Material.aoMap", c++);
		}

		if (_material.bumpMap) {
			_material.bumpMap->bind_texture_unit(c);
			shader.SetInt("_Material.normalMap", c++);
		}

		if (_material.emissionMap) {
			_material.emissionMap->bind_texture_unit(c);
			shader.SetInt("_Material.emissionMap", c++);
		}

		if (_material.heightMap) {
			_material.heightMap->bind_texture_unit(c);
			shader.SetInt("_Material.parallaxMap", c++);
		}
	}
	
	shader.SetFloat("_Material.metallic",				_material.metallic);
	shader.SetFloat("_Material.smoothness",				_material.smoothness);
	shader.SetFloat("_Material.occolusionStrength",		_material.aoStrength);
	shader.SetBool("_Material.useAlphaClipping",		_material.useAlphaClipping);
	shader.SetFloat("_Material.alphaClippingThreshold", _material.alphaClippingThreshold);
	shader.SetVec4("_Material.reflectColor",			_material.reflectColor);
	shader.SetBool("_Material.useEmission",				_material.useEmissionMap);
	shader.SetBool("_Material.useMetallic",				_material.useMetallicMap);
}

void Renderer::Render()
{
	// if game object is inactive, no render
	if (!_gameObject->is_active())
		return;

	this->_material.shader.Active();
	for (Mesh* mesh : this->_meshes) {
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

Renderer* Renderer::Clone() const
{
	return new Renderer(*this);
}
