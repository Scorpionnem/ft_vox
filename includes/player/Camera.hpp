/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:08 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/26 10:43:30 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

extern glm::vec3 pos;
extern glm::vec3 front;
extern glm::vec3 up;

extern float	deltaTime;
extern float	lastFrame;

extern float yaw;
extern float pitch;

extern float	SCREEN_WIDTH;
extern float	SCREEN_HEIGHT;

class Camera
{
	public:
		Camera();
		void	update();
		glm::mat4	getViewMatrix();
		glm::vec3 direction;
		
};
