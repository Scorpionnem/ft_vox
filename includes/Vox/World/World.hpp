/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:52 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/07 17:26:27 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Chunk.hpp"
#include "Camera.hpp"
#include <unordered_map>
#include <memory>
#include <ChunkGenerator.hpp>

#define HORIZONTAL_RENDER_DISTANCE 8
#define VERTICAL_RENDER_DISTANCE 4

class World
{
	public:
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

		void					update(Camera &camera);
		
		std::shared_ptr<Chunk>	getChunk(Vec3i pos);
		void					genChunk(Vec3i pos);
		
		std::vector<std::shared_ptr<Chunk>>	&getLoadedChunks() {return (_loadedChunks);}
		std::vector<std::shared_ptr<Chunk>>	&getVisibleChunks() {return (_visibleChunks);}
		int	getHorizontalRenderDistance() {return (_horizontalRenderDistance);}
		int	getVerticalRenderDistance() {return (_verticalRenderDistance);}
	private:
		int	_horizontalRenderDistance = HORIZONTAL_RENDER_DISTANCE;
		int	_verticalRenderDistance = VERTICAL_RENDER_DISTANCE;
		ChunkGenerator	_generator;

		std::unordered_map<uint64_t, std::shared_ptr<Chunk>>	_chunks;
		std::vector<std::shared_ptr<Chunk>>						_loadedChunks;
		std::vector<std::shared_ptr<Chunk>>						_visibleChunks;
};
