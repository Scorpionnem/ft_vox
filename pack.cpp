/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 01:58:22 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/11 03:32:10 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unordered_map>
#include <Math.hpp>
#include <cstdint>
#include <vector>

#define CHUNK_SIZE 32
using BlockStateId = uint32_t;
using localVec3i = Vec3i;

void	printBits(uint32_t n)
{
	int	i = 31;
	while (i >= 0)
		std::cout << ((n & (1 << i--)) > 0);
	std::cout << std::endl;
}

/*
	c++ pack.cpp src/Math/Math.cpp src/Math/Vec3.cpp src/Math/Vec3d.cpp src/Math/Vec3i.cpp -I includes/Math && ./a.out

	Blocks are stored from right to left (right is 0)

	for example 00000000000000000000000000000001 here the 1 shows that there is a block at Y = 0
*/

class	PackedChunk
{
	public:
		PackedChunk()
		{
			_blocks.resize(CHUNK_SIZE * CHUNK_SIZE);
		}
		~PackedChunk() {}

		void	setBlock(localVec3i pos, BlockStateId id)
		{
			BlockStateId	block = getBlock(pos);
			if (block != 0)
				_clearBlock(pos, block);

			uint32_t	&mask = _getMask(pos, id);

			mask |= 1 << pos.y;
		}
		BlockStateId	getBlock(localVec3i pos)
		{
			for (auto pair : _getSlice(pos))
			{
				uint32_t	&mask = pair.second;

				if (mask >> pos.y & 1)
					return (pair.first);
			}
			return (0);
		}
	private:
		std::vector<std::pair<BlockStateId, uint32_t>>	&_getSlice(localVec3i pos)
		{
			return (_blocks[pos.x + pos.z * CHUNK_SIZE]);
		}
		uint32_t	&_getMask(localVec3i pos, BlockStateId block)
		{
			auto	&slice = _getSlice(pos);
			for (auto &pair : slice)
			{
				if (pair.first == block)
					return (pair.second);
			}
			slice.push_back(std::make_pair(block, 0));
			return (_getMask(pos, block));
		}

		void	_clearBlock(localVec3i pos, BlockStateId sliceId)
		{
			uint32_t	&slice = _getMask(pos, sliceId);

			slice ^= 1 << pos.y;
		}
		std::vector<std::vector<std::pair<BlockStateId, uint32_t>>>	_blocks;
};

int	main(void)
{
	PackedChunk	chunk;

	chunk.setBlock(Vec3i(0, 0, 0), 4);
	chunk.setBlock(Vec3i(0, 0, 0), 1);
	chunk.setBlock(Vec3i(0, 1, 0), 1);
	chunk.setBlock(Vec3i(0, 31, 0), 1);
	std::cout << chunk.getBlock(Vec3i(0, 0, 0)) << std::endl;
	std::cout << chunk.getBlock(Vec3i(0, 2, 0)) << std::endl;
}
