#ifndef SPHERE_H
#define SPHERE_H

#include "../../Components/Component.h"
#include "../../Components/GameObject.h"
#include "../Object/Renderer.h"

class GameObject;

class Sphere : public GameObject
{
public:
	Sphere(Transform transform);
	/*Sphere(Transform transform, float radius = 1.0, int sector = 3, int stack = 2, bool smooth = false);

private:
	void build_vertices_flat();
	void build_vertices_smooth();
	void set(float radius, int sectors, int stacks, bool smooth);
	void clean_meshes();
	glm::vec3 computeFaceNormal(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3);
private:
	float	_radius;
	int		_sectors;
	int		_stack;
	bool	_smooth;*/
};

#endif