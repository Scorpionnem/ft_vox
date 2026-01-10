/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3i.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:57:27 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/10 21:28:15 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3i.hpp"
#include "Vec3.hpp"
#include "Vec3d.hpp"

Vec3i Vec3i::operator+(const Vec3i &v) const
{
	return (Vec3i(x + v.x, y + v.y, z + v.z));
}

Vec3i Vec3i::operator-(const Vec3i &v) const
{
	return (Vec3i(x - v.x, y - v.y, z - v.z));
}

Vec3i Vec3i::operator*(const Vec3i &v) const
{
	return (Vec3i(x * v.x, y * v.y, z * v.z));
}

Vec3i Vec3i::operator/(const Vec3i &v) const
{
	return (Vec3i(x / v.x, y / v.y, z / v.z));
}

Vec3i::Vec3i(const Vec3 &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vec3i::Vec3i(const Vec3d &v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
