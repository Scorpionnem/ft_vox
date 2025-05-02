/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:29:51 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 20:17:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include "Chunk.hpp"
#include <unordered_map>

class	World
{
	public:
		World(){}
		void	setBlock(int x, int y, int z, bool state);
		bool	getBlock(int x, int y, int z);
		Chunk	*getChunk(glm::vec3 targetPos);
		void	addChunk(glm::vec3 targetPos);
		void	drawChunks(glm::vec3 playerPos, int radius);

	std::unordered_map<std::string, Chunk> worldData;
};

extern World world;
