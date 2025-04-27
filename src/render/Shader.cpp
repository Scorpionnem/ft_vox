/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:20:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/26 11:25:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include "Shader.hpp"

static int	loadVertexShader(const char *shader)
{
	int				success;
	char			infoLog[512];
	unsigned int	res = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(res, 1, &shader, NULL);
	glCompileShader(res);
	glGetShaderiv(res, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(res, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return (-1);
	}
	return (res);
}

static int	loadFragmentShader(const char *shader)
{
	int				success;
	char			infoLog[512];
	unsigned int	res = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(res, 1, &shader, NULL);
	glCompileShader(res);
	glGetShaderiv(res, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(res, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return (-1);
	}
	return (res);
}

static int	loadShaderProgram(const char *vertex, const char *fragment)
{
	unsigned int	res;
	int				success;
	char			infoLog[512];
	int				vertexShader;
	int				fragmentShader;
	
	vertexShader = loadVertexShader(vertex);
	if (vertexShader == -1)
		return (0);
	fragmentShader = loadFragmentShader(fragment);
	if (fragmentShader == -1)
		return (0);

	res = glCreateProgram();
	glAttachShader(res, vertexShader);
	glAttachShader(res, fragmentShader);
	glLinkProgram(res);
	glGetProgramiv(res, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(res, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return (0);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return (res);
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	std::string	vertexCode;
	std::string	fragmentCode;
	std::ifstream	vShaderFile;
	std::ifstream	fShaderFile;

	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char	*vShaderCode = vertexCode.c_str();
	const char	*fShaderCode = fragmentCode.c_str();
	
	this->ID = loadShaderProgram(vShaderCode, fShaderCode);
}

Shader::Shader(unsigned int ID)
{
	this->ID = ID;
}

void	Shader::use()
{
	glUseProgram(this->ID);
}

void	Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void	Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void	Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void	Shader::setMat4(const std::string &name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void	Shader::setVec3(const std::string &name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(value));
}
