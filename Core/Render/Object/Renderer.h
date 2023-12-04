#ifndef RENDERER_H
#define RENDERER_H

#include "../RenderingSystem/Rendering.h"
#include "Shader.h"
#include "../../common.h"
#include "../../Components/Component.h"
#include "Material.h"
#include "Mesh.h"

class Material;

class Renderer : public Component {
public:
	Renderer(const Material& material, std::vector<Mesh*> meshes);
	~Renderer();

	void update_shader();
	void Render();

	Material&	get_material();
	void		set_material(const Material& material);
	
	std::vector<Mesh*>& get_meshes();
	/// <summary>
	/// This will delete completly old meshes
	/// </summary>
	/// <param name="meshes"></param>
	void				set_meshes(const std::vector<Mesh*>& meshes);

	Renderer* Clone() const override;

	__declspec(property(get = get_material, 
						put = set_material))	Material& material;

private:
	Material					_material;
	std::vector<Mesh*>			_meshes;
};

#endif
