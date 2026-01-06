/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderCache.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:06:14 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 12:11:52 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"

std::shared_ptr<Shader>	ShaderCache::get(const std::string &path)
{
	auto	[it, inserted] = _shaders.try_emplace(path);

	if (inserted)
	{
		it->second = std::make_shared<Shader>();
		it->second->load(GL_VERTEX_SHADER , path + ".vs");
		it->second->load(GL_FRAGMENT_SHADER , path + ".fs");
		it->second->link();
	}

	return (it->second);
}
