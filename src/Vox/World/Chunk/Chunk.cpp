/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:52:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/11 15:48:46 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chunk.hpp"
#include "World.hpp"

void	Chunk::generate()
{
	_blocks.resize(CHUNK_VOLUME);

	generateTerrain();
	generateFeatures();
	_generated = true;
}

void	Chunk::generateTerrain()
{
	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			worldVec3i	wp = getWorldPos(Vec3i(x, 0, z));

			int	terrainHeight = getGenerationHeight(worldVec2i(wp.x, wp.z));

			if (wp.y > std::max(terrainHeight, WATERLEVEL))
				continue ;

			for (int y = CHUNK_SIZE; y >= 0; y--)
			{
				localVec3i	pos(x, y, z);
				setBlock(pos, getGenerationBlock(getWorldPos(pos)));
			}
		}
}

void	Chunk::generateFeatures()
{

}

BlockStateId	Chunk::getGenerationBlock(worldVec3i pos)
{
	int	genHeight = getGenerationHeight(Vec2i(pos.x, pos.z));
	if (pos.y <= genHeight)
	{
		if (pos.y == genHeight)
		{
			if (pos.y <= WATERLEVEL)
				return (Blocks::SAND);
			return (Blocks::GRASS);
		}
		if (pos.y >= genHeight - 2)
			return (Blocks::DIRT);
		return (Blocks::STONE);
	}
	if (pos.y < WATERLEVEL)
		return (Blocks::WATER);
	return (Blocks::AIR);
}

int	Chunk::getGenerationHeight(worldVec2i pos)
{
	return (_world->wgen.getSplineValue("continentalness", pos) + _world->wgen.getSplineValue("riverness", pos) + _world->wgen.getSplineValue("erosion", pos) + _world->wgen.getSplineValue("mountainness", pos));
}

BlockStateId	Chunk::getBlock(localVec3i pos)
{
	if (!isInBounds(pos))
		return (getGenerationBlock(getWorldPos(pos)));
	int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;
	return (_blocks[index]);
}

bool	Chunk::setBlock(localVec3i pos, BlockStateId block)
{
	if (!isInBounds(pos))
		return (false);
	int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;
	_blocks[index] = block;
	return (true);
}

bool	Chunk::isInBounds(localVec3i pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE)
		return (false);
	return (true);
}

bool	Chunk::isBlockSolid(localVec3i pos)
{
	BlockStateId	id = getBlock(pos);

	return (_world->isBlockStateSolid(id));
}

void	Chunk::mesh(MeshCache &meshCache)
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

void	Chunk::remesh(MeshCache &meshCache)
{
	_uploaded = false;
	mesh(meshCache);
}

void	Chunk::draw(std::shared_ptr<Shader> shader)
{
	_mesh->draw(shader);
	_transparentMesh->draw(shader);
}

bool	Chunk::upload()
{
	if (!_uploaded)
	{
		_mesh->upload();
		_transparentMesh->upload();
		_uploaded = true;
		return (true);
	}
	_uploaded = true;
	return (false);
}
