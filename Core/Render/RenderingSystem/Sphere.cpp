#include "Sphere.h"

Sphere::Sphere(Transform transform)
	: GameObject(transform, "Sphere")
{
	//set(radius, sector,stack,smooth);
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	const float PI = 3.14159265359f;
	for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			vertices.push_back({
				glm::vec3(xPos, yPos, zPos),
				glm::vec3(xPos, yPos, zPos),
				glm::vec4(1.0),
				glm::vec2(xSegment, ySegment),
				glm::vec2(0.0)
			});
		}
	}

	bool oddRow = false;
	for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
		if (!oddRow) // even rows: y == 0, y == 2; and so on 
		{
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
				indices.push_back(y * (X_SEGMENTS + 1) + x);
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		} else {
			for (int x = X_SEGMENTS; x >= 0; --x) {
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				indices.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	Material* material = new Material;
	material->renderFace = Front;
	std::vector<Mesh*> meshes = { new Mesh(vertices, indices) };
	Renderer* r = this->AddComponent<Renderer>(material, meshes);
	r->set_draw_mode(TriangleStrip);
}
//
//void Sphere::build_vertices_flat()
//{
//	const float PI = acos(-1.0f);
//
//	std::vector<Vertex> vertices;
//	std::vector<GLuint> indices;
//
//	float sectorStep = 2 * PI / this->_sectors;
//	float stackStep = PI / this->_stack;
//	float sectorAngle, stackAngle;
//
//	std::vector<Vertex> tmpVertices;
//
//	for (int i = 0; i <= this->_stack; ++i)
//	{
//		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
//		float xy = this->_radius * cosf(stackAngle);       // r * cos(u)
//		float z = this->_radius * sinf(stackAngle);        // r * sin(u)
//
//		// add (sectorCount+1) vertices per stack
//		// the first and last vertices have same position and normal, but different tex coords
//		for (int j = 0; j <= this->_sectors; ++j)
//		{
//			sectorAngle = j * sectorStep;           // starting from 0 to 2pi
//			Vertex vertex;
//			// x = r * cos(u) * cos(v)
//			// y = r * cos(u) * sin(v)
//			// z = r * sin(u)
//			vertex.position = { xy * cosf(sectorAngle), xy * sinf(sectorAngle), z };       
//			vertex.texCoord = { (float)j / this->_sectors , (float)i / this->_stack };
//			tmpVertices.push_back(vertex);
//		}
//	}
//
//	this->clean_meshes();
//
//	Vertex v1, v2, v3, v4;                          // 4 vertex positions and tex coords
//	std::vector<float> n;                           // 1 face normal
//
//	int i, j, k, vi1, vi2;
//	int index = 0;                                  // index for vertex
//	for (i = 0; i < this->_stack; ++i)
//	{
//		vi1 = i * (this->_sectors + 1);                // index of tmpVertices
//		vi2 = (i + 1) * (this->_sectors + 1);
//
//		for (j = 0; j < this->_sectors; ++j, ++vi1, ++vi2)
//		{
//			// get 4 vertices per sector
//			//  v1--v3
//			//  |    |
//			//  v2--v4
//			v1 = tmpVertices[vi1];
//			v2 = tmpVertices[vi2];
//			v3 = tmpVertices[vi1 + 1];
//			v4 = tmpVertices[vi2 + 1];
//
//			Vertex vert1, vert2, vert3, vert4;
//			// if 1st stack and last stack, store only 1 triangle per sector
//			// otherwise, store 2 triangles (quad) per sector
//			if (i == 0) // a triangle for first stack ==========================
//			{
//				// put a triangle
//				vert1.position = v1.position;
//				vert2.position = v2.position;
//				vert3.position = v4.position;
//
//				// put tex coords of triangle
//				vert1.texCoord = v1.texCoord;
//				vert2.texCoord = v2.texCoord;
//				vert3.texCoord = v4.texCoord;
//
//				// put normal
//				vert1.normal = computeFaceNormal(vert1.position, vert2.position, vert3.position);
//				vert2.normal = vert1.normal;
//				vert3.normal = vert2.normal;
//
//				// put indices of 1 triangle
//				indices.push_back(index);
//				indices.push_back(index + 1);
//				indices.push_back(index + 2);
//				index += 3;     // for next
//			} else if (i == (this->_stack - 1)) // a triangle for last stack =========
//			{
//				// put a triangle
//				vert1.position = v1.position;
//				vert2.position = v2.position;
//				vert3.position = v3.position;
//
//				// put tex coords of triangle
//				vert1.texCoord = v1.texCoord;
//				vert2.texCoord = v2.texCoord;
//				vert3.texCoord = v3.texCoord;
//
//				// put normal
//				vert1.normal = computeFaceNormal(vert1.position, vert2.position, vert3.position);
//				vert2.normal = vert1.normal;
//				vert3.normal = vert2.normal;
//
//				// put indices of 1 triangle
//				indices.push_back(index);
//				indices.push_back(index + 1);
//				indices.push_back(index + 2);
//
//				index += 3;     // for next
//			} else // 2 triangles for others ====================================
//			{
//				// put quad vertices: v1-v2-v3-v4
//				vert1.position = v1.position;
//				vert2.position = v2.position;
//				vert3.position = v3.position;
//				vert4.position = v4.position;
//
//				// put tex coords of quad
//				vert1.texCoord = v1.texCoord;
//				vert2.texCoord = v2.texCoord;
//				vert3.texCoord = v3.texCoord;
//				vert4.texCoord = v4.texCoord;
//
//				// put normal
//				vert1.texCoord = computeFaceNormal(v1.position, v2.position, v3.position);
//				vert2.texCoord = v1.texCoord;
//				vert3.texCoord = v1.texCoord;
//				vert4.texCoord = v1.texCoord;
//
//				// put indices of quad (2 triangles)
//				indices.push_back(index);
//				indices.push_back(index + 1);
//				indices.push_back(index + 2);
//				indices.push_back(index + 2);
//				indices.push_back(index + 1);
//				indices.push_back(index + 3);
//				index += 4;     // for next
//			}
//		}
//	}
//}
//
//void Sphere::build_vertices_smooth()
//{
//	const float PI = acos(-1.0f);
//
//	this->clean_meshes();
//
//	std::vector<Vertex> vertices;
//	std::vector<GLuint> indices;
//
//	float x, y, z, xy;                              // vertex position
//	float nx, ny, nz, lengthInv = 1.0f / this->_radius;    // normal
//	float s, t;                                     // texCoord
//
//	float sectorStep = 2 * PI / this->_sectors;
//	float stackStep = PI / this->_stack;
//	float sectorAngle, stackAngle;
//
//	for (int i = 0; i <= this->_stack; ++i)
//	{
//		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
//		xy = this->_radius * cosf(stackAngle);             // r * cos(u)
//		z = this->_radius * sinf(stackAngle);              // r * sin(u)
//
//		// add (sectorCount+1) vertices per stack
//		// the first and last vertices have same position and normal, but different tex coords
//		for (int j = 0; j <= this->_sectors; ++j)
//		{
//			sectorAngle = j * sectorStep;           // starting from 0 to 2pi
//
//			// vertex position
//			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
//			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
//
//			// normalized vertex normal
//			nx = x * lengthInv;
//			ny = y * lengthInv;
//			nz = z * lengthInv;
//
//			// vertex tex coord between [0, 1]
//			s = (float)j / this->_sectors;
//			t = (float)i / this->_stack;
//
//			vertices.push_back({
//				glm::vec3(x, y, z),
//				glm::vec3(nx, ny, nz),
//				glm::vec4(1.0, 1.0, 1.0, 1.0f),
//				glm::vec2(s, t),
//				glm::vec2(0.0f)
//				});
//		}
//	}
//
//	// indices
//	//  k1--k1+1
//	//  |  / |
//	//  | /  |
//	//  k2--k2+1
//	unsigned int k1, k2;
//	for (int i = 0; i < this->_stack; ++i)
//	{
//		k1 = i * (this->_sectors + 1);     // beginning of current stack
//		k2 = k1 + this->_sectors + 1;      // beginning of next stack
//
//		for (int j = 0; j < this->_sectors; ++j, ++k1, ++k2)
//		{
//			// 2 triangles per sector excluding 1st and last stacks
//			if (i != 0)
//			{
//				// k1---k2---k1+1
//				indices.push_back(k1);
//				indices.push_back(k2);
//				indices.push_back(k1 + 1);
//			}
//
//			if (i != (_stack - 1))
//			{
//				 // k1+1---k2---k2+1
//				indices.push_back(k1 + 1);
//				indices.push_back(k2);
//				indices.push_back(k2 + 1);
//			}
//		}
//	}
//	if (this->HasComponent<Renderer>()) {
//		Renderer* r = this->GetComponent<Renderer>();
//		clean_meshes();
//	} else {
//		Material material;
//		material.renderFace = Front;
//		material.shader = Shader::get_default_shader();
//		std::vector<Mesh*> meshes = { new Mesh(vertices, indices) };
//		Renderer* r = this->AddComponent<Renderer>(material, meshes);
//		r->attach_to_gameObject(this);
//	}
//}
//
//void Sphere::set(float radius, int sectors, int stacks, bool smooth)
//{
//	if (radius > 0) {
//		this->_radius = radius;
//	} else {
//		this->_radius = 1.0;
//	}
//	if (_sectors < 3) {
//		this->_sectors = 3;
//	} else {
//		this->_sectors = sectors;
//	}
//	if (stacks < 2) {
//		this->_stack = 2;
//	} else {
//		this->_stack = stacks;
//	}
//
//	if (smooth) {
//		build_vertices_smooth();
//	} else {
//		build_vertices_flat();
//	}
//}
//
//void Sphere::clean_meshes()
//{
//	if (this->HasComponent<Renderer>()) {
//		Renderer* r = GetComponent<Renderer>();
//		for (auto mesh : r->get_meshes()) {
//			delete mesh;
//		}
//		r->get_meshes().clear();
//	}
//}
//
//glm::vec3 Sphere::computeFaceNormal(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3)
//{
//	const float EPSILON = 0.000001f;
//
//	glm::vec3 normal(0.0f);     // default return value (0,0,0)
//	float nx, ny, nz;
//
//	// find 2 edge vectors: v1-v2, v1-v3
//	float ex1 = v2.x - v1.x;
//	float ey1 = v2.y - v1.y;
//	float ez1 = v2.z - v1.z;
//	float ex2 = v3.x - v1.x;
//	float ey2 = v3.y - v1.y;
//	float ez2 = v3.z - v1.z;
//
//	// cross product: e1 x e2
//	nx = ey1 * ez2 - ez1 * ey2;
//	ny = ez1 * ex2 - ex1 * ez2;
//	nz = ex1 * ey2 - ey1 * ex2;
//
//	// normalize only if the length is > 0
//	float length = sqrtf(nx * nx + ny * ny + nz * nz);
//	if (length > EPSILON)
//	{
//		// normalize
//		float lengthInv = 1.0f / length;
//		normal[0] = nx * lengthInv;
//		normal[1] = ny * lengthInv;
//		normal[2] = nz * lengthInv;
//	}
//
//	return normal;
//}
