/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   World.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:01:26 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 19:57:44 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "World.hpp"
#include "Camera.hpp"

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

BlockStateId	Blocks::AIR;
BlockStateId	Blocks::STONE;

void	World::update(Camera &camera)
{

	if (ImGui::Begin("Render Distance", (bool *)__null))
	{
		ImGui::InputInt("Horizontal", &_horizontalRenderDistance);
		ImGui::InputInt("Vertical", &_verticalRenderDistance);
		if (_horizontalRenderDistance < 1)
			_horizontalRenderDistance = 1;
		if (_verticalRenderDistance < 1)
			_verticalRenderDistance = 1;
	}
	ImGui::End();

	Vec3	camChunkPos;
	camChunkPos.x = (int)(camera.pos.x / CHUNK_SIZE);
	camChunkPos.y = (int)(camera.pos.y / CHUNK_SIZE);
	camChunkPos.z = (int)(camera.pos.z / CHUNK_SIZE);

	int	startX = camChunkPos.x + (_horizontalRenderDistance - 1);
	int	startZ = camChunkPos.z + (_horizontalRenderDistance - 1);
	int	startY = camChunkPos.y + (_verticalRenderDistance - 1);
	int	endX = camChunkPos.x - _horizontalRenderDistance;
	int	endZ = camChunkPos.z - _horizontalRenderDistance;
	int	endY = camChunkPos.y - _verticalRenderDistance;

	_loadedChunks.clear();
	_visibleChunks.clear();
	for (int y = startY; y >= endY; y--)
		for (int x = startX; x >= endX; x--)
			for (int z = startZ; z >= endZ; z--)
			{
				std::shared_ptr<Chunk> chunk = getChunk(Vec3i(x, y, z));
				if (!chunk)
				{
					genChunk(Vec3i(x, y, z));
					continue ;
				}
				if (!chunk->_meshed)
					continue ;
				_loadedChunks.push_back(chunk);
				if (camera.frustum.isInside(Vec3(chunk->_pos * Vec3i(CHUNK_SIZE)) - camera.pos, Vec3(chunk->_pos * Vec3i(CHUNK_SIZE) + Vec3i(CHUNK_SIZE)) - camera.pos))
					_visibleChunks.push_back(chunk);
			}
}

std::shared_ptr<Chunk>	World::getChunk(Vec3i pos)
{
	auto find = _chunks.find(pos.hash());

	if (find == _chunks.end())
		return (nullptr);
	return (find->second);
}

void	World::genChunk(Vec3i pos)
{
	std::shared_ptr<Chunk>	chunk = std::make_shared<Chunk>(pos, this);

	_generator.gen(chunk);
	_chunks.insert(std::make_pair(pos.hash(), chunk));
}
