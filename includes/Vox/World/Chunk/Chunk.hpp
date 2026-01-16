/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/16 20:48:04 by mbatty           ###   ########.fr       */
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
#include "Noise.hpp"

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

		int				getGenerationHeight(worldVec2i pos);
		BlockStateId	getGenerationShape(worldVec3i pos);
		BlockStateId	getGenerationDecoration(worldVec3i pos, BlockStateId cur);
		BlockStateId	getGenerationFeatures(worldVec3i pos, BlockStateId cur);
		
		BlockStateId	getGenerationBlock(worldVec3i pos);

		void	generateTerrain();
		void	generate();

		void	draw(std::shared_ptr<Shader> shader);
		bool	upload();

		void	mesh(MeshCache &meshCache);
		void	remesh(MeshCache &meshCache);
		bool	isMeshed() {return (_meshed);}

		void	update(float delta)
		{
			if (_spawnFade > 0)
			{
				_spawnFade -= delta;
				if (_spawnFade < 0)
					_spawnFade = 0;
			}
		}

		BlockStateId	getBlock(localVec3i pos);
		bool			setBlock(localVec3i pos, BlockStateId block);

		bool			isBlockSolid(localVec3i pos);
		bool			isInBounds(localVec3i pos);

		worldVec3i	getWorldPos(localVec3i pos) {return (pos + _pos * CHUNK_SIZE);}
		localVec3i	getLocalPos(worldVec3i pos) {return (pos - _pos * CHUNK_SIZE);}
		chunkVec3i	getPos() {return (_pos);}

		bool	isLoaded() {return (_loaded);}
		void	setLoaded(bool state) {_loaded = state;}

		bool	isLoadedThisFrame() {return (_loadedThisFrame);}
		void	setLoadedThisFrame(bool state) {_loadedThisFrame = state;}
	private:
		chunkVec3i					_pos;

		std::vector<BlockStateId>	_blocks;
		std::atomic_bool			_generated = false;

		bool						_uploaded = false;
		std::atomic_bool			_meshed = false;
		std::shared_ptr<Mesh>		_mesh;
		std::shared_ptr<Mesh>		_transparentMesh;

		#define MAX_SPAWN_FADE		0.5
		float						_spawnFade = MAX_SPAWN_FADE;

		std::atomic_bool			_loaded = true;
		bool						_loadedThisFrame = true;
		World						*_world;
};

