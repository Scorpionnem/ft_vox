/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 14:21:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float square_vertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
};

float cube_vertices[] = {
// front face
-0.5f,	-0.5f,	0.5f,	0.0f, 0.0f, 1.0f,	0.0f,	0.0f,	// bottom-left	7
0.5f,	-0.5f,	0.5f,	0.0f, 0.0f, 1.0f,	1.0f,	0.0f,	// bottom-right	8
0.5f,	0.5f,	0.5f,	0.0f, 0.0f, 1.0f,	1.0f,	1.0f,	// top-right		9
0.5f,	0.5f,	0.5f,	0.0f, 0.0f, 1.0f,	1.0f,	1.0f,	// top-right		10
-0.5f,	0.5f,	0.5f,	0.0f, 0.0f, 1.0f,	0.0f,	1.0f,	// top-left		11
-0.5f,	-0.5f,	0.5f,	0.0f, 0.0f, 1.0f,	0.0f,	0.0f,	// bottom-left	12
// back face
-0.5f,	-0.5f,	-0.5f,	0.0f, 0.0f, -1.0f,	0.0f,	0.0f,	// bottom-left	0
0.5f,	0.5f,	-0.5f,	0.0f, 0.0f, -1.0f,	1.0f,	1.0f,	// top-right		1
0.5f,	-0.5f,	-0.5f,	0.0f, 0.0f, -1.0f,	1.0f,	0.0f,	// bottom-right	2
0.5f,	0.5f,	-0.5f,	0.0f, 0.0f, -1.0f,	1.0f,	1.0f,	// top-right		3
-0.5f,	-0.5f,	-0.5f,	0.0f, 0.0f, -1.0f,	0.0f,	0.0f,	// bottom-left	4
-0.5f,	0.5f,	-0.5f,	0.0f, 0.0f, -1.0f,	0.0f,	1.0f,	// top-left		6
// left face
-0.5f,	0.5f,	0.5f,	-1.0f, 0.0f, 0.0f, 1.0f,	0.0f,	// top-right		13
-0.5f,	0.5f,	-0.5f,	-1.0f, 0.0f, 0.0f, 1.0f,	1.0f,	// top-left		14
-0.5f,	-0.5f,	-0.5f,	-1.0f, 0.0f, 0.0f, 0.0f,	1.0f,	// bottom-left	15
-0.5f,	-0.5f,	-0.5f,	-1.0f, 0.0f, 0.0f, 0.0f,	1.0f,	// bottom-left	16
-0.5f,	-0.5f,	0.5f,	-1.0f, 0.0f, 0.0f, 0.0f,	0.0f,	// bottom-right	17
-0.5f,	0.5f,	0.5f,	-1.0f, 0.0f, 0.0f, 1.0f,	0.0f,	// top-right		18
// right face
0.5f,	0.5f,	0.5f,	1.0f, 0.0f, 0.0f, 1.0f,	0.0f,	// top-left		19
0.5f,	-0.5f,	-0.5f,	1.0f, 0.0f, 0.0f, 0.0f,	1.0f,	// bottom-right	20
0.5f,	0.5f,	-0.5f,	1.0f, 0.0f, 0.0f, 1.0f,	1.0f,	// top-right		21
0.5f,	-0.5f,	-0.5f,	1.0f, 0.0f, 0.0f, 0.0f,	1.0f,	// bottom-right	22
0.5f,	0.5f,	0.5f,	1.0f, 0.0f, 0.0f, 1.0f,	0.0f,	// top-left		23
0.5f,	-0.5f,	0.5f,	1.0f, 0.0f, 0.0f, 0.0f,	0.0f,	// bottom-left	24
// bottom face
-0.5f,	-0.5f,	-0.5f,	0.0f, -1.0f, 0.0f, 0.0f,	1.0f,	// top-right	25
0.5f,	-0.5f,	-0.5f,	0.0f, -1.0f, 0.0f, 1.0f,	1.0f,	// top-left		26
0.5f,	-0.5f,	0.5f,	0.0f, -1.0f, 0.0f, 1.0f,	0.0f,	// bottom-left	27
0.5f,	-0.5f,	0.5f,	0.0f, -1.0f, 0.0f, 1.0f,	0.0f,	// bottom-left	28
-0.5f,	-0.5f,	0.5f,	0.0f, -1.0f, 0.0f, 0.0f,	0.0f,	// bottom-right	29
-0.5f,	-0.5f,	-0.5f,	0.0f, -1.0f, 0.0f, 0.0f,	1.0f,	// top-right	30
// top face
-0.5f,	0.5f,	-0.5f,	0.0f, 1.0f, 0.0f, 0.0f,	1.0f,	// top-left		31
0.5f,	0.5f,	0.5f,	0.0f, 1.0f, 0.0f, 1.0f,	0.0f,	// bottom-right	32
0.5f,	0.5f,	-0.5f,	0.0f, 1.0f, 0.0f, 1.0f,	1.0f,	// top-right		33
0.5f,	0.5f,	0.5f,	0.0f, 1.0f, 0.0f, 1.0f,	0.0f,	// bottom-right	34
-0.5f,	0.5f,	-0.5f,	0.0f, 1.0f, 0.0f, 0.0f,	1.0f,	// top-left		35
-0.5f,	0.5f,	0.5f,	0.0f, 1.0f, 0.0f, 0.0f,	0.0f // bottom-left	36
};

#include "ft_vox.hpp"
#include "EBO.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "Shader.hpp"
#include "Assets.hpp"
#include "Camera.hpp"
#include "Hooks.hpp"
#include "Utils.hpp"

#include "Mesh.hpp"

void display_fps(GLFWwindow *window, float deltaTime)
{
	std::stringstream	strs;
	strs << (int)(1.0f / deltaTime) << " fps";

	glfwSetWindowTitle(window, strs.str().c_str());
}

#include "Block.hpp"
#include "Chunk.hpp"

#include "World.hpp"

int	main(void)
{	
	GLFWwindow	*window = initWindow();
	if (!window)
		return (1);

	loadAssets();

	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Camera	camera;
	
	world.addChunk(glm::vec3(0, 0, 0));
	world.getChunk(glm::vec3(0, 0, 0))->gen();
	world.addChunk(glm::vec3(0, 1, 0));
	world.getChunk(glm::vec3(0, 1, 0))->gen();
	world.addChunk(glm::vec3(1, 0, 0));
	world.getChunk(glm::vec3(1, 0, 0))->gen();
	world.addChunk(glm::vec3(1, 1, 0));
	world.getChunk(glm::vec3(1, 1, 0))->gen();

	// glfwSwapInterval(0);

	assets.getTexture("atlas").bind();
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		

		key_hook(window);

		
		camera.update();
		glm::mat4	view = camera.getViewMatrix();
		glm::mat4	projection = glm::perspective(glm::radians(90.0f), SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 160.0f);;
		glm::mat4	model(1.0f);
		
		
		assets.getShader("block").use();
		assets.getShader("block").setMat4("view", view);
		assets.getShader("block").setMat4("projection", projection);
		assets.getShader("block").setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
		assets.getShader("block").setVec3("lightPos", glm::vec3(0, 0, 0));
		assets.getShader("block").setMat4("model", model);
		assets.getShader("block").setFloat("time", glfwGetTime());

		world.drawChunks(pos, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
		if ((int)lastFrame != (int)currentFrame)
			display_fps(window, deltaTime);
		lastFrame = currentFrame;
	}
	assets.free();
	glfwTerminate();
	return (0);
}
