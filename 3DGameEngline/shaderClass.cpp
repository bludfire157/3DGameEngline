#include "shaderClass.h"

std::string get_file_contents(const char* fileName) {

	// Creating the stream to access the file
	std::ifstream in(fileName, std::ios::binary);

	// check if can access the stream
	if (in) {

		// Create a string to read and then return it
		std::string contents;

		// Set the length of contents to the length of the file
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);

		// Reading the file
		in.read(&contents[0], contents.size());

		// Close the stream
		in.close();

		return contents;
	}

	// Couldn't access file
	throw errno;
}

Shader::Shader(const char* vertexFile, const char* fregmentFile) {

	// Gets the contnents of the files
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fregmentCode = get_file_contents(fregmentFile);

	// Convert the content to a char array
	const char* vertexSource = vertexCode.c_str();
	const char* fregmentSource = fregmentCode.c_str();

	// Create Vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Add the code for the vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	// Compile the code
	glCompileShader(vertexShader);

	// Create Fragment shader object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Add the code for the Fragment shader object
	glShaderSource(fragmentShader, 1, &fregmentSource, NULL);

	// Compile the code
	glCompileShader(fragmentShader);


	// Create shader program object
	ID = glCreateProgram();

	// Add the shaders to the shader program object
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Link the shaders together in the shader program object
	glLinkProgram(ID);

	// Delete the shader objects since they are already added and linked in the shader program object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {

	glUseProgram(ID);
}

void Shader::Delete() {

	glDeleteProgram(ID);
}
