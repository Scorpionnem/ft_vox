/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:32:50 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/12 22:40:53 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

void resize_hook(GLFWwindow* window, int width, int height)
{
	(void)window;(void)width;(void)height;
	glViewport(0, 0, width, height);
}

void	key_hook(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float cameraSpeed = 15.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -=  glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos +=  glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	// if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	// 	player_y -= 0.1f;
	// if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	// 	player_y += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		yaw -= 1.f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		yaw += 1.f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		pitch += 1.f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		pitch -= 1.f;
}

void	move_mouse_hook(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;
	(void)xpos;
	(void)ypos;

	// double	wwidth;
	// double	wheight;
	
	static float lastX = 400;
	static float lastY = 400;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed: y ranges bottom to top
	
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	
	yaw += xoffset;
	pitch += yoffset;
	
	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	// getMouseRealPos(window, &wwidth, &wheight, xpos, ypos);
	// square_vertices[24] = wwidth;
	// square_vertices[25] = wheight;
	// square_vertices[0] = 0 - wwidth;
	// square_vertices[1] = wheight;
	// std::cout << xpos << std::endl;
	// triangle_vertices1[] = ypos / 800.f;
}
