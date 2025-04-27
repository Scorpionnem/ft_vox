/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:31:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 13:18:26 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include "Camera.hpp"
#include "Hooks.hpp"
#include "Input.hpp"

static void	initGLFW(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	
}

GLFWwindow	*initWindow(void)
{
	initGLFW();
	
	GLFWwindow	*res = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ft_vox", NULL, NULL);
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
		glfwTerminate();
		return (NULL);
	}
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(res, resize_hook);
	glfwSetCursorPosCallback(res, move_mouse_hook);
	glfwSetCharCallback(res, char_callback);
	glfwSetKeyCallback(res, special_callback);
	glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	return (res);
}
