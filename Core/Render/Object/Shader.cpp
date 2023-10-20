#include "Shader.h"

Shader::Shader(const char* name, const char* vertPath, const char* fragPath, const char* geoPath) {
	std::string vertShaderSrc = readShaderFile(vertPath);
	std::string fragShaderSrc = readShaderFile(fragPath);
	const char* vertexSource = vertShaderSrc.c_str();
	const char* fragmentSource = fragShaderSrc.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	getGLError(vertexShader, ShaderType::VertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	getGLError(fragmentShader, ShaderType::FragmentShader);

	GLuint geometryShader = 0;
	if (geoPath != "") {
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShader);
		getGLError(fragmentShader, ShaderType::FragmentShader);
	}

	_id = glCreateProgram();
	glAttachShader(_id, vertexShader);
	glAttachShader(_id, fragmentShader);
	if (geometryShader != 0) {
		glAttachShader(_id, geometryShader);
	}
	glLinkProgram(_id);
	// Check link error
	getGLError(this->_id, ShaderType::ProgramShader);

	glDetachShader(_id, vertexShader);
	glDetachShader(_id, fragmentShader);
	if (geometryShader != 0) {
		glDetachShader(_id, geometryShader);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryShader != 0) {
		glDeleteShader(geometryShader);
	}
}

void Shader::Active() {
	glUseProgram(_id);
}

void Shader::Delete() {
	glDeleteProgram(_id);
}

GLint Shader::getUniformLocation(const char* uniform) {
	return glGetUniformLocation(_id, uniform);
}

void Shader::SetBool(const char* uniformName, bool value)
{
	glUniform1i(glGetUniformLocation(_id, uniformName), static_cast<int>(value));
}

void Shader::SetInt(const char* uniformName, int value)
{
	glUniform1i(glGetUniformLocation(_id, uniformName), value);
}

void Shader::SetIntArray(const char* uniformName, int* values, uint32_t count)
{
}

void Shader::SetFloat(const char* uniformName, float value)
{
	glUniform1f(glGetUniformLocation(_id, uniformName), value);
}

void Shader::SetFloat2(const char* uniformName, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(_id, uniformName), 1, &value[0]);
}

void Shader::SetFloat3(const char* uniformName, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(_id, uniformName), 1, &value[0]);
}

void Shader::SetFloat4(const char* uniformName, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(_id, uniformName), 1, &value[0]);
}

void Shader::SetMat2(const char* uniformName, const glm::mat2& mat)
{
	glUniformMatrix2fv(glGetUniformLocation(_id, uniformName), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const char* uniformName, const glm::mat3& mat)
{
	glUniformMatrix3fv(glGetUniformLocation(_id, uniformName), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const char* uniformName, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(_id, uniformName), 1, GL_FALSE, &mat[0][0]);
}

std::string Shader::getName() const {
	return _name;
}

void Shader::getGLError(const GLuint& id, ShaderType glType)
{
	GLint success;
	char  message[MAX_MESSAGE_LENGTH];

	if (glType == ShaderType::ProgramShader)
	{
		glGetShaderiv(id, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(id, MAX_MESSAGE_LENGTH, nullptr, message);
			APP_ERROR("Shader linking failed!");
		}
	}
	else
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(id, MAX_MESSAGE_LENGTH, nullptr, message);
			APP_ERROR("Shader compile failed!");

		}
	}
}

std::string Shader::readShaderFile(const char* filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file)
	{
		std::string contents;
		file.seekg(0, std::ios::end);
		contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&contents[0], contents.size());
		file.close();
		return (contents);
	}
	throw(errno);
}
