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
	GLuint _id;
	std::string _name;

public:
	Shader(const char* name, const char* vertPath, const char* fragPath, const char* geoPath = "");

	void Active();

	void Delete();

	GLint getUniformLocation(const char* uniform);

	void SetBool(const char* uniformName, bool value);
	void SetInt(const char* uniformName, int value);
	void SetIntArray(const char* uniformName, int* values, uint32_t count);
	void SetFloat(const char* uniformName, float value);
	void SetFloat2(const char* uniformName, const glm::vec2& value);
	void SetFloat3(const char* uniformName, const glm::vec3& value);
	void SetFloat4(const char* uniformName, const glm::vec4& value);
	void SetMat2(const char* uniformName, const glm::mat2& value);
	void SetMat3(const char* uniformName, const glm::mat3& value);
	void SetMat4(const char* uniformName, const glm::mat4& value);

	std::string getName() const;


private:
	// Ref: Victor Gordan
	// 12th - July - 2023
	// https://github.com/VictorGordan/opengl-tutorials/blob/main/YoutubeOpenGL%204%20-%20Organizing/shaderClass.cpp
	std::string readShaderFile(const char* filePath);

	void getGLError(const GLuint& id, ShaderType glType);
};

#endif
