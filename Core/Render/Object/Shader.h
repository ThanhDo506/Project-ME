#ifndef SHADER_H
#define SHADER_H

#define MAX_MESSAGE_LENGTH 500

#include "../../common.h"
#include <glm/glm.hpp>
#include <fstream>

enum ShaderType {
	VertexShader,
	FragmentShader,
	GeometryShader,
	ProgramShader
};

class Shader {

private:
	/**
	 * Do not modify this attribute.
	 */
	GLuint _id;
	std::string _name;

public:
	Shader(const std::string& name, const char* vertPath, const char* fragPath, const char* geoPath = "");
	~Shader();

	void clean();

	void Active();
	void Delete();

	GLint get_uniform_location(const char* uniform);

	void SetBool(const char* uniformName, bool value);
	void SetInt(const char* uniformName, int value);

	// TODO: haven't done this!
	void SetIntArray(const char* uniformName, int* values, uint32_t count);
	void SetFloat(const char* uniformName, float value);
	void SetFloat2(const char* uniformName, const glm::vec2& value);
	void SetFloat3(const char* uniformName, const glm::vec3& value);
	void SetFloat4(const char* uniformName, const glm::vec4& value);
	void SetMat2(const char* uniformName, const glm::mat2& value);
	void SetMat3(const char* uniformName, const glm::mat3& value);
	void SetMat4(const char* uniformName, const glm::mat4& value);
	void SetVec2(const char* uniformName, const glm::vec2& value);
	void SetVec2(const char* uniformName, const float& x, const float& y);
	void SetVec3(const char* uniformName, const glm::vec3& value);
	void SetVec3(const char* uniformName, const float& x, const float& y, const float& z);
	void SetVec4(const char* uniformName, const glm::vec4& value);
	void SetVec4(const char* uniformName, const float& x, const float& y, const float& z, const float& w);

	std::string get_name() const;
	void		set_name(const std::string& name);

	static Shader& get_default_shader();

	__declspec(property(get = get_name,
						put = set_name))	std::string name;
private:
	// Ref: Victor Gordan
	// 12th - July - 2023
	// https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%204%20-%20Organizing/shaderClass.cpp
	std::string read_shader_file(const char* filePath);

	bool getGLError(const GLuint& id, ShaderType glType);
	void checkCompileErrors(GLuint shader, std::string type);
};

#endif
