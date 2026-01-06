/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:52 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/06 15:39:30 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Chunk.hpp"
#include <unordered_map>
#include <memory>
#include <ChunkGenerator.hpp>

#define RENDER_DISTANCE 5

struct World
{
	World(MeshCache &cache) : _generator(cache)
	{
		uint32_t	threadCount = std::thread::hardware_concurrency() / 2;

		std::cout << "Starting " << threadCount << " generation thread" << std::endl;

		_generator.start(threadCount);
	}
	~World()
	{
		_generator.stop();
	}
	ChunkGenerator	_generator;

	void	update(Camera &camera)
	{
		Vec3	camChunkPos = Vec3((int)(camera.pos.x / CHUNK_SIZE), (int)(camera.pos.y / CHUNK_SIZE), (int)(camera.pos.z / CHUNK_SIZE));

		int	startX = camChunkPos.x + RENDER_DISTANCE;
		int	startZ = camChunkPos.z + RENDER_DISTANCE;
		int	startY = camChunkPos.y + RENDER_DISTANCE;
		int	endX = camChunkPos.x - RENDER_DISTANCE;
		int	endZ = camChunkPos.z - RENDER_DISTANCE;
		int	endY = camChunkPos.y - RENDER_DISTANCE;

		_loadedChunks.clear();
		_visibleChunks.clear();
		for (int y = startY; y >= endY; y--)
			for (int x = startX; x >= endX; x--)
				for (int z = startZ; z >= endZ; z--)
				{
					std::shared_ptr<Chunk> chunk = getChunk(Vec3i(x, y, z));
					if (!chunk)
					{
						genChunk(Vec3i(x, y, z));
						continue ;
					}
					if (!chunk->_meshed)
						continue ;
					_loadedChunks.push_back(chunk);
					if (camera.frustum.isInside((chunk->_pos * Vec3i(CHUNK_SIZE)) + (CHUNK_SIZE / 2)))
						_visibleChunks.push_back(chunk);
				}
	}
	std::vector<std::shared_ptr<Chunk>>	&getLoadedChunks() {return (_loadedChunks);}
	std::vector<std::shared_ptr<Chunk>>	&getVisibleChunks() {return (_visibleChunks);}
	std::shared_ptr<Chunk>	getChunk(Vec3i pos)
	{
		auto find = _chunks.find(pos.hash());

		if (find == _chunks.end())
			return (nullptr);
		return (find->second);
	}
	void	genChunk(Vec3i pos)
	{
		std::shared_ptr<Chunk>	chunk = std::make_shared<Chunk>(pos);

		_generator.gen(chunk);
		_chunks.insert(std::make_pair(pos.hash(), chunk));
	}
	std::unordered_map<uint64_t, std::shared_ptr<Chunk>>	_chunks;
	std::vector<std::shared_ptr<Chunk>>						_loadedChunks;
	std::vector<std::shared_ptr<Chunk>>						_visibleChunks;
};
