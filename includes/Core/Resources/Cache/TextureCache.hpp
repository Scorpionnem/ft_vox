/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureCache.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:01:13 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/05 17:09:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unordered_map>
#include <memory>
#include "Texture.hpp"

class	Engine;

class	TextureCache
{
	public:
		TextureCache(Engine *engine) : _engine(engine)
		{
			(void)_engine;
		}
		~TextureCache() {}

		std::shared_ptr<Texture>	get(const std::string &path)
		{
			auto	[it, inserted] = _textures.try_emplace(path);

			if (inserted)
			{
				it->second = std::make_shared<Texture>();
				it->second->load(path);
				it->second->upload();
			}

			return (it->second);
		}
	private:
		Engine	*_engine;
		std::unordered_map<std::string, std::shared_ptr<Texture>>	_textures;
};
