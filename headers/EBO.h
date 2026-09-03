#ifndef EBO_H
#define EBO_H

#include <GL/glext.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

typedef struct {
	GLuint ID;
} EBO;

EBO CreateEBO(GLuint *indices, GLsizeiptr size) {
	EBO e;
	glGenBuffers(1, &e.ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	return e;
}

void BindEBO(EBO e) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e.ID);
}

void UnbindEBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DeleteEBO(EBO e) {
	glDeleteBuffers(1, &e.ID);
}

#endif
