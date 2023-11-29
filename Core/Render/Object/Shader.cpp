#include "Shader.h"

Shader::Shader(std::string name, const char* vertPath, const char* fragPath, const char* geoPath) 
	: _name(name)
{
	std::string vertShaderSrc = read_shader_file(vertPath);
	std::string fragShaderSrc = read_shader_file(fragPath);
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

Shader::~Shader()
{
	this->clean();
}

void Shader::clean()
{
	glDeleteShader(this->_id);
	this->_id = 0;
}

void Shader::Active() {
	glUseProgram(_id);
}

void Shader::Delete() {
	glDeleteProgram(_id);
}

GLint Shader::get_uniform_location(const char* uniform) {
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

void Shader::SetFloat(std::string uniformName, float value)
{
	SetFloat(uniformName.c_str(), value);
}

void Shader::SetMat2(std::string uniformName, const glm::mat2& value)
{
	SetMat2(uniformName.c_str(), value);
}

void Shader::SetMat3(std::string uniformName, const glm::mat3& value)
{
	SetMat3(uniformName.c_str(), value);
}

void Shader::SetMat4(std::string uniformName, const glm::mat4& value)
{
	SetMat4(uniformName.c_str(), value);
}

void Shader::SetVec2(std::string uniformName, const glm::vec2& value)
{
	SetVec2(uniformName.c_str(), value);
}

void Shader::SetVec2(std::string uniformName, const float& x, const float& y)
{
	SetVec2(uniformName.c_str(), x, y);
}

void Shader::SetVec3(std::string uniformName, const glm::vec3& value)
{
	SetVec3(uniformName.c_str(), value);
}

void Shader::SetVec3(std::string uniformName, const float& x, const float& y, const float& z)
{
	SetVec3(uniformName.c_str(), x, y, z);
}

void Shader::SetVec4(std::string uniformName, const glm::vec4& value)
{
	SetVec4(uniformName.c_str(), value);
}

void Shader::SetVec4(std::string uniformName, const float& x, const float& y, const float& z, const float& w)
{
	SetVec4(uniformName.c_str(), x, y, z, w);
}

std::string Shader::get_name() const
{
	return this->_name;
}

void Shader::set_name(std::string newName)
{
	this->_name = newName;
}

Shader* Shader::get_default_shader()
{
	static Shader* s;
	if (!s) {
		s = new Shader("Default Shader", "Resources/GLSL/default.vert", "Resources/GLSL/default.frag");
	}
	return s;
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

void Shader::SetVec2(const char* uniformName, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(_id, uniformName), 1, &value[0]);
}

void Shader::SetVec2(const char* uniformName, const float& x, const float& y)
{
	glUniform2f(glGetUniformLocation(this->_id, uniformName), x, y);
}

void Shader::SetVec3(const char* uniformName, const glm::vec3& value)
{
	glUniform2fv(glGetUniformLocation(_id, uniformName), 1, &value[0]);
}

void Shader::SetVec3(const char* uniformName, const float& x, const float& y, const float& z)
{
	glUniform3f(glGetUniformLocation(this->_id, uniformName), x, y, z);
}

void Shader::SetVec4(const char* uniformName, const glm::vec4& value)
{
	glUniform2fv(glGetUniformLocation(_id, uniformName), 1, &value[0]);
}

void Shader::SetVec4(const char* uniformName, const float& x, const float& y, const float& z, const float& w)
{
	glUniform4f(glGetUniformLocation(this->_id, uniformName), x, y, z, w);
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

std::string Shader::read_shader_file(const char* filePath)
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
