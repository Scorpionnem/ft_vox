/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vox.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:33:10 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 12:45:38 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VOX_HPP
# define FT_VOX_HPP

int	convertIndex(int x, int y, int z);

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <vector>
# include <map>
# include "glad.h"
# include "glfw3.h"
# include <cmath>
# include <sys/time.h>
# include <unistd.h>

# include "VBO.hpp"
# include "VAO.hpp"

# include "../glm/glm/glm.hpp"
# include "../glm/glm/gtc/matrix_transform.hpp"
# include "../glm/glm/gtc/type_ptr.hpp"
# include "Shader.hpp"
# include "Texture.hpp"
# include "Block.hpp"
# include "Chunk.hpp"
# include "Assets.hpp"

extern Assets	assets;

extern float square_vertices[];
extern glm::vec3 pos;
extern glm::vec3 front;
extern glm::vec3 up;
extern float	deltaTime;
extern float 	yaw;
extern float 	pitch;
extern float	lastFrame;

extern float	SCREEN_WIDTH;
extern float	SCREEN_HEIGHT;

extern std::vector<Block>	cubes;

# include "Camera.hpp"

//init.cpp
GLFWwindow	*initWindow(void);

//hooks.cpp
void 	resize_hook(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void	move_mouse_hook(GLFWwindow* window, double xpos, double ypos);
void	key_hook(GLFWwindow *window);

//utils.cpp
void	getMouseRealPos(GLFWwindow* window, double *width, double *height, double xpos, double ypos);
void display_fps(GLFWwindow	*window, struct timeval start_time, int target_fps);
int	convertIndex(int x, int y, int z);

#endif