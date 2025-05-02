/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:17:56 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/01 10:56:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include "Chunk.hpp"
#include "Assets.hpp"
#include "World.hpp"

bool	Chunk::hasSolidBlock(int x, int y, int z)
{
	// if (x >= 16 || y >= 16 || z >= 16)
	// 	return (false);
	// if (x < 0 || y < 0 || z < 0)
	// 	return (false);
	// if (this->getBlock(x, y, z) == true)
	// 	return (true);
	// return (false);
	return (world.getBlock(x + (_coords.x * 16), y + (_coords.y * 16), z + (_coords.z * 16)));
}

Chunk::Chunk(glm::vec3 coords)
{
	this->_coords = coords;
	chunkData.insert(chunkData.begin(), 4096, false);
}

void	Chunk::calcCulling()
{
	this->mesh.vertices.clear();
	this->mesh.indices.clear();
	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 16; y++)
			for (int z = 0; z < 16; z++)
			{
				if (this->getBlock(x, y, z) == false)
					continue ;
				if (!hasSolidBlock(x - 1, y, z))
					mesh.addFace(glm::vec3(x, y, z) + _coords * 16.0f, FaceDirection::Left, getAtlasOffset(0, assets.getAtlasMap("grass_side")));
				if (!hasSolidBlock(x + 1, y, z))
					mesh.addFace(glm::vec3(x, y, z) + _coords * 16.0f, FaceDirection::Right, getAtlasOffset(0, assets.getAtlasMap("grass_side")));
				if (!hasSolidBlock(x, y - 1, z))
					mesh.addFace(glm::vec3(x, y, z) + _coords * 16.0f, FaceDirection::Bottom, getAtlasOffset(0, assets.getAtlasMap("dirt")));
				if (!hasSolidBlock(x, y + 1, z))
					mesh.addFace(glm::vec3(x, y, z) + _coords * 16.0f, FaceDirection::Top, getAtlasOffset(0, assets.getAtlasMap("grass_top")));
				if (!hasSolidBlock(x, y, z - 1))
					mesh.addFace(glm::vec3(x, y, z) + _coords * 16.0f, FaceDirection::Back, getAtlasOffset(0, assets.getAtlasMap("grass_side")));
				if (!hasSolidBlock(x, y, z + 1))
					mesh.addFace(glm::vec3(x, y, z) + _coords * 16.0f, FaceDirection::Front, getAtlasOffset(0, assets.getAtlasMap("grass_side")));
			}
	mesh.upload();
}
