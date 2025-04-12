/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:30:52 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/12 16:34:31 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

void	getMouseRealPos(GLFWwindow* window, double *width, double *height, double xpos, double ypos)
{
	int	wwidth;
	int	wheight;
	
	glfwGetWindowSize(window, &wwidth, &wheight);
	(*width) = xpos / wwidth * 2 - 1;
	(*height) = (wheight - ypos) / wheight * 2 - 1;
}
