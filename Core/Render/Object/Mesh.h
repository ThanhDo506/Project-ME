#ifndef MESH_H
#define MESH_H

#include "../../common.h"
#include "Vertex.h"

struct Vertex;

class Mesh
{
	friend class Renderer;
public:
	// TODO: should make a static/dynamic buffer
	// Here just static buffer
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();
	/**
	 * Draw the mesh. Please bind shader before call Draw.
	 */
	void Draw();

	void Clean();
private:
	GLuint						_vao;
	GLuint						_vbo;
	GLuint						_ebo;
	std::vector<Vertex>			_vertices;
	std::vector<unsigned int>	_indices;
};

#endif // !MESH_H
