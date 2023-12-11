#include "Renderer.h"
#include "../../../third-party/imgui/imgui.h"



Renderer::Renderer(Material* material, std::vector<Mesh*> meshes)
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
		|| !_material->is_must_update())
		return;

	Shader& shader = material->shader;
	shader.Active();
	shader.SetFloat2("tilling", _material->tilling);
	shader.SetFloat2("offset", _material->offset);
	//if (_material.is_texture_changed()) {
	//	int c = 0;
	//	shader.SetFloat2("_Material.tilling", _material.tilling);
	//	shader.SetFloat2("_Material.offset", _material.offset);

	//	if (_material.diffuseMap) {
	//		_material.diffuseMap->bind_texture_unit(c);
	//		shader.SetInt("_Material.diffuseMap", c++);
	//	}

	//	if (_material.roughnessMap) {
	//		_material.roughnessMap->bind_texture_unit(c);
	//		shader.SetInt("_Material.roughnessMap", c++);
	//	}

	//	if (_material.metallicMap) {
	//		_material.metallicMap->bind_texture_unit(c);
	//		shader.SetInt("_Material.metallicMap", c++);
	//	}

	//	if (_material.aoMap) {
	//		_material.aoMap->bind_texture_unit(c);
	//		shader.SetInt("_Material.aoMap", c++);
	//	}

	//	if (_material.bumpMap) {
	//		_material.bumpMap->bind_texture_unit(c);
	//		shader.SetInt("_Material.normalMap", c++);
	//	}

	//	if (_material.emissionMap) {
	//		_material.emissionMap->bind_texture_unit(c);
	//		shader.SetInt("_Material.emissionMap", c++);
	//	}

	//	if (_material.heightMap) {
	//		_material.heightMap->bind_texture_unit(c);
	//		shader.SetInt("_Material.parallaxMap", c++);
	//	}
	//	//APP_INFO("Update texture of %s shader", shader.name.c_str());
	//	_material._textureChanged = false;
	//}
	
	shader.SetFloat("_Material.metallic",				_material->_metallic);
	shader.SetFloat("_Material.smoothness",				_material->_smoothness);
	shader.SetFloat("_Material.aoStrength",				_material->_aoStrength);
	shader.SetBool("_Material.useAlphaClipping",		_material->_useAlphaClipping);
	shader.SetFloat("_Material.alphaClippingThreshold", _material->_alphaClippingThreshold);
	shader.SetVec4("_Material.baseColor",				_material->_baseColor);
	shader.SetBool("_Material.useEmission",				_material->_useEmissionMap);
	shader.SetBool("_Material.useMetallic",				_material->_useMetallicMap);
	shader.SetBool("_Material.useRoughness",			_material->_useRoughnessMap);
	shader.SetBool("_Material.hasNormalMap",			_material->_hasNormalMap);
	//APP_INFO("Update attributes of %s shader",	shader.name.c_str());
}

void Renderer::Render()
{
	// if game object is inactive, no render
	if (!_gameObject->is_active())
		return;

	this->_material->shader.Active();
	for (Mesh* mesh : this->_meshes) {
		mesh->Draw(this->_drawMode);
	}
}

Material* Renderer::get_material()
{
	return _material;
}

void Renderer::set_material(Material* material)
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

void Renderer::OnGui()
{
	if (ImGui::TreeNode("Renderer")) {
		if (ImGui::TreeNode("Material")) {
			Material* material = this->get_material();

			if (ImGui::TreeNode("UV")) {
				ImGui::DragFloat2("Tilling", &material->_tilling[0], 0.02, -10.0f, 10.0f);
				ImGui::DragFloat2("Offset", &material->_offset[0], 0.02, -10.0f, 10.0f);
				ImGui::TreePop();
			}

			ImGui::Text("Base Map");
			ImGui::Image((void*)static_cast<intptr_t>(material->get_diffuse_map()->get_id()),
				ImVec2(48, 48), ImVec2(0, 1), ImVec2(1, 0));

			ImGui::ColorEdit4("Color", &material->_baseColor[0]);

			ImGui::Text("Metallic");
			ImGui::Checkbox("Use Metallic", &material->_useMetallicMap);
			if (material->_useMetallicMap) {
				ImGui::Image((void*)static_cast<intptr_t>(material->get_metallic_map()->get_id()),
					ImVec2(48, 48), ImVec2(0, 1), ImVec2(1, 0));
			} else {
				ImGui::SliderFloat("Metallic value", &material->_metallic, 0.0, 1.0);
			}

			ImGui::Text("Normal Map");
			ImGui::Checkbox("Use Normal map", &material->_hasNormalMap);
			if (material->normalMap) {
				ImGui::Image((void*)static_cast<intptr_t>(material->get_normal_map()->get_id()),
					ImVec2(48, 48), ImVec2(0, 1), ImVec2(1, 0));
			}
			

			ImGui::Text("Roughness");
			ImGui::Checkbox("Use Roughness", &material->_useRoughnessMap);
			if (material->_useRoughnessMap) {
				ImGui::Image((void*)static_cast<intptr_t>(material->get_roughness_map()->get_id()),
					ImVec2(48, 48), ImVec2(0, 1), ImVec2(1, 0));
			} else {
				ImGui::SliderFloat("Smoothness", &material->_smoothness, 0.0, 1.0);
			}

			ImGui::Text("AO Map");
			ImGui::Image((void*)static_cast<intptr_t>(material->get_ao_map()->get_id()),
				ImVec2(48, 48), ImVec2(0, 1), ImVec2(1, 0));

			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
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
	return GL_POINTS;
}
