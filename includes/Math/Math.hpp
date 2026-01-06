/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:00:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/06 19:08:41 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vec3.hpp"
#include "Vec3i.hpp"
#include "Vec2.hpp"
#include "Vec2i.hpp"
#include "Mat4.hpp"
#include <cmath>

// Vec3

float	dot(const Vec3 &v1, const Vec3 &v2);
float	length(const Vec3 &v);
Vec3	cross(const Vec3 &v1, const Vec3 &v2);
Vec3	normalize(const Vec3 &v);

// Vec2

// Mat4

inline Mat4 perspective(float fovDeg, float aspect, float near, float far)
{
	float fovRad = fovDeg * M_PI / 180.0f;
	float f = 1.0f / std::tan(fovRad / 2.0f);

	Mat4 m;
	m.data[0] = f / aspect;
	m.data[5] = f;
	m.data[10] = (far + near) / (near - far);
	m.data[11] = -1.0f;
	m.data[14] = (2.0f * far * near) / (near - far);
	return (m);
}

inline Mat4 lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up)
{
	Vec3 f = normalize(center - eye);
	Vec3 s = normalize(cross(f, up));
	Vec3 u = cross(s, f);

	Mat4 m(1);
	m(0, 0) = s.x; m(1, 0) = s.y; m(2, 0) = s.z;
	m(0, 1) = u.x; m(1, 1) = u.y; m(2, 1) = u.z;
	m(0, 2) = -f.x; m(1, 2) = -f.y; m(2, 2) = -f.z;
	m(3, 0) = -dot(s, eye);
	m(3, 1) = -dot(u, eye);
	m(3, 2) = dot(f, eye);
	return (m);
}

inline Mat4 rotate(float angleRad, const Vec3 &axis)
{
	Vec3 a = normalize(axis);
	float c = std::cos(angleRad);
	float s = std::sin(angleRad);
	float oneMinusC = 1.0f - c;

	Mat4 m(1);
	m(0, 0) = c + a.x * a.x * oneMinusC;
	m(0, 1) = a.x * a.y * oneMinusC + a.z * s;
	m(0, 2) = a.x * a.z * oneMinusC - a.y * s;

	m(1, 0) = a.y * a.x * oneMinusC - a.z * s;
	m(1, 1) = c + a.y * a.y * oneMinusC;
	m(1, 2) = a.y * a.z * oneMinusC + a.x * s;

	m(2, 0) = a.z * a.x * oneMinusC + a.y * s;
	m(2, 1) = a.z * a.y * oneMinusC - a.x * s;
	m(2, 2) = c + a.z * a.z * oneMinusC;

	return (m);
}

inline Mat4 rotate(Mat4 &mat, float angleRad, const Vec3 &axis)
{
	return (mat * rotate(angleRad, axis));
}

inline float radians(float deg)
{
	return (deg * M_PI / 180.0f);
}
