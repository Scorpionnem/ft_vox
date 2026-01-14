/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockModel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:42:30 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/14 17:11:05 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Mesh.hpp"

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
		Mesh::Vertex(V8, Vec3(0,-1,0), UV01),
		Mesh::Vertex(V6, Vec3(0,-1,0), UV10),
		Mesh::Vertex(V5, Vec3(0,-1,0), UV00)
	);

	const Mesh::Face BOTTOM_FACE2(
		Mesh::Vertex(V8, Vec3(0,-1,0), UV01),
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
