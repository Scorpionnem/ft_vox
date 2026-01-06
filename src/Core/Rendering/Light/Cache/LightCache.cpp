/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LightCache.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:28:59 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 16:51:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"

std::shared_ptr<Light>	LightCache::add(Vec3 pos, Vec3 color)
{
	_lights.push_back(std::make_shared<Light>(_engine->getMeshCache(), _engine->getShaderCache()));
	_lights.back()->create(pos, color);
	return (_lights.back());
}
