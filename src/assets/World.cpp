/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:28:19 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/01 10:56:37 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "World.hpp"

World	world;

Chunk	*World::getChunk(glm::vec3 targetPos)
{
	std::unordered_map<std::string, Chunk>::iterator	finder;
	finder = this->worldData.find(format_coords(targetPos));
	if (finder != this->worldData.end())
		return (&finder->second);
	else
		return (NULL);
}

void	World::addChunk(glm::vec3 targetPos)
{
	if (targetPos.x < 0 || targetPos.y < 0 || targetPos.z < 0 || targetPos.y > 15)
		return ;
	this->worldData.insert(std::make_pair(format_coords(targetPos), Chunk(targetPos)));
}

void	World::drawChunks(glm::vec3 playerPos, int radius)
{
	int playerChunkX = (int)playerPos.x / 16;
	int playerChunkY = (int)playerPos.y / 16;
	int playerChunkZ = (int)playerPos.z / 16;

	for (int dx = -radius; dx <= radius; ++dx) {
		for (int dy = -radius; dy <= radius; ++dy) {
			for (int dz = -radius; dz <= radius; ++dz) {
				// Distance 3D au centre
				float distance = sqrt(dx * dx + dy * dy + dz * dz);
				if (distance <= radius) {
					int chunkX = (playerChunkX + dx);
					int chunkY = (playerChunkY + dy);
					int chunkZ = (playerChunkZ + dz);

					if (chunkX < 0 || chunkY < 0 || chunkZ < 0 || chunkY > 15)
						continue ;
					Chunk	*tmp;
					tmp = getChunk(glm::vec3(chunkX, chunkY, chunkZ));
					if (tmp)
						tmp->draw();
					else
					{
						addChunk(glm::vec3(chunkX, chunkY, chunkZ));
						world.getChunk(glm::vec3(chunkX, chunkY, chunkZ))->gen();
						world.getChunk(glm::vec3(chunkX, chunkY, chunkZ))->calcCulling();
					}
				}
			}
		}
	}
}

void	World::setBlock(int x, int y, int z, bool state)
{
	Chunk	*tmp = getChunk(glm::vec3(x / 16, y / 16, z / 16));
	if (tmp)
		tmp->setBlock(x % 16, y % 16, z % 16, state);
}

bool	World::getBlock(int x, int y, int z)
{
	if (x < 0 || y < 0 || z < 0)
		return (false);
	Chunk	*tmp = getChunk(glm::vec3(x / 16, y / 16, z / 16));
	if (tmp)
		return (tmp->getBlock(x % 16, y % 16, z % 16));
	return (false);
}
