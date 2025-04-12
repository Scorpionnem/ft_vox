/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/12 22:52:31 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float square_vertices[] = {
	-0.5f,	-0.5f,	-0.5f,		0.0f,	0.0f,
	0.5f,	-0.5f,	-0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	-0.5f,		1.0f,	1.0f,
	0.5f,	0.5f,	-0.5f,		1.0f,	1.0f,
	-0.5f,	0.5f,	-0.5f,		0.0f,	1.0f,
	-0.5f,	-0.5f,	-0.5f,		0.0f,	0.0f,
	-0.5f,	-0.5f,	0.5f,		0.0f,	0.0f,
	0.5f,	-0.5f,	0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	1.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	1.0f,
	-0.5f,	0.5f,	0.5f,		0.0f,	1.0f,
	-0.5f,	-0.5f,	0.5f,		0.0f,	0.0f,
	-0.5f,	0.5f,	0.5f,		1.0f,	0.0f,
	-0.5f,	0.5f,	-0.5f,		1.0f,	1.0f,
	-0.5f,	-0.5f,	-0.5f,		0.0f,	1.0f,
	-0.5f,	-0.5f,	-0.5f,		0.0f,	1.0f,
	-0.5f,	-0.5f,	0.5f,		0.0f,	0.0f,
	-0.5f,	0.5f,	0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	-0.5f,		1.0f,	1.0f,
	0.5f,	-0.5f,	-0.5f,		0.0f,	1.0f,
	0.5f,	-0.5f,	-0.5f,		0.0f,	1.0f,
	0.5f,	-0.5f,	0.5f,		0.0f,	0.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	0.0f,
	-0.5f,	-0.5f,	-0.5f,		0.0f,	1.0f,
	0.5f,	-0.5f,	-0.5f,		1.0f,	1.0f,
	0.5f,	-0.5f,	0.5f,		1.0f,	0.0f,
	0.5f,	-0.5f,	0.5f,		1.0f,	0.0f,
	-0.5f,	-0.5f,	0.5f,		0.0f,	0.0f,
	-0.5f,	-0.5f,	-0.5f,		0.0f,	1.0f,
	-0.5f,	0.5f,	-0.5f,		0.0f,	1.0f,
	0.5f,	0.5f,	-0.5f,		1.0f,	1.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	0.0f,
	0.5f,	0.5f,	0.5f,		1.0f,	0.0f,
	-0.5f,	0.5f,	0.5f,		0.0f,	0.0f,
	-0.5f,	0.5f,	-0.5f,		0.0f,	1.0f
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
	(void)EBO;(void)indices;(void)vertices;
	glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
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
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float	deltaTime = 0.0f;
float	lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;

#include <sys/time.h>
void display_fps(struct timeval start_time, int target_fps)
{
    struct timeval        end_time;
    int                    start;
    int                    end;

    gettimeofday(&end_time, NULL);
    start = start_time.tv_sec * 1000000 + start_time.tv_usec;
    end = end_time.tv_sec * 1000000 + end_time.tv_usec;
    while (1000000 / abs(end - start + 1) > target_fps)
    {
        gettimeofday(&end_time, NULL);
        end = end_time.tv_sec * 1000000 + end_time.tv_usec;
    }
    gettimeofday(&end_time, NULL);
    end = end_time.tv_sec * 1000000 + end_time.tv_usec;
    printf("%d\n", 1000000 / abs(end - start + 1));
}

int	main(void)
{	
	GLFWwindow	*window = initWindow();
	if (!window)
		return (1);
	
	Shader	shaderProgram("shaders/shader.vs", "shaders/shader.fs");
	Texture	texture("textures/mossy_bricks.png");

	unsigned int VBO, VAO;
	unsigned int VBO1, VAO1, EBO;

	load_multiple_objects(&EBO, &VAO1, &VBO1, square_vertices, square_indices);

	glEnable(GL_DEPTH_TEST);

	std::vector<glm::vec3>	cubes;

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 10; k++)
				cubes.push_back(glm::vec3(i, j, k));

	// glm::vec3	cubPositions[] =
	// {
	// 	glm::vec3( 0.0f, 0.0f, 0.0f),
	// 	glm::vec3( 0.0f, 1.0f, 0.0f),
	// 	glm::vec3( 0.0f, 2.0f, 0.0f),
	// 	glm::vec3( 1.0f, -1.0f, 0.0f),
	// 	glm::vec3( -1.0f, -1.0f, 0.0f),
	// 	glm::vec3(-1.7f, 3.0f, -7.5f),
	// 	glm::vec3( 1.3f, -2.0f, -2.5f),
	// 	glm::vec3( 1.5f, 2.0f, -2.5f),
	// 	glm::vec3( 1.5f, 0.2f, -1.5f),
	// 	glm::vec3(-1.3f, 1.0f, -1.5f)
	// };

	glBindTexture(GL_TEXTURE_2D, texture.ID);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	struct timeval tv;

	while (!glfwWindowShouldClose(window))
	{
		gettimeofday(&tv, NULL);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		key_hook(window);

		glClearColor(0.2f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();


		
		glm::mat4	view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)); // convert to radians first
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw));

		cameraFront = glm::normalize(direction);
		
		projection = glm::perspective(glm::radians(90.0f), 800.0f / 800.0f, 0.1f, 100.0f);
		// view = glm::translate(view, glm::vec3(player_x, player_y, player_z));

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		unsigned int	Loc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(view));
		Loc = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(projection));
		

		
		glBindVertexArray(VAO1);
		for(std::vector<glm::vec3>::iterator it = cubes.begin(); it != cubes.end(); it++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, *it);
			// float angle = 20.0f * (i + 1) * glfwGetTime();
			float angle = 0;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			
			Loc = glGetUniformLocation(shaderProgram.ID, "model");
			glUniformMatrix4fv(Loc, 1, GL_FALSE, glm::value_ptr(model));
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		display_fps(tv, 500);
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
