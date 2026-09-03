#ifndef VAO_H
#define VAO_H

#include <GL/gl.h>
#include <GL/glext.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "VBO.h"

typedef struct {
	GLuint ID;
} VAO;

VAO CreateVAO() {
	VAO v;
	glGenVertexArrays(1, &v.ID);
	return v;
}

void LinkAttrib(VBO v, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset) {
	BindVBO(v);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

	glEnableVertexAttribArray(layout);
	UnbindVBO();
}

void BindVAO(VAO v) {
	glBindVertexArray(v.ID);

}

void UnbindVAO() {
	glBindVertexArray(0);
}

void DeleteVAO(VAO v) {
	glDeleteVertexArrays(1, &v.ID);
}

#endif
