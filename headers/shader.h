#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

char *getFileContents(const char* filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Couldnt open file: %s", filename);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);

	rewind(file);
	char *buffer = malloc(size + 1);
	fread(buffer, 1, size, file);

	buffer[size] = '\0';
	return buffer;
}

typedef struct {
	GLuint ID;
} Shader;

Shader CreateShader(const char* vertexFile, const char* fragmentFile) {
	Shader s;

	char *vertexSource = getFileContents(vertexFile);
	char *fragmentSource = getFileContents(fragmentFile);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar **)&vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar **)&fragmentSource, NULL);
	glCompileShader(fragmentShader);

	s.ID = glCreateProgram();
	glAttachShader(s.ID, vertexShader);
	glAttachShader(s.ID, fragmentShader);

	glLinkProgram(s.ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	free(vertexSource);
	free(fragmentSource);

	return s;
}

void ActivateShader(Shader s) {
	glUseProgram(s.ID);
}

void DeleteShader(Shader s) {
	glDeleteProgram(s.ID);
}

#endif
