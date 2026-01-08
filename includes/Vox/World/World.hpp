/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:52 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 21:39:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Chunk.hpp"
#include "Camera.hpp"
#include <unordered_map>
#include <memory>
#include <ChunkGenerator.hpp>
#include <BlockType.hpp>

#define HORIZONTAL_RENDER_DISTANCE 8
#define VERTICAL_RENDER_DISTANCE 4

struct Blocks
{
	static BlockStateId	AIR;
	static BlockStateId	STONE;
	static BlockStateId	DIRT;
	static BlockStateId	GRASS;
};

class World
{
	private:
		void	_setBlocksDefines()
		{
			Blocks::AIR = getDefaultStateId("air");
			Blocks::STONE = getDefaultStateId("stone");
			Blocks::DIRT = getDefaultStateId("dirt");
			Blocks::GRASS = getDefaultStateId("grass");
		}
	public:
		World(MeshCache &cache) : _generator(cache)
		{
			_registerBlock("air", 0, {}, false);
			_registerBlock("stone", 0, {}, true);
			_registerBlock("dirt", 1, {}, true);
			_registerBlock("grass", 3, {}, true);

			_computeBlockStates();

			uint32_t	threadCount = std::thread::hardware_concurrency() / 2;

			std::cout << "Starting " << threadCount << " generation thread" << std::endl;

			_generator.start(threadCount);
		}
		~World()
		{
			_generator.stop();
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
			return (getBlockType(id)->getDefault()->id());
		}

		void					update(Camera &camera);

		std::shared_ptr<Chunk>	getChunk(Vec3i pos);
		void					genChunk(Vec3i pos);

		std::vector<std::shared_ptr<Chunk>>	&getLoadedChunks() {return (_loadedChunks);}
		std::vector<std::shared_ptr<Chunk>>	&getVisibleChunks() {return (_visibleChunks);}
		int	getHorizontalRenderDistance() {return (_horizontalRenderDistance);}
		int	getVerticalRenderDistance() {return (_verticalRenderDistance);}
		int	getMaxLoadedChunks() {return ((_horizontalRenderDistance * 2) * (_horizontalRenderDistance * 2) * (_verticalRenderDistance * 2));}
	private:
		void	_computeBlockStates()
		{
			for (auto pair : _blockTypes)
			{
				std::shared_ptr<BlockType>	bt = pair.second;
				std::unordered_map<BlockStateHash, std::shared_ptr<BlockState>>	&bss = bt->getBlockStates();

				for (auto pairr : bss)
				{
					std::shared_ptr<BlockState> bs = pairr.second;

					_blockStates.insert(std::make_pair(bs->id(), bs));
				}
			}

			_blockStateSolid.resize(_blockStates.size());

			for (auto pair : _blockStates)
			{
				_blockStateSolid[pair.first] = pair.second->parent->isSolid();
			}

			_setBlocksDefines();
		}
		void	_registerBlock(const std::string &id, int textureId, std::vector<Property> properties, bool solid)
		{
			_blockTypes.insert(std::make_pair(id, std::make_shared<BlockType>(id, textureId, properties, solid)));
		}
		int	_horizontalRenderDistance = HORIZONTAL_RENDER_DISTANCE;
		int	_verticalRenderDistance = VERTICAL_RENDER_DISTANCE;
		ChunkGenerator	_generator;

		std::unordered_map<std::string, std::shared_ptr<BlockType>>		_blockTypes;
		std::unordered_map<BlockStateId, std::shared_ptr<BlockState>>	_blockStates;
		std::vector<bool>												_blockStateSolid;

		std::unordered_map<uint64_t, std::shared_ptr<Chunk>>	_chunks;
		std::vector<std::shared_ptr<Chunk>>						_loadedChunks;
		std::vector<std::shared_ptr<Chunk>>						_visibleChunks;
};
