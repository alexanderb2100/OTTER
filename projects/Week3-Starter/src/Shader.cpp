#include "Shader.h"
#include "Logging.h"
#include <fstream>
#include <sstream>

Shader::Shader() :
	// We zero out all of our members so we don't have garbage data in our class
	_vs(0),
	_fs(0),
	_handle(0)
{
	// TODO: Constructor
	_handle = glCreateProgram();
}

Shader::~Shader() {
	// TODO: Destructor
}

bool Shader::LoadShaderPart(const char* source, ShaderPartType type)
{
	// TODO: Implement
	// Creates a new shader part (VS, FS, GS, etc...)
	GLuint handle = glCreateShader((GLenum)type);
	// Load the GLSL source and compile it
	glShaderSource(handle, 1, &source, nullptr);
	glCompileShader(handle);
	// Get the compilation status for the shader part
	GLint status = 0;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

	return true;
}

bool Shader::LoadShaderPartFromFile(const char* path, ShaderPartType type) {
	// Open the file at path
	std::ifstream file(path);

	// Check to see if the file is open
	if (file.is_open()) {
		// Create a string stream to load the entire contents of the file
		std::stringstream stream;
		stream << file.rdbuf();

		// Compile the shader part from the loaded contents of the file
		bool result = LoadShaderPart(stream.str().c_str(), type);

		// Close the file
		file.close();
		return result;
	}
	// Failed to open file, log it and return false
	else {
		LOG_WARN("Could not open file at \"{}\"", path);
		return false;
	}
}

bool Shader::Link()
{
	// Todo: Implement
	return true;
}

void Shader::Bind() {
	// Simply calls glUseProgram with our shader handle
	glUseProgram(_handle);
}

void Shader::Unbind() {
	// We unbind a shader program by using the default program (0)
	glUseProgram(0);
}
