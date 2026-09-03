#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "cglm/affine-pre.h"
#include "cglm/cam.h"
#include "cglm/mat4.h"
//#include "headers/shapes.h"
#include "cglm/util.h"
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
		// Front face (+Z)
		-0.5f, -0.5f,  0.5f,		CHLORINE_BLUE,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		CHLORINE_BLUE,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		CHLORINE_BLUE,		1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,		CHLORINE_BLUE,		0.0f, 1.0f,
		// Back face (-Z)
		 0.5f, -0.5f, -0.5f,		KREMA_PURPLE,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,		KREMA_PURPLE,		1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,		KREMA_PURPLE,		1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,		KREMA_PURPLE,		0.0f, 1.0f,
		// Right face (+X)
		 0.5f, -0.5f,  0.5f,		KREMA_ORANGE,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		KREMA_ORANGE,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		KREMA_ORANGE,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,		KREMA_ORANGE,		0.0f, 1.0f,
		// Left face (-X)
		-0.5f, -0.5f, -0.5f,		KREMA_GREEN,		0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,		KREMA_GREEN,		1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,		KREMA_GREEN,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,		KREMA_GREEN,		0.0f, 1.0f,
		// Top face (+Y)
		-0.5f,  0.5f,  0.5f,		PURE_WHITE,			0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		PURE_WHITE,			1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		PURE_WHITE,			1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,		PURE_WHITE,			0.0f, 1.0f,
		// Bottom face (-Y)
		-0.5f, -0.5f, -0.5f,		PURE_BLACK,			0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		PURE_BLACK,			1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		PURE_BLACK,			1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,		PURE_BLACK,			0.0f, 1.0f,
	};

	GLuint indices[] = {
		 0,  1,  2,  2,  3,  0,
		 4,  5,  6,  6,  7,  4,
		 8,  9, 10, 10, 11,  8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
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

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);


		ActivateShader(shaderProgram);

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = crntTime;
		}

		mat4 model;
		mat4 view;
		mat4 proj;

		glm_mat4_identity(model);
		glm_mat4_identity(view);
		glm_mat4_identity(proj);

		glm_rotate(model, glm_rad(rotation), (vec3){0.0f, 1.0f, 0.0f});
		glm_translate(view, (vec3){0.0, -0.5f, -6.0});
		glm_perspective(glm_rad(45.0f), (float)windowWidth/windowHeight, 0.1f, 100.0f, proj);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float*)model);

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float*)view);

		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, (float*)proj);


		glUniform1f(uniID, 0.5f);
		BindTexture(imageTexture);

		BindVAO(VAO1);
	
		glClearColor(PURE_BLACK, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
