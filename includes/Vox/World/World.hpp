/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:52 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/17 16:07:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Chunk.hpp"
#include "Camera.hpp"
#include <unordered_map>
#include <memory>
#include <ChunkGenerator.hpp>
#include <WorldGenerator.hpp>
#include <BlockType.hpp>

#define HORIZONTAL_RENDER_DISTANCE 8
#define VERTICAL_RENDER_DISTANCE 4

#include <BoostedGenerator.hpp>

struct Blocks
{
	static BlockStateId	NO_BLOCK;

	static BlockStateId	AIR;
	static BlockStateId	STONE;
	static BlockStateId	DIRT;
	static BlockStateId	GRASS;
	static BlockStateId	SAND;
	static BlockStateId	WATER;
	static BlockStateId	OAK_LOG;
};

class World
{
	private:
		void	_setBlocksDefines()
		{
			Blocks::NO_BLOCK = BlockState::getGlobalId() + 1;

			Blocks::AIR = getDefaultStateId("air");
			Blocks::STONE = getDefaultStateId("stone");
			Blocks::DIRT = getDefaultStateId("dirt");
			Blocks::GRASS = getDefaultStateId("grass");
			Blocks::SAND = getDefaultStateId("sand");
			Blocks::WATER = getDefaultStateId("water");
			Blocks::OAK_LOG = getDefaultStateId("oak_log");
		}

		void	_imGui();
	public:
		World(MeshCache &cache, std::shared_ptr<Shader> computeShader) : _generator(cache)
		{
			_wgen.load();

			_registerBlock("air", 0, {}, false);
			_registerBlock("stone", 0, {}, true);
			_registerBlock("dirt", 1, {}, true);
			_registerBlock("grass", 3, {}, true);
			_registerBlock("sand", 4, {}, true);
			_registerBlock("water", 9, {}, false);
			_registerBlock("oak_log", 6, {}, true);

			_computeBlockStates();

			uint32_t	threadCount = std::thread::hardware_concurrency() - 1;

			std::cout << "Starting " << threadCount << " generation thread" << std::endl;

			_generator.start(threadCount);
			_boostedGenerator.init(computeShader);
			_boostedGenerator.dispatch({});
		}
		~World()
		{
			_generator.stop();
		}

		void	reload()
		{
			_wgen.reload();
			_chunks.clear();
		}

		void					update(float delta, Camera &camera);

		std::shared_ptr<Chunk>	getChunk(chunkVec3i pos);
		void					genChunk(chunkVec3i pos);

		BlockStateId	getBlock(worldVec3i pos)
		{
			std::shared_ptr<Chunk>	chunk = getChunk(pos / CHUNK_SIZE);

			if (!chunk || !chunk->isMeshed())
				return (Blocks::AIR);
			return (chunk->getBlock(chunk->getLocalPos(pos)));
		}
		bool	setBlock(worldVec3i pos, BlockStateId block)
		{
			std::shared_ptr<Chunk>	chunk = getChunk(pos / CHUNK_SIZE);

			if (!chunk || !chunk->isMeshed())
				return (false);
			chunk->setBlock(chunk->getLocalPos(pos), block);
			return (true);
		}

		std::shared_ptr<BlockType>	getBlockType(const std::string &id)
		{
			return (_blockTypes[id]);
		}
		std::shared_ptr<BlockState>	getBlockState(BlockStateId id)
		{
			return (_blockStates[id]);
		}
		bool	isBlockStateSolid(BlockStateId id)
		{
			return (_blockStateSolid[id]);
		}
		BlockStateId getDefaultStateId(const std::string &id)
		{
			return (getBlockType(id)->getDefaultState()->id());
		}

		const std::vector<std::shared_ptr<Chunk>>					&getLoadedChunks() {return (_loadedChunks);}
		const std::vector<std::shared_ptr<Chunk>>					&getVisibleChunks() {return (_visibleChunks);}
		const std::unordered_map<uint64_t, std::shared_ptr<Chunk>>	&getAllChunks() {return (_chunks);}

		int	getHorizontalRenderDistance() {return (_horizontalRenderDistance);}
		int	getVerticalRenderDistance() {return (_verticalRenderDistance);}
		int	getMaxLoadedChunks() {return ((_horizontalRenderDistance * 2) * (_horizontalRenderDistance * 2) * (_verticalRenderDistance * 2));}

		static chunkVec3i	getChunkPos(worldVec3i pos) {return (pos / CHUNK_SIZE);}

		const WorldGenerator	&getWgen() {return (_wgen);}
	private:
		void	_updateGenerator(Vec3 camPos);
		void	_computeBlockStates();
		void	_registerBlock(const std::string &id, int textureId, std::vector<BlockProperty> properties, bool solid)
		{
			_blockTypes.insert(std::make_pair(id, std::make_shared<BlockType>(id, textureId, properties, solid)));
		}
		int	_horizontalRenderDistance = HORIZONTAL_RENDER_DISTANCE;
		int	_verticalRenderDistance = VERTICAL_RENDER_DISTANCE;
		ChunkGenerator	_generator;
		BoostedGenerator	_boostedGenerator;

		chunkVec3i	_lastCamPos = Vec3i(42);

		std::unordered_map<std::string, std::shared_ptr<BlockType>>		_blockTypes;
		std::unordered_map<BlockStateId, std::shared_ptr<BlockState>>	_blockStates;
		std::vector<bool>												_blockStateSolid;

		std::unordered_map<uint64_t, std::shared_ptr<Chunk>>	_chunks;
		std::vector<std::shared_ptr<Chunk>>						_loadedChunks;
		std::vector<std::shared_ptr<Chunk>>						_visibleChunks;
		std::vector<std::shared_ptr<Chunk>>						_chunksGenQueue;

		WorldGenerator											_wgen;
};
