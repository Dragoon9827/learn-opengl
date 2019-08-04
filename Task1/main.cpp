#include "opengl.h"
#include "shader.h"

#include <stdio.h>
#include <iostream>
#include <filesystem>

//vertex shader
const char* vertexShaderSource = 
	"#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 outColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"	outColor = aColor;\n"
	"}\0";

//fragment shader
const char* fragShaderSource = 
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec3 outColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(outColor, 0.5f);\n"
	"}\0";

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ³õÊ¼»¯´°¿Ú
	GLFWwindow* window = glfwCreateWindow(800, 600, "learn opengl", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "fail to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "fail to init glad" << std::endl;
		return -1;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	//SHADER
	Shader shader("shader/vertexShader.vs", "shader/fragmentShader.fs");

	/*
	//VERTEX SHADER
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//CHECK COMPILE
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "VERTEX SHADER COMPILE ERROR\n" << infoLog << std::endl;
	}

	//FRAGMENT SHADER
	int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	//CHECK COMPILE
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "FRAGMENT SHADER COMPILE ERROR\n" << infoLog << std::endl;
	}

	//LINK SHADER
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	//CHECK COMPILE
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "SHADER PROGRAM LINK ERROR\n" << infoLog << std::endl;
	}

	//DELETE SHADER because don't need them any more
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	*/

	glViewport(0, 0, 800, 600);

	//vertex info
	float vertices[] =
	{
		// position              // color					//texture
		-0.5f, -0.7f,  0.0f,    1.0f, 0.0f, 0.0f, 0.4f,		0.0f, 1.0f,		// bottom left
		 0.1f, -0.7f,  0.0f,	1.0f, 0.0f, 0.0f, 0.4f,		1.0f, 1.0f,		// bottom right
		-0.5f,  0.1f,  0.0f,	1.0f, 0.0f, 0.0f, 0.4f,		0.0f, 0.0f,		// top left
		 0.1f,  0.1f,  0.0f,	1.0f, 0.0f, 0.0f, 0.4f,		1.0f, 0.0f,		// top right

		-0.1f, -0.2f,  0.0f,	0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		 0.5f, -0.2f,  0.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		-0.1f,  0.6f,  0.0f,	0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		 0.5f,  0.6f,  0.0f,	0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 0.0f,
	};

	//indices info
	unsigned int indices[] =
	{
		4, 5, 6,
		5, 6, 7,
		0, 1, 2,
		1, 2, 3,
	};

	//vertex buffer
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// bind array buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// bind element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribution
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribution
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture attribution
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// unbind array buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	// mode: draw line gl_line    fill gl_fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// LOAD TEXTURE
	unsigned int texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("texture/1.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "fail to load texture" << std::endl;
	}
	stbi_image_free(data);

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering
		glClearColor(0, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		// use shader program
		// glUseProgram(shaderProgram);
		shader.use();

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// free resource
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}