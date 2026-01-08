/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:52:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 19:58:08 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chunk.hpp"
#include "World.hpp"

BlockStateId	Chunk::getGenerationBlock(Vec3i pos)
{
	Vec3i	wp = worldPos(pos);

	if (wp.y < getGenerationHeight(Vec2i(wp.x, wp.z)))
		return (Blocks::STONE);
	return (Blocks::AIR);
}

void	Chunk::generateTerrain()
{
	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			Vec3i	wp = worldPos(Vec3i(x, 0, z));

			int	terrainHeight = getGenerationHeight(Vec2i(wp.x, wp.z));

			if (wp.y > terrainHeight)
				continue ;

			for (int y = CHUNK_SIZE; y >= 0; y--)
			{
				if (worldPos(Vec3i(x, y, z)).y > terrainHeight)
					continue ;

				Vec3i	pos = Vec3i(x, y, z);
				setBlock(pos, getGenerationBlock(pos));
			}
		}
}

bool	Chunk::isBlockSolid(Vec3i pos)
{
	BlockStateId	id = getBlock(pos);

	return (_world->isBlockStateSolid(id));
}

void	Chunk::genMesh(MeshCache &meshCache)
{
	_mesh = meshCache.gen();

	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int y = 0; y < CHUNK_SIZE; y++)
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if (isBlockSolid(Vec3i(x, y, z)))
				{
					if (!isBlockSolid(Vec3i(x, y + 1, z)))
						Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::TOP);
					if (!isBlockSolid(Vec3i(x, y - 1, z)))
						Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::BOTTOM);
					if (!isBlockSolid(Vec3i(x + 1, y, z)))
						Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::EAST);
					if (!isBlockSolid(Vec3i(x - 1, y, z)))
						Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::WEST);
					if (!isBlockSolid(Vec3i(x, y, z + 1)))
						Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::NORTH);
					if (!isBlockSolid(Vec3i(x, y, z - 1)))
						Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::SOUTH);
				}
			}
	_meshed = true;
}
