#include "Shader.h"
#include "serialization/Serializer.hpp"

Shader::Shader(const char* vertexPath, const char* fragPath)
{
	std::string vertexCode;
	std::string fragCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragShaderFile;

	vertexFilepath = vertexPath;
	fragmentFilepath = fragPath;
	
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//load the text files in to a filestream
		vertexShaderFile.open(vertexPath);
		fragShaderFile.open(fragPath);

		//create a string stream to store the *whole* shader
		std::stringstream vertexShaderStream, fragShaderStream;

		//read the text files in to their streams
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();

		//get rid of file handles in memory
		vertexShaderFile.close();
		fragShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragCode = fragShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "failed to read shader(s) from file" << std::endl;
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragShaderCode = fragCode.c_str();

	unsigned int vertexId;
	unsigned int fragId;

	//debug
	int success;
	char infoLog[512];

	//create and compile vertex shader, check if it was successful
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexId);
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	//...fragment
	fragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragId, 1, &fragShaderCode, NULL);
	glCompileShader(fragId);
	glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	//Shader program
	id = glCreateProgram();
	glAttachShader(id, vertexId);
	glAttachShader(id, fragId);
	glLinkProgram(id);
	//check if shader program compiled and linked correctly
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << vertexPath << std::endl;
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragId);

	fillMappings();
}

Shader::Shader(const char* vertexPath, const char* geometryPath, const char* fragPath)
{
	std::string vertexCode;
	std::string fragCode;
	std::string geoCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragShaderFile;
	std::ifstream geoShaderFile;

	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	geoShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//load the text files in to a filestream
		vertexShaderFile.open(vertexPath);
		fragShaderFile.open(fragPath);
		geoShaderFile.open(geometryPath);

		//create a string stream to store the *whole* shader
		std::stringstream vertexShaderStream, fragShaderStream, geoShaderStream;

		//read the text files in to their streams
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();
		geoShaderStream << geoShaderFile.rdbuf();

		//get rid of file handles in memory
		vertexShaderFile.close();
		fragShaderFile.close();
		geoShaderFile.close();

		vertexCode = vertexShaderStream.str();
		fragCode = fragShaderStream.str();
		geoCode = geoShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "failed to read shader(s) from file" << std::endl;
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragShaderCode = fragCode.c_str();
	const char* geoShaderCode = geoCode.c_str();

	unsigned int vertexId;
	unsigned int fragId;
	unsigned int geoId;

	//debug
	int success;
	char infoLog[512];

	//create and compile vertex shader, check if it was successful
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexId);
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	//...fragment
	fragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragId, 1, &fragShaderCode, NULL);
	glCompileShader(fragId);
	glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	//...geometry
	geoId = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geoId, 1, &geoShaderCode, NULL);
	glCompileShader(geoId);
	glGetShaderiv(geoId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geoId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	//Shader program
	id = glCreateProgram();
	glAttachShader(id, vertexId);
	glAttachShader(id, geoId);
	glAttachShader(id, fragId);
	glLinkProgram(id);
	//check if shader program compiled and linked correctly
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << vertexPath << std::endl;
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragId);
	glDeleteShader(geoId);

	fillMappings();
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setVec2(const std::string& name, glm::vec2 value) const
{
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}


void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setBoolID(unsigned int boolID, bool value) const
{
	glUniform1i(boolID, (int)value);
}

void Shader::setMat4ID(const unsigned int mat4ID, glm::mat4 value) const
{
	glUniformMatrix4fv(mat4ID, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setFloatID(unsigned int floatID, float value) const
{
	glUniform1f(floatID, value);
}

void Shader::setVec3ID(unsigned int vec3ID, glm::vec3 value) const
{
	glUniform3fv(vec3ID, 1, glm::value_ptr(value));
}

void Shader::setIntID(const unsigned int intID, int value) const
{
	glUniform1i(intID, value);
}

unsigned int Shader::getBoolLocation(const std::string& name)
{
	return glGetUniformLocation(id, name.c_str());
}
unsigned int Shader::getIntLocation(const std::string& name)
{
	return glGetUniformLocation(id, name.c_str());
}
unsigned int Shader::getFloatLocation(const std::string& name)
{
	return glGetUniformLocation(id, name.c_str());
}
unsigned int Shader::getVec3Location(const std::string& name)
{
	return glGetUniformLocation(id, name.c_str());
}
unsigned int Shader::getMat4Location(const std::string& name)
{
	return glGetUniformLocation(id, name.c_str());
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
	return glGetUniformLocation(id, name.c_str());
}

std::string Shader::textureTypeToShaderName(TextureType t)
{
	if (t == TextureType::diffuse)
	{
		return("mat.m_Diffuse");
	}

	if (t == TextureType::specular)
	{
		return("mat.m_Specular");
	}

	if (t == TextureType::reflection)
	{
		return("mat.m_Reflection");
	}

	if (t == TextureType::normal)
	{
		return("mat.m_Normal");
	}

	if (t == TextureType::metallic)
	{
		return("mat.m_Metallic");
	}

	if (t == TextureType::roughness)
	{
		return("mat.m_Roughness");
	}

	if (t == TextureType::ao)
	{
		return("mat.m_AO");
	}
}

void Shader::fillMappings()
{
	for (int TextureTypeInt = 0; TextureTypeInt <= 8; TextureTypeInt++)
	{
		TextureType t = static_cast<TextureType>(TextureTypeInt);
		std::string shaderString = textureTypeToShaderName(t);
		unsigned int shaderId = getUniformLocation(shaderString);
		textureIdMappings.insert(std::pair<TextureType, unsigned int>(t, shaderId));
	}
}

tinyxml2::XMLElement* Shader::serialize(tinyxml2::XMLDocument* doc)
{
	auto shaderElement = doc->NewElement("Shader");
	auto vertexElement = Serializer::SerializeString("vertexFilepath", vertexFilepath, doc);
	auto fragElement = Serializer::SerializeString("fragmentFilepath", fragmentFilepath, doc);
	shaderElement->LinkEndChild(vertexElement);
	shaderElement->LinkEndChild(fragElement);
	return shaderElement;
}


