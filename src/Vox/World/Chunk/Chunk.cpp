/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:52:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/09 20:14:53 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chunk.hpp"
#include "World.hpp"

int	Chunk::getGenerationHeight(Vec2i pos)
{
	return (_world->wgen.getNoise("continentalness", pos) + _world->wgen.getNoise("peaks_valleys", pos) + _world->wgen.getNoise("erosion", pos) + _world->wgen.getNoise("mountainness", pos));
}

BlockStateId	Chunk::getGenerationBlock(Vec3i pos)
{
	Vec3i	wp = worldPos(pos);

	int	genHeight = getGenerationHeight(Vec2i(wp.x, wp.z));
	if (wp.y <= genHeight)
	{
		if (wp.y == genHeight)
		{
			if (wp.y <= WATERLEVEL)
				return (Blocks::SAND);
			return (Blocks::GRASS);
		}
		if (wp.y >= genHeight - 2)
			return (Blocks::DIRT);
		return (Blocks::STONE);
	}
	if (wp.y < WATERLEVEL)
		return (Blocks::WATER);
	return (Blocks::AIR);
}

void	Chunk::generateTerrain()
{
	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			Vec3i	wp = worldPos(Vec3i(x, 0, z));

			int	terrainHeight = getGenerationHeight(Vec2i(wp.x, wp.z));

			if (wp.y > std::max(terrainHeight, WATERLEVEL))
				continue ;

			for (int y = CHUNK_SIZE; y >= 0; y--)
			{
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
	_transparentMesh = meshCache.gen();

	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int y = 0; y < CHUNK_SIZE; y++)
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				BlockStateId	block = getBlock(Vec3i(x, y, z));
				bool	solid = isBlockSolid(Vec3i(x, y, z));
				std::shared_ptr<Mesh>	mesh = solid ? _mesh : _transparentMesh;
				int	textureId = _world->getBlockState(block)->parent->textureId();

				if (block != Blocks::AIR)
				{
					if (!isBlockSolid(Vec3i(x, y + 1, z)) && getBlock(Vec3i(x, y + 1, z)) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::TOP, textureId);
					if (!isBlockSolid(Vec3i(x, y - 1, z)) && getBlock(Vec3i(x, y - 1, z)) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::BOTTOM, textureId);
					if (!isBlockSolid(Vec3i(x + 1, y, z)) && getBlock(Vec3i(x + 1, y, z)) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::EAST, textureId);
					if (!isBlockSolid(Vec3i(x - 1, y, z)) && getBlock(Vec3i(x - 1, y, z)) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::WEST, textureId);
					if (!isBlockSolid(Vec3i(x, y, z + 1)) && getBlock(Vec3i(x, y, z + 1)) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::NORTH, textureId);
					if (!isBlockSolid(Vec3i(x, y, z - 1)) && getBlock(Vec3i(x, y, z - 1)) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::SOUTH, textureId);
				}
			}
	_meshed = true;
}
