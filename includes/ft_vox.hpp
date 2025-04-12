/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vox.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:10 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/12 22:44:07 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "glad.h"
#include "glfw3.h"

#include "Shader.hpp"
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc/type_ptr.hpp"

//init.cpp
GLFWwindow	*initWindow(void);

//hooks.cpp
void 	resize_hook(GLFWwindow* window, int width, int height);
void	move_mouse_hook(GLFWwindow* window, double xpos, double ypos);
void	key_hook(GLFWwindow *window);

//utils.cpp
void	getMouseRealPos(GLFWwindow* window, double *width, double *height, double xpos, double ypos);

extern float square_vertices[];
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern float	deltaTime;
extern float 	yaw;
extern float pitch;
