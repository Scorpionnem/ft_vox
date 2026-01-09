/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/09 21:30:49 by mbatty           ###   ########.fr       */
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

# define CHUNK_SIZE 32
# define CHUNK_VOLUME CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE

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

class	World;

class	Chunk
{
	public:
		Chunk(Vec3i pos, World *world) : _pos(pos)
		{
			_world = world;
		}
		~Chunk() {}

		Vec3i	worldPos(Vec3i pos)
		{
			return (pos + _pos * CHUNK_SIZE);
		}
		Vec3i	localPos(Vec3i pos)
		{
			return (pos - _pos * CHUNK_SIZE);
		}
		int	getGenerationHeight(Vec2i pos);
		BlockStateId	getGenerationBlock(Vec3i pos);
		void	generateTerrain();
		void	generateFeatures()
		{

		}
		void	generate()
		{
			_blocks.resize(CHUNK_VOLUME);

			generateTerrain();
			generateFeatures();
			_generated = true;
		}
		bool	upload()
		{
			if (!_uploaded)
			{
				_mesh->upload();
				_transparentMesh->upload();
				_uploaded = true;
				return (true);
			}
			_uploaded = true;
			return (false);
		}
		void	genMesh(MeshCache &meshCache);
		void	remesh(MeshCache &meshCache)
		{
			_uploaded = false;
			genMesh(meshCache);
		}
		void	draw(std::shared_ptr<Shader> shader)
		{
			_mesh->draw(shader);
			_transparentMesh->draw(shader);
		}
		bool	isBlockSolid(Vec3i pos);
		BlockStateId	getBlock(Vec3i pos)
		{
			if (!isInBounds(pos))
				return (getGenerationBlock(pos));
			int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;
			return (_blocks[index]);
		}
		void	setBlock(Vec3i pos, BlockStateId block)
		{
			if (!isInBounds(pos))
				return ;
			int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;
			_blocks[index] = block;
		}

		bool	isInBounds(Vec3i pos)
		{
			if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE)
				return (false);
			return (true);
		}
	// private:
		std::vector<BlockStateId>	_blocks;
		Vec3i						_pos;
		std::shared_ptr<Mesh>		_mesh;
		std::shared_ptr<Mesh>		_transparentMesh;
		bool						_uploaded = false;
		std::atomic_bool			_generated = false;
		std::atomic_bool			_meshed = false;
		World						*_world;
};
