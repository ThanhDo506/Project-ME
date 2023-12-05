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
		APP_INFO("Update texture of %s shader", shader.name.c_str());
		_material._textureChanged = false;
	}
	
	shader.SetFloat("_Material.metallic",				_material.metallic);
	shader.SetFloat("_Material.smoothness",				_material.smoothness);
	shader.SetFloat("_Material.aoStrength",				_material.aoStrength);
	shader.SetBool("_Material.useAlphaClipping",		_material.useAlphaClipping);
	shader.SetFloat("_Material.alphaClippingThreshold", _material.alphaClippingThreshold);
	shader.SetVec4("_Material.reflectColor",			_material.reflectColor);
	shader.SetBool("_Material.useEmission",				_material.useEmissionMap);
	shader.SetBool("_Material.useMetallic",				_material.useMetallicMap);
	APP_INFO("Update attributes of %s shader",	shader.name.c_str());
}

void Renderer::Render()
{
	// if game object is inactive, no render
	if (!_gameObject->is_active())
		return;

	this->_material.shader.Active();
	for (Mesh* mesh : this->_meshes) {
		mesh->Draw(this->_drawMode);
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

std::vector<Mesh*>& Renderer::get_meshes()
{
	return this->_meshes;
}

void Renderer::set_meshes(const std::vector<Mesh*>& meshes)
{
	for (auto mesh : this->_meshes) {
		delete mesh;
	}
	this->_meshes.clear();
	this->_meshes = meshes;
}

Renderer* Renderer::Clone() const
{
	return new Renderer(*this);
}

void Renderer::set_draw_mode(const DrawMode& mode)
{
	this->_drawMode = draw_mode_to_gl_enum(mode);
}

GLenum Renderer::draw_mode_to_gl_enum(const DrawMode& mode)
{
	switch (mode)
	{
	case TriangleStrip:
		return GL_TRIANGLE_STRIP;
		break;
	case Points:
		return GL_POINTS;
		break;
	case Lines:
		return GL_LINES;
		break;
	case LineLoop:
		return GL_LINE_LOOP;
		break;
	case LineStrip:
		return GL_LINE_STRIP;
		break;
	case Triangles:
		return GL_TRIANGLES;
		break;
	case TriangleFan:
		return GL_TRIANGLE_FAN;
		break;
	case Quads:
		return GL_QUADS;
		break;
	case QuadStrip:
		return GL_QUAD_STRIP;
		break;
	case Polygon:
		return GL_POLYGON;
		break;
	default:
		break;
	}
}
