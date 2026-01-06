/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshCache.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:02:29 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 14:03:25 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"

std::shared_ptr<Mesh>	MeshCache::gen()
{
	const std::lock_guard<std::mutex>	lock(_mutex);

	std::shared_ptr<Mesh>	mesh = std::make_shared<Mesh>(_engine->getTextureCache());
	_meshes.push_back(mesh);
	return (mesh);
}

std::shared_ptr<Mesh>	MeshCache::get(const std::string &path)
{
	const std::lock_guard<std::mutex>	lock(_mutex);

	auto	[it, inserted] = _namedMeshes.try_emplace(path);

	if (inserted)
	{
		it->second = std::make_shared<Mesh>(_engine->getTextureCache());
		_meshes.push_back(it->second);
		it->second->load(path);
		it->second->upload();
	}

	return (it->second);
}
