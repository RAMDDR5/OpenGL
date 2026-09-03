#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "headers/shapes.h"
#include "headers/shader.h"
#include "headers/VBO.h"
#include "headers/EBO.h"
#include "headers/VAO.h"
#include "headers/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define VERSION_MAJOR	4
#define VERSION_MINOR	6

#define MADRID_GOLD		0.9960784313f, 0.7450980392f, 0.0627450980f
#define YELLOW_GREEN	0.6039215686f, 0.8039215686f, 0.1960784313f
#define CHLORINE_BLUE	0.0470588235f, 0.6862745098f, 1.0000000000f
#define IMPERIAL_RED	0.9294117647f, 0.1607843137f, 0.2235294117f
#define KREMA_PURPLE	0.4627450980f, 0.0156862745f, 1.0000000000f
#define KREMA_GREEN		0.0078431372f, 0.5411764705f, 0.0588235294f
#define KREMA_ORANGE	0.9294117647f, 0.4392156862f, 0.0784313725f
#define PURE_WHITE		1.0000000000f, 1.0000000000f, 1.0000000000f
#define PURE_BLACK		0.0000000000f, 0.0000000000f, 0.0000000000f

int main(void) {
	glfwInit(); 

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		SQUARE_TOP_LEFT,		CHLORINE_BLUE,		0.0f, 1.0f,
		SQUARE_TOP_RIGHT,		KREMA_PURPLE,		1.0f, 1.0f,
		SQUARE_BOTTOM_RIGHT,	KREMA_ORANGE,		1.0f, 0.0f,
		SQUARE_BOTTOM_LEFT,		KREMA_GREEN,		0.0f, 0.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 3, 2
	};

	GLFWwindow *window = glfwCreateWindow(800, 800, "ObamaGL", NULL, NULL);
	int windowHeight, windowWidth;

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	Shader shaderProgram = CreateShader("headers/default.vert", "headers/default.frag");

	VAO VAO1 = CreateVAO();

	BindVAO(VAO1);

	VBO VBO1 = CreateVBO(vertices, sizeof(vertices));
	EBO EBO1 = CreateEBO(indices, sizeof(indices));

	LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	UnbindVAO();
	UnbindVBO();
	UnbindEBO();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); 

	Texture imageTexture = CreateTexture("image.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR);	
	texUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		ActivateShader(shaderProgram);
		glUniform1f(uniID, 0.5f);
		BindTexture(imageTexture);

		BindVAO(VAO1);
	
		glClearColor(PURE_BLACK, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}

	DeleteVAO(VAO1);
	DeleteVBO(VBO1);
	DeleteEBO(EBO1);
	DeleteShader(shaderProgram);
	DeleteTexture(imageTexture);

	glfwDestroyWindow(window); 
	glfwTerminate();
	
	return 0;
}
