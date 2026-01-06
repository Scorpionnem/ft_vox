/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:13:53 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 21:11:04 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>

struct Mat4
{
	float	data[16];

	Mat4() : Mat4(0) {}
	Mat4(float val)
	{
		std::fill(data, data + 16, 0.0f);
		this->data[0] = this->data[5] = this->data[10] = this->data[15] = val;
	}
	Mat4(const Mat4 &cpy)
	{
		*this = cpy;
	}
	Mat4 &operator=(const Mat4 &cpy)
	{
		for (int i = 0; i < 16; i++)
			this->data[i] = cpy.data[i];
		return (*this);
	}
	float &operator()(int col, int row)
	{
		return (data[col * 4 + row]);
	}
	const float &operator()(int col, int row) const
	{
		return (data[col * 4 + row]);
	}
};

inline Mat4 operator*(const Mat4 &a, const Mat4 &b)
{
	Mat4 result;
	for (int col = 0; col < 4; ++col)
	{
		for (int row = 0; row < 4; ++row)
		{
			result(col, row) = 0.0f;
			for (int k = 0; k < 4; ++k)
				result(col, row) += a(k, row) * b(col, k);
		}
	}
	return (result);
}

inline Mat4 translate(const Vec3 &v)
{
	Mat4 m(1);
	m(3, 0) = v.x;
	m(3, 1) = v.y;
	m(3, 2) = v.z;
	return (m);
}
