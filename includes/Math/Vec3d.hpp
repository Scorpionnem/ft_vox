/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec3d.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:59:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/07 17:31:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct	Vec3;

struct	Vec3d
{
	Vec3d()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Vec3d(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec3d(double xyz)
	{
		this->x = xyz;
		this->y = xyz;
		this->z = xyz;
	}
	Vec3d(const Vec3 &vi);

	Vec3d operator+(const Vec3d &v) const;
	Vec3d operator-(const Vec3d &v) const;
	Vec3d operator*(const Vec3d &v) const;
	Vec3d operator/(const Vec3d &v) const;
	double	x, y, z;
};
