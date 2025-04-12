/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vox.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:10 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/12 18:32:53 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "glad.h"
#include "glfw3.h"

#include "Shader.hpp"

//init.cpp
GLFWwindow	*initWindow(void);

//hooks.cpp
void 	resize_hook(GLFWwindow* window, int width, int height);
void	move_mouse_hook(GLFWwindow* window, double xpos, double ypos);
void	key_hook(GLFWwindow *window);

//utils.cpp
void	getMouseRealPos(GLFWwindow* window, double *width, double *height, double xpos, double ypos);

extern float square_vertices[];
