/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:29:51 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 14:50:20 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include <unordered_map>

// struct	ChunkCoordHash
// {
//     std::size_t operator()(const glm::vec3& coord) const
// 	{
//         std::size_t h1 = std::hash<int>()(coord.x);
//         std::size_t h2 = std::hash<int>()(coord.y);
//         std::size_t h3 = std::hash<int>()(coord.z);
//         return h1 ^ (h2 << 1) ^ (h3 << 2);
//     }
// };

// extern unsigned int shadercaca;

class World
{
	public:
		World()
		{
			for (int x = 0; x < 16; x++)
				for (int y = 0; y < 16; y++)
					for (int z = 0; z < 16; z++)
						worldData[convertIndex(x, y, z)] = Chunk(glm::vec3(x , y , z));
		}
		Chunk &getChunk(int x, int y, int z)
		{
			return (worldData[convertIndex(x, y, z)]);
		}
		void setChunk(int x, int y, int z, Block block)
		{
			block._coords.x = x;
			block._coords.y = y;
			block._coords.z = z;
			worldData[convertIndex(x / 16, y / 16, z / 16)].setBlock(x % 16, y % 16, z % 16, block);
		}
		void	draw()
		{
			for (int i = 0; i < 4096; i++)
				worldData[i].draw();
		}
	// private:
		std::array<Chunk, 4096>	worldData;
};
