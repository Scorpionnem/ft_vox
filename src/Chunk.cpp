/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:17:56 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 14:29:08 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

void	Chunk::calcCulling()
{
	for (int x = 0; x < 16; x++)
		for (int y = 0; y < 16; y++)
			for (int z = 0; z < 16; z++)
			{
				for (int i = 0; i < 6; i++)
					this->getBlock(x, y, z).drawFace[i] = true;
				if (x - 1 >= 0 && this->getBlock(x - 1, y, z)._id != "air")
					this->getBlock(x, y, z).drawFace[2] = false;
				if (x + 1 < 16 && this->getBlock(x + 1, y, z)._id != "air")
					this->getBlock(x, y, z).drawFace[3] = false;
				if (y - 1 >= 0 && this->getBlock(x, y - 1, z)._id != "air")
					this->getBlock(x, y, z).drawFace[4] = false;
				if (y + 1 < 16 && this->getBlock(x, y + 1, z)._id != "air")
					this->getBlock(x, y, z).drawFace[5] = false;
				if (z - 1 >= 0 && this->getBlock(x, y, z - 1)._id != "air")
					this->getBlock(x, y, z).drawFace[0] = false;
				if (z + 1 < 16 && this->getBlock(x, y, z + 1)._id != "air")
					this->getBlock(x, y, z).drawFace[1] = false;
			}
}
