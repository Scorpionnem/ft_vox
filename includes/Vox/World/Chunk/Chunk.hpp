/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/14 18:05:51 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <Math.hpp>
#include <Shader.hpp>
#include <MeshCache.hpp>
#include <atomic>
#include <limits.h>
#include "BlockType.hpp"
#include "Perlin3D.hpp"

#include "BlockModel.hpp"

#define WATERLEVEL 0
#define CHUNK_SIZE 32
#define CHUNK_VOLUME CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE

class	World;

// Position is chunk local space
using localVec3i = Vec3i;
// Position in wold space
using worldVec3i = Vec3i;
// Position in chunk space (1, 1, 1) is (CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE) in world space
using chunkVec3i = Vec3i;

// Position is chunk local space
using localVec2i = Vec2i;
// Position in wold space
using worldVec2i = Vec2i;
// Position in chunk space (1, 1) is (CHUNK_SIZE, CHUNK_SIZE) in world space
using chunkVec2i = Vec2i;

class	Chunk
{
	public:
		Chunk(chunkVec3i pos, World *world) : _pos(pos)
		{
			_world = world;
		}
		~Chunk() {}

		Vec3i	getWorldPos(localVec3i pos)
		{
			return (pos + _pos * CHUNK_SIZE);
		}
		Vec3i	getLocalPos(worldVec3i pos)
		{
			return (pos - _pos * CHUNK_SIZE);
		}

		int				getGenerationHeight(worldVec2i pos);
		BlockStateId	getGenerationBlock(worldVec3i pos);

		void	generateTerrain();
		void	generateFeatures();
		void	generate();

		void	mesh(MeshCache &meshCache);
		void	remesh(MeshCache &meshCache);

		void	update(float delta)
		{
			if (_spawnFade > 0)
			{
				_spawnFade -= delta;
				if (_spawnFade < 0)
					_spawnFade = 0;
			}
		}
		void	draw(std::shared_ptr<Shader> shader);
		bool	upload();

		bool			isBlockSolid(localVec3i pos);
		BlockStateId	getBlock(localVec3i pos);
		bool			setBlock(localVec3i pos, BlockStateId block);
		bool			isInBounds(localVec3i pos);
		
		chunkVec3i	getPos() {return (_pos);}
		bool		isMeshed() {return (_meshed);}
	private:
		std::vector<BlockStateId>	_blocks;
		std::atomic_bool			_generated = false;

		chunkVec3i					_pos;

		bool						_uploaded = false;
		std::atomic_bool			_meshed = false;
		std::shared_ptr<Mesh>		_mesh;
		std::shared_ptr<Mesh>		_transparentMesh;

		World						*_world;
		
		#define MAX_SPAWN_FADE		0.5
		float						_spawnFade = MAX_SPAWN_FADE;
};
