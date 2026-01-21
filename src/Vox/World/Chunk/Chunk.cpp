/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:52:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/21 17:48:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chunk.hpp"
#include "World.hpp"

void	Chunk::generate()
{
	_blocks.resize(CHUNK_VOLUME);

	generateTerrain();
	_generated = true;
}

#include "Chrono.hpp"

void	Chunk::generateTerrain()
{
	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
			for (int y = CHUNK_SIZE; y >= 0; y--)
			{
				localVec3i	pos(x, y, z);
				
				setBlock(pos, getGenerationBlock(getWorldPos(pos)));
			}
}

BlockStateId	Chunk::getGenerationShape(worldVec3i pos, int genHeight)
{	
	if (pos.y <= genHeight)
	{
		int	depth = genHeight - pos.y;

		float	tunnelsIntensity = 1 - smoothstep(0.0, 300, depth);
		tunnelsIntensity = std::clamp(tunnelsIntensity, 0.0f, 0.75f);
		if (Noise::calcNoise(pos, 0.015, 1, 3) * tunnelsIntensity > 0.25)
			return (Blocks::AIR);

		float	intensity = smoothstep(0.0, 100, depth);
		if ((Noise::calcNoise(pos, 0.01, 1, 4) * intensity) > 0.2)
			return (Blocks::AIR);

		return (Blocks::STONE);
	}
	if (pos.y < WATERLEVEL)
		return (Blocks::WATER);
	return (Blocks::AIR);
}

BlockStateId	Chunk::getGenerationDecoration(worldVec3i pos, int genHeight, BlockStateId cur)
{
	if (pos.y <= genHeight && cur != Blocks::AIR)
	{
		int		depth = genHeight - pos.y;

		if (pos.y == genHeight && pos.y == WATERLEVEL - 1) // Return biome's water level block (for rivers sand)
			return (Blocks::SAND);
		if (pos.y == genHeight && pos.y < WATERLEVEL)
			return (Blocks::SAND); // Return biome's top underwater block
		if (depth <= 3 && pos.y < WATERLEVEL)
			return (Blocks::SAND);
			
		if (pos.y == genHeight)
			return (Blocks::GRASS); // Return top biome's top decoration block
		if (depth <= 3)
			return (Blocks::DIRT);

		bool	isSurface = cur == Blocks::STONE && getGenerationShape(Vec3i(pos.x, pos.y + 1, pos.z), genHeight) == Blocks::AIR;

		if (isSurface)
			return (Blocks::STONE); // Return cave/sky biome's top decoration block
	}

	return (Blocks::NO_BLOCK);
}

BlockStateId	Chunk::getGenerationFeatures(worldVec3i pos, BlockStateId cur)
{
	(void)pos;(void)cur;
	// if ((int)(Noise::White(Vec3i(pos.x, pos.y, pos.z)) * 100.0) == 1)
	// 	if (getGenerationBlock(Vec3i(pos.x, pos.y - 1, pos.z)) == Blocks::GRASS)
	// 		return (Blocks::OAK_LOG);

	// if ((int)(Noise::White(Vec3i(pos.x, pos.y, pos.z)) * 100.0) == 1)
	// 	if (cur == Blocks::AIR && getGenerationBlock(Vec3i(pos.x, pos.y - 1, pos.z)) == Blocks::STONE)
	// 		return (Blocks::SAND);

	return (Blocks::NO_BLOCK);
}

BlockStateId	Chunk::getGenerationBlock(worldVec3i pos)
{
	int	genHeight = getGenerationHeight(Vec2i(pos.x, pos.z));

	BlockStateId	res = getGenerationShape(pos, genHeight);

	BlockStateId	decoration = Blocks::NO_BLOCK;
	if (res != Blocks::AIR)
		decoration = getGenerationDecoration(pos, genHeight, res);
	if (decoration != Blocks::NO_BLOCK)
		res = decoration;

	BlockStateId	feature = Blocks::NO_BLOCK;

	if (res == Blocks::AIR)
		feature = getGenerationFeatures(pos, res);
	if (feature != Blocks::NO_BLOCK)
		res = feature;
	return (res);
}

int	Chunk::getGenerationHeight(worldVec2i pos)
{
	return (_world->getWgen().getSplineValue("continentalness", pos) + _world->getWgen().getSplineValue("riverness", pos) + _world->getWgen().getSplineValue("erosion", pos) + _world->getWgen().getSplineValue("mountainness", pos));
}

BlockStateId	Chunk::getBlock(localVec3i pos)
{
	std::unique_lock<std::mutex> lock(_mutex);
	
	if (!isInBounds(pos))
		return (Blocks::AIR);
	int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;
	return (_blocks[index]);
}

bool	Chunk::setBlock(localVec3i pos, BlockStateId block)
{
	if (block == Blocks::NO_BLOCK || !isInBounds(pos))
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
	BlockStateId	id = _world->getBlock(getWorldPos(pos));

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
				BlockStateId	block = _world->getBlock(getWorldPos(Vec3i(x, y, z)));
				bool	solid = isBlockSolid(Vec3i(x, y, z));
				std::shared_ptr<Mesh>	mesh = solid ? _mesh : _transparentMesh;
				int	textureId = _world->getBlockState(block)->getParent()->textureId();

				if (block != Blocks::AIR)
				{
					if (!isBlockSolid(Vec3i(x, y + 1, z)) && _world->getBlock(getWorldPos(Vec3i(x, y + 1, z))) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::TOP, textureId);
					if (!isBlockSolid(Vec3i(x, y - 1, z)) && _world->getBlock(getWorldPos(Vec3i(x, y - 1, z))) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::BOTTOM, textureId);
					if (!isBlockSolid(Vec3i(x + 1, y, z)) && _world->getBlock(getWorldPos(Vec3i(x + 1, y, z))) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::EAST, textureId);
					if (!isBlockSolid(Vec3i(x - 1, y, z)) && _world->getBlock(getWorldPos(Vec3i(x - 1, y, z))) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::WEST, textureId);
					if (!isBlockSolid(Vec3i(x, y, z + 1)) && _world->getBlock(getWorldPos(Vec3i(x, y, z + 1))) != block)
						Cube::addFace(mesh, Vec3i(x, y, z), Cube::Direction::NORTH, textureId);
					if (!isBlockSolid(Vec3i(x, y, z - 1)) && _world->getBlock(getWorldPos(Vec3i(x, y, z - 1))) != block)
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
	shader->setFloat("uSpawnFade", _spawnFade / MAX_SPAWN_FADE);
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
	return (false);
}
