/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:07:20 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/02 13:09:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vec3.hpp"

Vec3 Vec3::operator+(const Vec3 &v) const
{
	return (Vec3(x + v.x, y + v.y, z + v.z));
}

Vec3 Vec3::operator-(const Vec3 &v) const
{
	return (Vec3(x - v.x, y - v.y, z - v.z));
}

Vec3 Vec3::operator*(const Vec3 &v) const
{
	return (Vec3(x * v.x, y * v.y, z * v.z));
}

Vec3 Vec3::operator/(const Vec3 &v) const
{
	return (Vec3(x / v.x, y / v.y, z / v.z));
}
