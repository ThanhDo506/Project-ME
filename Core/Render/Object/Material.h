#ifndef MATERIAL_H
#define MATERIAL_H

#include <utility>
#include "../../utilities/Logger.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"

enum RenderFace {
	Front,
	Back,
	Both
};

enum SurfaceType {
	Opaque,
	Transparent
};

enum BlendingMode {
	Alpha,
	Premultiply,
	Additive,
	Multiply
};

class Material {
public:
	bool		is_must_update() const;

	bool		is_texture_changed() const;

	Texture& get_diffuse_map();
	void	set_diffuse_map(Texture diffuseMap);

	Texture& get_roughness_map();
	void	set_roughness_map(Texture roughnessMap);

	Texture& get_metallic_map();
	void	set_metallic_map(Texture metallicMap);

	Texture& get_ao_map();
	void	set_ao_map(Texture aoMap);

	Texture& get_normal_map();
	void	set_normal_map(Texture normalMap);

	Texture& get_height_map();
	void	set_height_map(Texture heightMap);

	Texture& get_emission_map();
	void	set_emission_map(Texture emissionMap);

	float	get_metallic() const;
	void	set_metallic(float metallic);

	float	get_smoothness() const;
	void	set_smoothness(float smoothness);

	float	get_ao_strength() const;
	void	set_ao_strength(float aoStrength);

	bool	is_use_alpha_clipping() const;
	void	set_use_alpha_clipping(bool useAlphaClipping);

	float	get_alpha_clipping_threshold();
	void	set_alpha_clipping_threshold(float val);

	glm::vec4	get_reflect_color() const;
	void		set_reflect_color(glm::vec4 newColor);

	bool		is_use_emission_map() const;
	void		set_use_emission_map(bool use);

	bool		is_use_metallic_map() const;
	void		set_use_metallic_map(bool use);

	bool		is_received_shadow() const;
	void		set_received_shader(bool use);

	void		set_tilling(glm::vec2 newTilling);
	glm::vec2	get_tilling() const;

	void		set_offset(glm::vec2 newOffset);
	glm::vec2	get_offset() const;

	SurfaceType get_sufface_type() const;
	void		set_sufface_type(SurfaceType newSurfaceType);

	RenderFace	get_render_face() const;
	void		set_render_face(RenderFace newRenderFace);

	BlendingMode get_blending_mode() const;
	void		 set_blending_mode(BlendingMode newBlendingMode);

	bool		is_use_specular_highlight() const;
	void		set_use_specular_highlight(bool val);

	bool		is_use_enviroment_reflections() const;
	void		set_use_enviroment_reflections(bool val);

	short		get_priority_render() const;
	void		set_priority_render(short newPriority);

	Shader*		get_shader();
	void		set_shader(Shader* shader);

	__declspec(property(get = get_diffuse_map, put = set_diffuse_map))								Texture			diffuseMap;
	__declspec(property(get = get_roughness_map, put = set_roughness_map))							Texture			roughnessMap;
	__declspec(property(get = get_metallic_map, put = set_metallic_map))							Texture			metallicMap;
	__declspec(property(get = get_ao_map, put = set_ao_map))										Texture			occlusionMap;
	__declspec(property(get = get_ao_map, put = set_ao_map))										Texture			ambientOccolusionMap;
	__declspec(property(get = get_ao_map, put = set_ao_map))										Texture			aoMap;
	__declspec(property(get = get_normal_map, put = set_normal_map))								Texture			normalMap;
	__declspec(property(get = get_normal_map, put = set_normal_map))								Texture			bumpMap;
	__declspec(property(get = get_height_map, put = set_height_map))								Texture			heightMap;
	__declspec(property(get = get_height_map, put = set_height_map))								Texture			parallaxMap;
	__declspec(property(get = get_emission_map, put = set_emission_map))							Texture			emissionMap;

	__declspec(property(get = get_metallic, put = set_metallic))									float			metallic;
	__declspec(property(get = get_smoothness, put = set_smoothness))								float			smoothness;
	__declspec(property(get = get_ao_strength, put = set_ao_strength))								float			aoStrength;
	__declspec(property(get = get_ao_strength, put = set_ao_strength))								float			occolusionStrength;
	__declspec(property(get = is_use_alpha_clipping, put = set_use_alpha_clipping))					bool			useAlphaClipping;
	__declspec(property(get = get_alpha_clipping_threshold, put = set_alpha_clipping_threshold))	float			alphaClippingThreshold;
	__declspec(property(get = get_reflect_color, put = set_reflect_color))							glm::vec4		reflectColor;
	__declspec(property(get = is_use_emission_map, put = set_use_emission_map))						bool			useEmissionMap;
	__declspec(property(get = is_use_metallic_map, put = set_use_metallic_map))						bool			useMetallicMap;
	__declspec(property(get = is_received_shadow, put = set_received_shadow))						bool			receivedShadow;

	__declspec(property(get = get_offset, put = set_offset))										glm::vec2		offset;
	__declspec(property(get = get_tilling, put = set_tilling))										glm::vec2		tilling;
	__declspec(property(get = get_sufface_type, put = set_sufface_type))							SurfaceType		surfaceType;
	__declspec(property(get = get_render_face, put = set_render_face))								RenderFace		renderFace;
	__declspec(property(get = get_blending_mode, put = set_blending_mode))							BlendingMode	blendingMode;
	__declspec(property(get = is_use_specular_highlight, put = set_use_specular_highlight))			bool			specularHighlight;
	__declspec(property(get = is_use_enviroment_reflections, put = set_use_enviroment_reflections)) bool			enviromentReflection;
	__declspec(property(get = is_must_update))														bool			isMushUpdate;
	__declspec(property(get = get_priority_render, put = set_priority_render))						short			priorityRender;

	__declspec(property(get = get_shader, put = set_shader))										Shader*			shader;

private:
	Texture						_diffuseMap;
	Texture						_roughnessMap;
	Texture						_metallicMap;
	Texture						_aoMap;
	Texture						_normalMap;
	Texture						_emissionMap;
	Texture						_heightMap;

	float						_metallic;
	float						_smoothness;
	float						_aoStrength;
	float						_alphaClippingThreshold = 0;
	glm::vec4					_reflectColor;
	bool						_useEmissionMap = false;
	bool						_useMetallicMap = false;
	bool						_receivedShadow = false;
	glm::vec2					_tilling = glm::vec2(0.0, 0.0);
	glm::vec2					_offset = glm::vec2(0.0, 0.0);
	SurfaceType					_surfaceType;
	RenderFace					_renderFace;
	BlendingMode				_blendingMode;
	bool						_useSpecularHighlight = false;
	bool						_useEnviromentReflections = false;
	bool						_mustUpdate = true;
	bool						_useAlphaClipping = false;
	bool						_textureChanged = true;
	short						_priorityRender = 0;

	Shader*						_shader;
};

#endif
