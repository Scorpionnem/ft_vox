/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3i.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:57:27 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/04 12:57:41 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3i.hpp"

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
