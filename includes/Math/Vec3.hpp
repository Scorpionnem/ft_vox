/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:59:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 13:01:22 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vec3i.hpp"

struct	Vec3
{
	Vec3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3(float xyz)
	{
		this->x = xyz;
		this->y = xyz;
		this->z = xyz;
	}
	Vec3(const Vec3i &vi)
	{
		this->x = vi.x;
		this->y = vi.y;
		this->z = vi.z;
	}

	Vec3 operator+(const Vec3 &v) const;
	Vec3 operator-(const Vec3 &v) const;
	Vec3 operator*(const Vec3 &v) const;
	Vec3 operator/(const Vec3 &v) const;
	float	x, y, z;
};
