/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunk.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:22:47 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/06 20:09:40 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <Math.hpp>
#include <Shader.hpp>
#include <MeshCache.hpp>
#include <atomic>
#include <limits.h>

# define CHUNK_SIZE 32
# define CHUNK_VOLUME CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE
# define BLOCK bool

#define seed 12312343298412897

inline Vec2 randomGradient(int ix, int iy)
{
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2;
	unsigned a = ix, b = iy;
	a *= 3284157443 + (seed + 1);

	b ^= a << s | a >> (w - s);
	b *= 1911520717;

	a ^= b << s | b >> (w - s);
	a *= 2048419325;
	float random = (a / (float)UINT_MAX) * 2.0f * M_PI;

	Vec2 v;
	v.x = sin(random);
	v.y = cos(random);

	return v;
}

inline float dotGridGradient(int ix, int iy, float x, float y)
{
	Vec2 gradient = randomGradient(ix, iy);

	float dx = x - (float)ix;
	float dy = y - (float)iy;

	return (dx * gradient.x + dy * gradient.y);
}

inline float interpolate(float a0, float a1, float w)
{
	return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

inline float perlin(float x, float y)
{
	int x0 = (int)std::floor(x);
	int y0 = (int)std::floor(y);
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	float sx = x - (float)x0;
	float sy = y - (float)y0;

	float n0 = dotGridGradient(x0, y0, x, y);
	float n1 = dotGridGradient(x1, y0, x, y);
	float ix0 = interpolate(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	float ix1 = interpolate(n0, n1, sx);

	float value = interpolate(ix0, ix1, sy);

	return (value);
}

inline float	perlin(float x, float y, float z)
{
	float ab = perlin(x, y);
	float bc = perlin(y, z);
	float ac = perlin(x, z);

	float ba = perlin(y, x);
	float cb = perlin(z, y);
	float ca = perlin(z, x);

	return (ab + bc + ac + ba + cb + ca) / 6.0;
}

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
		Mesh::Vertex(V6, Vec3(1,0,0), UV10)
	);

	const Mesh::Face EAST_FACE2(
		Mesh::Vertex(V3, Vec3(1,0,0), UV11),
		Mesh::Vertex(V6, Vec3(1,0,0), UV10),
		Mesh::Vertex(V7, Vec3(1,0,0), UV00)
	);

	const Mesh::Face WEST_FACE1(
		Mesh::Vertex(V5, Vec3(-1,0,0), UV10),
		Mesh::Vertex(V1, Vec3(-1,0,0), UV01),
		Mesh::Vertex(V4, Vec3(-1,0,0), UV11)
	);

	const Mesh::Face WEST_FACE2(
		Mesh::Vertex(V5, Vec3(-1,0,0), UV10),
		Mesh::Vertex(V4, Vec3(-1,0,0), UV11),
		Mesh::Vertex(V8, Vec3(-1,0,0), UV00)
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

	void	addFace(std::shared_ptr<Mesh> mesh, Vec3i pos, Direction dir);
}

inline float	calcNoise(const Vec3i &pos, float freq, float amp, int noisiness)
{
	float	res = 0;
	for (int i = 0; i < noisiness; i++)
	{
		res += perlin(pos.x * freq, pos.y * freq, pos.z * freq) * amp;

		freq *= 2;
		amp /= 2;
	}

	if (res > 1.0f)
		res = 1.0f;
	else if (res < -1.0f)
		res = -1.0f;

	return (res);
}

inline float	calcNoise(const Vec2i &pos, float freq, float amp, int noisiness)
{
	float	res = 0;
	for (int i = 0; i < noisiness; i++)
	{
		res += perlin(pos.x * freq, pos.y * freq) * amp;

		freq *= 2;
		amp /= 2;
	}

	if (res > 1.0f)
		res = 1.0f;
	else if (res < -1.0f)
		res = -1.0f;

	return (res);
}

class	Chunk
{
	public:
		Chunk(Vec3i pos) : _pos(pos) {}
		~Chunk() {}

		Vec3i	worldPos(Vec3i pos)
		{
			return (pos + _pos * CHUNK_SIZE);
		}
		int	getGenerationHeight(Vec2i pos)
		{
			return (std::floor(calcNoise(pos, 0.0125, 1, 1) * 100));
		}
		BLOCK	getGenerationBlock(Vec3i pos)
		{
			Vec3i	wp = worldPos(pos);

			if (wp.y < getGenerationHeight(Vec2i(wp.x, wp.z)))
				return (true);
			return (false);
		}
		void	generateTerrain()
		{
			for (int x = 0; x < CHUNK_SIZE; x++)
				for (int z = 0; z < CHUNK_SIZE; z++)
				{
					Vec3i	wp = worldPos(Vec3i(x, 0, z));

					int	terrainHeight = getGenerationHeight(Vec2i(wp.x, wp.z));

					if (wp.y > terrainHeight)
						continue ;

					for (int y = CHUNK_SIZE; y >= 0; y--)
					{
						if (worldPos(Vec3i(x, y, z)).y > terrainHeight)
							continue ;

						Vec3i	pos = Vec3i(x, y, z);
						setBlock(pos, getGenerationBlock(pos));
					}
				}
		}
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
		void	upload()
		{
			if (!_uploaded)
				_mesh->upload();
			_uploaded = true;
		}
		void	genMesh(MeshCache &meshCache)
		{
			_mesh = meshCache.gen();

			for (int x = 0; x < CHUNK_SIZE; x++)
				for (int y = 0; y < CHUNK_SIZE; y++)
					for (int z = 0; z < CHUNK_SIZE; z++)
					{
						if (getBlock(Vec3i(x, y, z)))
						{
							if (!getBlock(Vec3i(x, y + 1, z)))
								Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::TOP);
							if (!getBlock(Vec3i(x, y - 1, z)))
								Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::BOTTOM);
							if (!getBlock(Vec3i(x + 1, y, z)))
								Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::EAST);
							if (!getBlock(Vec3i(x - 1, y, z)))
								Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::WEST);
							if (!getBlock(Vec3i(x, y, z + 1)))
								Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::NORTH);
							if (!getBlock(Vec3i(x, y, z - 1)))
								Cube::addFace(_mesh, Vec3i(x, y, z), Cube::Direction::SOUTH);
						}
					}
			_meshed = true;
		}
		void	draw(std::shared_ptr<Shader> shader)
		{
			_mesh->draw(shader);
		}
		BLOCK	getBlock(Vec3i pos)
		{
			if (!isInBounds(pos))
				return (getGenerationBlock(pos));
			int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;
			return (_blocks[index]);
		}
		void	setBlock(Vec3i pos, BLOCK block)
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
		std::vector<BLOCK>	_blocks;
		Vec3i				_pos;
		std::shared_ptr<Mesh>	_mesh;
		bool					_uploaded = false;
		std::atomic_bool		_generated = false;
		std::atomic_bool		_meshed = false;
};
