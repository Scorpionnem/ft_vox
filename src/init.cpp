/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:31:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/12 14:32:22 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

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
		glfwTerminate();
		return (NULL);
	}
	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(res, resize_hook);
	glfwSetCursorPosCallback(res, move_mouse_hook);
	return (res);
}
