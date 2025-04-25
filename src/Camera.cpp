/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:30:54 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/24 18:51:59 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

glm::vec3 pos;
glm::vec3 front;
glm::vec3 up;

float	deltaTime = 0.0f;
float	lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;
