#include "opengl.h"
#include "Shader.h"
#include "Camera.h"

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

Camera mainCamera(glm::vec3(0.0f, 0.0f, 5.0f));

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

	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glDepthMask(GL_TRUE);

	//SHADER
	Shader shader("shader/vertexShader.vs", "shader/fragmentShader.fs");

	// glViewport(0, 0, 800, 600);

	//vertex info
	float vertices[] =
	{
		// position              // color					//texture
	// front
		-0.5f, -0.5f,  0.0f,    1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 0.0f,		// btttom left
		 0.2f, -0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 0.0f,		// bottom right
		-0.5f,  0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 1.0f,		// top left
		 0.2f,  0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 1.0f,		// top right

	// back
		 0.5f, -0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 0.0f,		// bottom left
		-0.5f, -0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 0.0f,		// bottom right
		 0.5f,  0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 1.0f,		// top left
		-0.5f,  0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 1.0f,		// top right

	// left
		-0.5f, -0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 0.0f,		// bottom left
		-0.5f, -0.5f,  0.0f,    1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 0.0f,		// bottom right
		-0.5f,  0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 1.0f,		// top left
		-0.5f,  0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 1.0f,		// top right

	// right
		 0.5f, -0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 0.0f,		// bottom left
		 0.5f, -0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 0.0f,		// bottom right
		 0.5f,  0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 1.0f,		// top left
		 0.5f,  0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 1.0f,		// top right

	// top
		-0.5f,  0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 0.0f,		// bottom left
		 0.5f,  0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 0.0f,		// bottom right
		-0.5f,  0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 1.0f,		// top left
		 0.5f,  0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 1.0f,		// top right

	// bottom
		-0.5f, -0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 0.0f,		// bottom left
		 0.5f, -0.5f,  1.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 0.0f,		// bottom right
		-0.5f, -0.5f,  0.0f,    1.0f, 1.0f, 1.0f, 0.5f,		0.0f, 1.0f,		// bottom left
		 0.5f, -0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 0.5f,		1.0f, 1.0f,		// bottom right
	};

	//indices info
	unsigned int indices[] =
	{
		 0, 1, 2,
		 1, 2, 3,
		 4, 5, 6,
		 5, 6, 7,
		 8, 9,10,
		 9,10,11,
		12,13,14,
		13,14,15,
		16,17,18,
		17,18,19,
		20,21,22,
		21,22,23
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

	shader.use();
	shader.setInt("texture", 0);

	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering
		glClearColor(0, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, texture);

		// use shader program
		// glUseProgram(shaderProgram);
		shader.use();

		glm::mat4 projection = glm::perspective(glm::radians(mainCamera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glm::mat4 view = mainCamera.GetViewMatrix();
		shader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
		shader.setMat4("model", model);

		// glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

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