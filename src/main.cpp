/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 16:20:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include "EBO.hpp"

float	SCREEN_WIDTH = 800.0f;
float	SCREEN_HEIGHT = 800.0f;

float cube_vertices[] = {
	// back face
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left	0
0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right		1
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right	2
0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right		3
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left	4
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left		6
// front face
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left	7
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-right	8
0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right		9
0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right		10
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top-left		11
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left	12
// left face
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right		13
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-left		14
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left	15
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left	16
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right	17
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right		18
// right face
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left		19
0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right	20
0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right		21
0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right	22
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left		23
0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left	24
// bottom face
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right	25
0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-left		26
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left	27
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left	28
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right	29
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right	30
// top face
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left		31
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right	32
0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right		33
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right	34
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left		35
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f // bottom-left	36
};

const unsigned int cube_indices[] = {
    0, 1, 2,    3, 4, 5,      // back face
    6, 7, 8,    9,10,11,      // front face
   12,13,14,   15,16,17,      // left face
   18,19,20,   21,22,23,      // right face
   24,25,26,   27,28,29,      // bottom face
   30,31,32,   33,34,35       // top face
};

float square_vertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
};

std::vector<Block>	cubes;

Assets	assets;

void	loadAssets()
{
	assets.loadTexture("missing", "textures/missing.png");
	assets.loadTexture("dirt", "textures/dirt.png");
	assets.loadTexture("grass_top", "textures/grass_top.png");
	assets.loadTexture("grass_side", "textures/grass_side.png");
}

Block genBlock(std::string id)
{
	if (id == "grass_block")
		return (Block(glm::vec3(0, 0, 0), "grass", "grass_top"));
	if (id == "dirt")
		return (Block(glm::vec3(0, 0, 0), "dirt", "dirt"));
	if (id == "air")
		return (Block(glm::vec3(0, 0, 0), "air", "air"));
	return (Block(glm::vec3(0, 0, 0), "", ""));
}

#include "World.hpp"

int	main(void)
{	
	GLFWwindow	*window = initWindow();
	if (!window)
		return (1);

	loadAssets();

	Shader	shaderProgram("shaders/block_shader.vs", "shaders/block_shader.fs");

	assets.loadShader("block", shaderProgram.ID);

	VAO	vao;
	vao.bind();
	VBO	vbo(cube_vertices, sizeof(cube_vertices));
	EBO	ebo(cube_indices, 36 * sizeof(unsigned int));
	vao.attribFloat(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.attribFloat(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();

	std::vector<Chunk>	chunks;

	for (int x = 0; x < 4; x++)
		for (int z = 0; z < 4; z++)
			chunks.push_back(Chunk(glm::vec3(x, 0, z)));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	struct timeval tv;
	Camera	camera;

	for (int i = 0; i < 16; i++)
	{
		for (int x = 0; x < 16; x++)
			for (int z = 0; z < 16; z++)
				chunks[i].setBlock(x, 0, z, genBlock("grass"));
	}

	glfwSwapInterval(0);

	int	lastprout = 0;

	while (!glfwWindowShouldClose(window))
	{
		// std::cout << "World pos (x, y, z) " << pos.x << " " << pos.y << " " << pos.z << std::endl;
		// std::cout << "Chunk pos (x, y, z) " << (int)pos.x / 16 << " " << (int)pos.y / 16 << " " << (int)pos.z / 16 << std::endl;

		gettimeofday(&tv, NULL);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		key_hook(window);

		camera.update();
		glm::mat4	view = camera.getViewMatrix();
		glm::mat4	projection = glm::perspective(glm::radians(90.0f), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 160.0f);;
		shaderProgram.setMat4("view", view);
		shaderProgram.setMat4("projection", projection);

		vao.bind();

		for (int i = 0; i < 1; i++)
			chunks[i].draw();


		vao.unbind();

		glfwSwapBuffers(window);
		glfwPollEvents();

		if ((int)glfwGetTime() != lastprout)
		{
			display_fps(window, tv, 5000);
			lastprout = (int)glfwGetTime();
		}
	}
	glDeleteProgram(shaderProgram.ID);
	
	vao.free();
	vbo.free();
	assets.free();
	glfwTerminate();
	return (0);
}
