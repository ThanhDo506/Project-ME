#include "Shader.h"
#include <sstream>
Shader::Shader(const std::string& name, const char* vertPath, const char* fragPath, const char* geoPath) 
	: _name(name)
{
	//std::string vertShaderSrc = read_shader_file(vertPath);
	//std::string fragShaderSrc = read_shader_file(fragPath);
	//const char* vertexSource = vertShaderSrc.c_str();
	//const char* fragmentSource = fragShaderSrc.c_str();

	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	//glCompileShader(vertexShader);
	//getGLError(vertexShader, ShaderType::VertexShader);

	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	//glCompileShader(fragmentShader);
	//getGLError(fragmentShader, ShaderType::FragmentShader);

	//GLuint geometryShader = 0;
	//if (geoPath != "") {
	//	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	//	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	//	glCompileShader(fragmentShader);
	//	getGLError(fragmentShader, ShaderType::FragmentShader);
	//}

	//_id = glCreateProgram();
	//glAttachShader(_id, vertexShader);

	//glAttachShader(_id, fragmentShader);

	//if (geometryShader != 0) {
	//	glAttachShader(_id, geometryShader);
	//	getGLError(this->_id, ShaderType::ProgramShader);
	//}
	//glLinkProgram(_id);
	// //Check link error
	//if (getGLError(this->_id, ShaderType::ProgramShader)) {
	//	APP_ERROR("Shader %s", name.c_str());
	//}

	//glDetachShader(_id, vertexShader);
	//glDetachShader(_id, fragmentShader);
	//if (geometryShader != 0) {
	//	glDetachShader(_id, geometryShader);
	//}
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	//if (geometryShader != 0) {
	//	glDeleteShader(geometryShader);
	//}
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertPath);
		fShaderFile.open(fragPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// if geometry shader path is present, also load a geometry shader
		if (geoPath != "" && geoPath != NULL)
		{
			gShaderFile.open(geoPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure& e)
	{
		APP_ERROR("[SHADER] FILE_NOT_SUCCESSFULLY_READ: %s", e.what());
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	// if geometry shader is given, compile geometry shader
	unsigned int geometry;
	if (geoPath != "" && geoPath != NULL)
	{
		const char* gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		checkCompileErrors(geometry, "GEOMETRY");
	}
	// shader Program
	_id = glCreateProgram();
	glAttachShader(_id, vertex);
	glAttachShader(_id, fragment);
	if (geoPath != "" && geoPath != NULL)
		glAttachShader(_id, geometry);
	glLinkProgram(_id);
	checkCompileErrors(_id, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geoPath !=  "" && geoPath != NULL)
		glDeleteShader(geometry);

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

std::string Shader::get_name() const
{
	return this->_name;
}

void Shader::set_name(const std::string& name)
{
	this->_name = name;
}

Shader& Shader::get_default_shader()
{
	static Shader* s;
	if (!s) {
		s = new Shader("Default Shader", "Resources/GLSL/error.vert", "Resources/GLSL/error.frag");
	}
	return *s;
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
	glUniform3fv(glGetUniformLocation(_id, uniformName), 1, &value[0]);
}

void Shader::SetVec3(const char* uniformName, const float& x, const float& y, const float& z)
{
	glUniform3f(glGetUniformLocation(this->_id, uniformName), x, y, z);
}

void Shader::SetVec4(const char* uniformName, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(_id, uniformName), 1, &value[0]);
}

void Shader::SetVec4(const char* uniformName, const float& x, const float& y, const float& z, const float& w)
{
	glUniform4f(glGetUniformLocation(this->_id, uniformName), x, y, z, w);
}

bool Shader::getGLError(const GLuint& id, ShaderType glType)
{
	GLint success;
	char  message[MAX_MESSAGE_LENGTH];

	if (glType == ShaderType::ProgramShader)
	{
		glGetShaderiv(id, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(id, MAX_MESSAGE_LENGTH, nullptr, message);
			APP_ERROR("Shader linking failed! msg: %s", message);
			return true;
		}
	}
	else
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(id, MAX_MESSAGE_LENGTH, nullptr, message);
			APP_ERROR("Shader linking failed! msg: %s", message);
			return true;
		}
	}
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			//std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			APP_ERROR("[SHADER] %s SHADER_COMPILATION_ERROR type: %s", this->_name.c_str(), type.c_str());
			APP_WARN("[SHADER] %s", infoLog);
			
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			//std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			APP_ERROR("[SHADER] %s PROGRAM_LINKING_ERROR type: %s", this->_name.c_str(), type.c_str());
			APP_WARN("[SHADER] %s", infoLog);

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
	else {
		std::cout << "Could not read file " << filePath << std::endl;
	}
	//throw(errno);
}
