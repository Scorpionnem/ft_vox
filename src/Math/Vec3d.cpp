/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3d.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:57:27 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/07 14:19:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3d.hpp"
#include "Vec3.hpp"

Vec3d Vec3d::operator+(const Vec3d &v) const
{
	return (Vec3d(x + v.x, y + v.y, z + v.z));
}

Vec3d Vec3d::operator-(const Vec3d &v) const
{
	return (Vec3d(x - v.x, y - v.y, z - v.z));
}

Vec3d Vec3d::operator*(const Vec3d &v) const
{
	return (Vec3d(x * v.x, y * v.y, z * v.z));
}

Vec3d Vec3d::operator/(const Vec3d &v) const
{
	return (Vec3d(x / v.x, y / v.y, z / v.z));
}

Vec3d::Vec3d(const Vec3 &vi)
{
	this->x = vi.x;
	this->y = vi.y;
	this->z = vi.z;
}
