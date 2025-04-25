/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:08 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 14:53:13 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

class Camera
{
	public:
		Camera()
		{
			pos = glm::vec3(0.0f, 3.0f, 0.0f);
			front = glm::vec3(0.0f, 0.0f, -1.0f);
			up = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		void	update()
		{
			this->direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			this->direction.y = sin(glm::radians(pitch));
			this->direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			front = glm::normalize(direction);
		}
		glm::mat4	getViewMatrix()
		{
			return (glm::lookAt(pos, pos + front, up));
		}
		glm::vec3 direction;
		
};
