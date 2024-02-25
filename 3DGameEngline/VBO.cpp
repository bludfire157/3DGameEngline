#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {

	// Create the VBO object
	glGenBuffers(1, &ID);

	// Set the VBO as the GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Add the triangle data to the buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind() {

	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {

	glDeleteBuffers(1, &ID);
}
