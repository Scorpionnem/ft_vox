/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshCache.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:02:02 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 14:03:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unordered_map>
#include <memory>
#include "Mesh.hpp"
#include <mutex>

class	Engine;

class	MeshCache
{
	public:
		MeshCache(Engine *engine) : _engine(engine) {}
		~MeshCache() {}

		std::shared_ptr<Mesh>	get(const std::string &path);
		std::shared_ptr<Mesh>	gen();
	private:
		Engine	*_engine;
		std::vector<std::shared_ptr<Mesh>>						_meshes;
		std::unordered_map<std::string, std::shared_ptr<Mesh>>	_namedMeshes;
		std::mutex												_mutex;
};
