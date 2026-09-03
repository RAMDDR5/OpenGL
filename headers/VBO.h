#ifndef VBO_H
#define VBO_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

typedef struct {
	GLuint ID;
} VBO;

VBO CreateVBO(GLfloat* vertices, GLsizeiptr size) {
	VBO v;
	glGenBuffers(1, &v.ID);
	glBindBuffer(GL_ARRAY_BUFFER, v.ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	
	return v;
}

void BindVBO(VBO v) {
	glBindBuffer(GL_ARRAY_BUFFER, v.ID);
}

void UnbindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DeleteVBO(VBO v) {
	glDeleteBuffers(1, &v.ID);
}

#endif
