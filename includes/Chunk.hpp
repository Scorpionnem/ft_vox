/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:27:54 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 14:41:48 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include <array>

class Chunk
{
	public:
		Chunk()
		{
			_coords = glm::vec3(0, 0, 0);
		}
		Chunk(glm::vec3 coords)
		{
			for (int x = 0; x < 16; x++)
				for (int y = 0; y < 16; y++)
					for (int z = 0; z < 16; z++)
						chunkData.push_back(Block(glm::vec3(x , y , z), "air", ""));
			this->calcCulling();
			this->_coords = coords; 	
		}
		Block &getBlock(int x, int y, int z)
		{
			return (chunkData[convertIndex(x, y, z)]);
		}
		void setBlock(int x, int y, int z, Block block)
		{
			block._coords.x = x;
			block._coords.y = y;
			block._coords.z = z;
			chunkData[convertIndex(x, y, z)] = block;
			this->calcCulling();
		}
		void	draw()
		{
			for (int i = 0; i < 4096; i++)
				chunkData[i].draw(_coords);
		}
		void	calcCulling();
	// private:
		std::vector<Block>	chunkData;
		glm::vec3			_coords;
};
