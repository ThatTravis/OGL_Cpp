#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath);

static unsigned int CompileShader(unsigned int type, const std::string& source);

unsigned int CreateShader();