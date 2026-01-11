/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/11 14:45:22 by mbatty           ###   ########.fr       */
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
#include "Perlin2D.hpp"

namespace Cube
{
	const Vec2 UV00(0.f, 0.f);
	const Vec2 UV10(1.f, 0.f);
	const Vec2 UV11(1.f, 1.f);
	const Vec2 UV01(0.f, 1.f);
	const Vec3	V1(0, 1, 1);
	const Vec3	V2(1, 1, 1);
	const Vec3	V3(1, 1, 0);
	const Vec3	V4(0, 1, 0);
	const Vec3	V5(0, 0, 1);
	const Vec3	V6(1, 0, 1);
	const Vec3	V7(1, 0, 0);
	const Vec3	V8(0, 0, 0);

	const Mesh::Face NORTH_FACE1(
		Mesh::Vertex(V5, Vec3(0,0,1), UV00),
		Mesh::Vertex(V2, Vec3(0,0,1), UV11),
		Mesh::Vertex(V1, Vec3(0,0,1), UV01)
	);

	const Mesh::Face NORTH_FACE2(
		Mesh::Vertex(V5, Vec3(0,0,1), UV00),
		Mesh::Vertex(V6, Vec3(0,0,1), UV10),
		Mesh::Vertex(V2, Vec3(0,0,1), UV11)
	);

	const Mesh::Face SOUTH_FACE1(
		Mesh::Vertex(V8, Vec3(0,0,-1), UV00),
		Mesh::Vertex(V4, Vec3(0,0,-1), UV01),
		Mesh::Vertex(V3, Vec3(0,0,-1), UV11)
	);

	const Mesh::Face SOUTH_FACE2(
		Mesh::Vertex(V8, Vec3(0,0,-1), UV00),
		Mesh::Vertex(V3, Vec3(0,0,-1), UV11),
		Mesh::Vertex(V7, Vec3(0,0,-1), UV10)
	);

	const Mesh::Face EAST_FACE1(
		Mesh::Vertex(V3, Vec3(1,0,0), UV11),
		Mesh::Vertex(V2, Vec3(1,0,0), UV01),
		Mesh::Vertex(V6, Vec3(1,0,0), UV00)
	);

	const Mesh::Face EAST_FACE2(
		Mesh::Vertex(V3, Vec3(1,0,0), UV11),
		Mesh::Vertex(V6, Vec3(1,0,0), UV00),
		Mesh::Vertex(V7, Vec3(1,0,0), UV10)
	);

	const Mesh::Face WEST_FACE1(
		Mesh::Vertex(V5, Vec3(-1,0,0), UV01),
		Mesh::Vertex(V1, Vec3(-1,0,0), UV00),
		Mesh::Vertex(V4, Vec3(-1,0,0), UV10)
	);

	const Mesh::Face WEST_FACE2(
		Mesh::Vertex(V5, Vec3(-1,0,0), UV01),
		Mesh::Vertex(V4, Vec3(-1,0,0), UV10),
		Mesh::Vertex(V8, Vec3(-1,0,0), UV11)
	);

	const Mesh::Face TOP_FACE1(
		Mesh::Vertex(V1, Vec3(0,1,0), UV01),
		Mesh::Vertex(V2, Vec3(0,1,0), UV11),
		Mesh::Vertex(V4, Vec3(0,1,0), UV00)
	);

	const Mesh::Face TOP_FACE2(
		Mesh::Vertex(V2, Vec3(0,1,0), UV11),
		Mesh::Vertex(V3, Vec3(0,1,0), UV10),
		Mesh::Vertex(V4, Vec3(0,1,0), UV00)
	);

	const Mesh::Face BOTTOM_FACE1(
		Mesh::Vertex(V8, Vec3(0,-1,0), UV00),
		Mesh::Vertex(V6, Vec3(0,-1,0), UV10),
		Mesh::Vertex(V5, Vec3(0,-1,0), UV01)
	);

	const Mesh::Face BOTTOM_FACE2(
		Mesh::Vertex(V8, Vec3(0,-1,0), UV00),
		Mesh::Vertex(V7, Vec3(0,-1,0), UV11),
		Mesh::Vertex(V6, Vec3(0,-1,0), UV10)
	);

	enum class Direction
	{
		NORTH,
		SOUTH,
		EAST,
		WEST,
		TOP,
		BOTTOM
	};

	void	addFace(std::shared_ptr<Mesh> mesh, Vec3i pos, Direction dir, int textureId);
}

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

		void	draw(std::shared_ptr<Shader> shader);
		bool	upload();

		bool			isBlockSolid(localVec3i pos);
		BlockStateId	getBlock(localVec3i pos);
		void			setBlock(localVec3i pos, BlockStateId block);
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
};
