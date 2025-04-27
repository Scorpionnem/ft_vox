/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:27:54 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 14:19:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"
#include "Mesh.hpp"
#include <array>
#include "Utils.hpp"

enum class ChunkState {
    Unloaded,
    Generating,
    Generated,
    Meshing,
    Ready
};

#define FASTNOISE_LITE_USE_STATIC
#include "FastNoiseLite.h"

class Chunk
{
	public:
		Chunk()
		{
			_coords = glm::vec3(0, 0, 0);
		}
		Chunk(glm::vec3 coords);
		bool getBlock(int x, int y, int z)
		{
			return (chunkData[convertIndex(x, y, z)]);
		}
		void setBlock(int x, int y, int z, bool block)
		{
			chunkData[convertIndex(x, y, z)] = block;
			calcCulling();
		}
		void	draw()
		{
			mesh.draw();
		}
		void	gen()
		{
			for (int x = 0; x < 16; ++x) {
				for (int z = 0; z < 16; ++z) {
					int worldX = _coords.x * 16 + x;
					int worldZ = _coords.z * 16 + z;
		
					// Compute the world height at (worldX, worldZ)
					float heightValue = std::sin(worldX * 0.08f) + std::sin(worldZ * 0.08f);
					int terrainHeight = static_cast<int>(((heightValue + 2.0f) / 4.0f) * 20.0f); // now mapped 0-255
		
					// Calculate this chunk's vertical bounds
					int chunkYStart = _coords.y * 16;
		
					for (int y = 0; y < 16; ++y) {
						int worldY = chunkYStart + y;
		
						if (worldY <= terrainHeight) {
							setBlock(x, y, z, true); // or Dirt/Stone depending
						}
					}
				}
			}
		}
		void	calcCulling();
		bool	hasSolidBlock(int x, int y, int z);
	// private:
		std::vector<bool>	chunkData;
		glm::vec3			_coords;
		Mesh				mesh;
};
