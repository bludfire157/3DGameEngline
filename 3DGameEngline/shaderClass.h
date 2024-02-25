#ifndef  SHADER_CLASS_H 
#define SHADER_CLASS_H 

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// get the contents of a file
std::string get_file_contents(const char* fileName);

class Shader {

public:
	GLuint ID;

	Shader(const char* vertexFile, const char* fregmentFile);

	void Activate();
	void Delete();
};

#endif
