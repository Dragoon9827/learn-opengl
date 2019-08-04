#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
	//program id
	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragPath);

	void use();

	void setBool(const std::string &name, bool value)const;
	void setInt(const std::string &name, int value)const;
	void setFloat(const std::string &name, float value)const;
};

#endif