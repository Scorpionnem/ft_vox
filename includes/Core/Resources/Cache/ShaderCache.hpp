/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderCache.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:05:45 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/17 16:01:41 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unordered_map>
#include <memory>
#include "Shader.hpp"

class	Engine;

class	ShaderCache
{
	public:
		ShaderCache(Engine *engine) : _engine(engine)
		{
			(void)_engine;
		}
		~ShaderCache() {}

		std::shared_ptr<Shader>	get(const std::string &path);
		std::shared_ptr<Shader>	getCompute(const std::string &path);
	private:
		Engine	*_engine;
		std::unordered_map<std::string, std::shared_ptr<Shader>>	_shaders;
};
