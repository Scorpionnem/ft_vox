/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:32:50 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/12 19:32:31 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

void resize_hook(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void	key_hook(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void	move_mouse_hook(GLFWwindow* window, double xpos, double ypos)
{
	(void)window;
	(void)xpos;
	(void)ypos;

	double	wwidth;
	double	wheight;
	
	getMouseRealPos(window, &wwidth, &wheight, xpos, ypos);
	square_vertices[24] = wwidth;
	square_vertices[25] = wheight;
	square_vertices[0] = 0 - wwidth;
	square_vertices[1] = wheight;
	std::cout << xpos << std::endl;
	// triangle_vertices1[] = ypos / 800.f;
}
