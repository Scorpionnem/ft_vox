/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/12 19:36:16 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float square_vertices[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
	};

unsigned int square_indices[] = {  // note that we start from 0!
    0, 1, 3,
	1, 2, 3
};

const char	*fragmentShaderSource1 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 fragCoord;\n"
"void main()\n"
"{\n"
" FragColor = vec4(fragCoord.x, 0.1f, 0.5f, 1.0f);\n"
"}\0";

// void	render_triangle(unsigned int shader, float *vertices)
// {
// }

// void	load_triangle_objects(unsigned int *VAO, unsigned int *VBO, float *vertices)
// {
// 	glGenVertexArrays(1, VAO);
//     glGenBuffers(1, VBO);

// 	(void)vertices;
// 	glBindVertexArray(*VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, *VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices1), vertices, GL_STATIC_DRAW);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
// 	glBindBuffer(GL_ARRAY_BUFFER, 0); 
// 	glBindVertexArray(0);
// }

void	load_multiple_objects(unsigned int *EBO, unsigned int *VAO, unsigned int *VBO, float *vertices, unsigned int *indices)
{
	glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);
}

#include <cmath>
#include <sys/time.h>
#include <unistd.h>

class	Texture
{
	public:
		Texture(const char *path)
		{
			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(path, &this->width, &this->height, &this->nrChannels, 0);
			glGenTextures(1, &this->ID);
			glBindTexture(GL_TEXTURE_2D, this->ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		unsigned char	*data;
		unsigned int	ID;
		int width;
		int height;
		int nrChannels;
};

int	main(void)
{	
	GLFWwindow	*window = initWindow();
	if (!window)
		return (1);
	
	Shader	shaderProgram("shaders/shader.vs", "shaders/shader.fs");
	Texture	texture("textures/image.png");

	unsigned int VBO, VAO;
	unsigned int VBO1, VAO1, EBO;
	
	while (!glfwWindowShouldClose(window))
	{
		key_hook(window);

		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		load_multiple_objects(&EBO, &VAO1, &VBO1, square_vertices, square_indices);
		shaderProgram.setFloat("caca", -0.5f);
		shaderProgram.use();
		glBindTexture(GL_TEXTURE_2D, texture.ID);
		glBindVertexArray(VAO1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
	glDeleteProgram(shaderProgram.ID);
	glDeleteTextures(1, &texture.ID);
	glfwTerminate();
	return (0);
}
