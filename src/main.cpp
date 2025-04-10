/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/10 17:04:50 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

float vertices[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
	};

const char	*vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char	*fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void	initGLFW(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void	processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		for (int i = 0; i < 12; i++)
			if (i == 0 || i == 3 || i == 6 || i == 9)
				vertices[i] -= 0.05f;
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		for (int i = 0; i < 12; i++)
			if (i == 0 || i == 3 || i == 6 || i == 9)
				vertices[i] += 0.05f;
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		for (int i = 0; i < 12; i++)
			if (i % 3)
				vertices[i] += 0.05f;
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		for (int i = 0; i < 12; i++)
			if (i % 3)
				vertices[i] -= 0.05f;
}

void	cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;
	(void)xpos;
	(void)ypos;
	// vertices[0] = xpos / 2000.f;
	// vertices[1] = ypos / 2000.f;
	// std::cout << xpos << " GLFWwindow* window, double xpos, double ypos" << ypos << std::endl;
}

GLFWwindow	*initWindow(void)
{
	GLFWwindow	*res = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (!res)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(res);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return (NULL);
	}
	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(res, framebuffer_size_callback);
	glfwSetCursorPosCallback(res, cursor_position_callback);
	return (res);
}

// void	draw_rectangle(double x, double y, double size)
// {
	
// }

int	main(void)
{
	initGLFW();
	
	GLFWwindow	*window = initWindow();

	if (!window)
		return (1);
	
	unsigned int	vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int	success;
	char	infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	unsigned int	fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	unsigned int	shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int	VBO;
	unsigned int	VAO;
	unsigned int	EBO;

	unsigned int	indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return (0);
}
