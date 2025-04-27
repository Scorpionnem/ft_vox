/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:30:54 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/26 17:57:38 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include "Camera.hpp"

glm::vec3 pos;
glm::vec3 front;
glm::vec3 up;

float	deltaTime = 0.0f;
float	lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;

float	SCREEN_WIDTH = 800.0f;
float	SCREEN_HEIGHT = 800.0f;

Camera::Camera()
{
	pos = glm::vec3(0.0f, 3.0f, 0.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void	Camera::update()
{
	this->direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->direction.y = sin(glm::radians(pitch));
	this->direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);
}

glm::mat4	Camera::getViewMatrix()
{
	return (glm::lookAt(pos, pos + front, up));
}
