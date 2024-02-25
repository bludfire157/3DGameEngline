#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size) {

	// Create the VBO object
	glGenBuffers(1, &ID);

	// Set the VBO as the GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// Add the triangle data to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {

	glDeleteBuffers(1, &ID);
}
