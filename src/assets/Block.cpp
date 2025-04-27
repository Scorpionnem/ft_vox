/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:17:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 12:53:08 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include "Block.hpp"
#include "Assets.hpp"

void Block::draw(glm::vec3 chunkCoords)
{
	(void)chunkCoords;
}

glm::vec2	Block::getTexture(FaceDirection	face)
{
	std::string	texture = this->textures.find(face)->second;
	
	return (getAtlasOffset(0, assets.getAtlasMap(texture)));
}