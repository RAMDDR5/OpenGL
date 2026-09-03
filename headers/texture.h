#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "shader.h"

typedef struct {
	GLuint ID;
	GLenum type;
} Texture;

Texture CreateTexture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, GLint filter) {
	Texture t;
	
	int imageWidth, imageHeight, numColCh;
	stbi_set_flip_vertically_on_load(1);
	unsigned char *bytes = stbi_load(image, &imageWidth, &imageHeight, &numColCh, 0);

	t.type = texType;

	glGenTextures(1, &t.ID);
	glActiveTexture(slot);
	glBindTexture(texType, t.ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, imageWidth, imageHeight, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);

	return t;
}

void texUnit(Shader s, const char* uniform, GLuint unit) {
	GLuint tex0Uni = glGetUniformLocation(s.ID, uniform);
	ActivateShader(s);
	glUniform1i(tex0Uni, unit);
}

void BindTexture(Texture t) {
	glBindTexture(t.type, t.ID);
}

void UnbindTexture(Texture t) {
	glBindTexture(t.type, 0);
}

void DeleteTexture(Texture t) {
	glDeleteTextures(1, &t.ID);
}

#endif
