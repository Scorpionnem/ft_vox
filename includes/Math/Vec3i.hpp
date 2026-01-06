/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3i.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:56:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 13:21:58 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

struct Vec3i
{
	Vec3i()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vec3i(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3i(int xyz)
	{
		this->x = xyz;
		this->y = xyz;
		this->z = xyz;
	}

	Vec3i operator+(const Vec3i &v) const;
	Vec3i operator-(const Vec3i &v) const;
	Vec3i operator*(const Vec3i &v) const;
	Vec3i operator/(const Vec3i &v) const;

	uint64_t	hash()
	{
		const uint64_t BITS = 21;
		const uint64_t MASK = (1ULL << BITS) - 1;
		const int64_t  BIAS = 1LL << (BITS - 1);

		int	x = this->x;
		int	y = this->y;
		int	z = this->z;

		uint64_t ux = uint64_t(int64_t(x) + BIAS) & MASK;
		uint64_t uy = uint64_t(int64_t(y) + BIAS) & MASK;
		uint64_t uz = uint64_t(int64_t(z) + BIAS) & MASK;

		return (ux << (BITS * 2)) | (uy << (BITS * 1)) | (uz << (BITS * 0));
	}
	int	x, y, z;
};
