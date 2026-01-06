/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LightCache.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:20:07 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 20:18:58 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Light.hpp"
#include <vector>

class	Engine;

class	LightCache
{
	public:
		LightCache(Engine *engine) : _engine(engine) {}
		~LightCache() {}

		std::shared_ptr<Light>	add(Vec3 pos, Vec3 color);
		void	setUniforms(std::shared_ptr<Shader> shader)
		{
			shader->use();
			shader->setInt("NR_POINT_LIGHTS", _lights.size());
			int	i = 0;
			for (auto light : _lights)
				light->setUniforms(i++, shader);
		}
		void	draw(Mat4 view, Mat4 proj)
		{
			for (auto light : _lights)
				light->draw(view, proj);
		}
		void	unload()
		{
			_lights.clear();
		}
	private:
		Engine	*_engine;
		std::vector<std::shared_ptr<Light>>	_lights;
};
