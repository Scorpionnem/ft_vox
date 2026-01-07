/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:08:20 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/07 16:10:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

void	Camera::update(float aspectRatio)
{
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	_direction.x = cos(radians(yaw)) * cos(radians(pitch));
	_direction.y = sin(radians(pitch));
	_direction.z = sin(radians(yaw)) * cos(radians(pitch));
	front = normalize(_direction);
	_updatePlaneNormals(aspectRatio);
}

void	Camera::_updatePlaneNormals(float aspectRatio)
{
	Mat4	vp = perspective(70, aspectRatio, 0.01, 1000) * getViewMatrix();

	frustum.left.A = vp(0,3) + vp(0,0);
	frustum.left.B = vp(1,3) + vp(1,0);
	frustum.left.C = vp(2,3) + vp(2,0);
	frustum.left.D = vp(3,3) + vp(3,0);

	frustum.right.A = vp(0,3) - vp(0,0);
	frustum.right.B = vp(1,3) - vp(1,0);
	frustum.right.C = vp(2,3) - vp(2,0);
	frustum.right.D = vp(3,3) - vp(3,0);

	frustum.bottom.A = vp(0,3) + vp(0,1);
	frustum.bottom.B = vp(1,3) + vp(1,1);
	frustum.bottom.C = vp(2,3) + vp(2,1);
	frustum.bottom.D = vp(3,3) + vp(3,1);

	frustum.top.A = vp(0,3) - vp(0,1);
	frustum.top.B = vp(1,3) - vp(1,1);
	frustum.top.C = vp(2,3) - vp(2,1);
	frustum.top.D = vp(3,3) - vp(3,1);

	frustum.zNear.A = vp(0,3) + vp(0,2);
	frustum.zNear.B = vp(1,3) + vp(1,2);
	frustum.zNear.C = vp(2,3) + vp(2,2);
	frustum.zNear.D = vp(3,3) + vp(3,2);

	frustum.zFar.A = vp(0,3) - vp(0,2);
	frustum.zFar.B = vp(1,3) - vp(1,2);
	frustum.zFar.C = vp(2,3) - vp(2,2);
	frustum.zFar.D = vp(3,3) - vp(3,2);

	frustum.zNear.normalize();
	frustum.zFar.normalize();
	frustum.bottom.normalize();
	frustum.top.normalize();
	frustum.left.normalize();
	frustum.right.normalize();
}

bool	Camera::Frustum::isInside(Vec3 minCorner, Vec3 maxCorner)
{
	Vec3	point = Vec3(top.A >= 0 ? maxCorner.x : minCorner.x, top.B >= 0 ? maxCorner.y : minCorner.y, top.C >= 0 ? maxCorner.z : minCorner.z);
	if (top.getDist(point) < 0)
		return (false);

	point = Vec3(bottom.A >= 0 ? maxCorner.x : minCorner.x, bottom.B >= 0 ? maxCorner.y : minCorner.y, bottom.C >= 0 ? maxCorner.z : minCorner.z);
	if (bottom.getDist(point) < 0)
		return (false);

	point = Vec3(right.A >= 0 ? maxCorner.x : minCorner.x, right.B >= 0 ? maxCorner.y : minCorner.y, right.C >= 0 ? maxCorner.z : minCorner.z);
	if (right.getDist(point) < 0)
		return (false);

	point = Vec3(left.A >= 0 ? maxCorner.x : minCorner.x, left.B >= 0 ? maxCorner.y : minCorner.y, left.C >= 0 ? maxCorner.z : minCorner.z);
	if (left.getDist(point) < 0)
		return (false);

	point = Vec3(zNear.A >= 0 ? maxCorner.x : minCorner.x, zNear.B >= 0 ? maxCorner.y : minCorner.y, zNear.C >= 0 ? maxCorner.z : minCorner.z);
	if (zNear.getDist(point) < 0)
		return (false);

	point = Vec3(zFar.A >= 0 ? maxCorner.x : minCorner.x, zFar.B >= 0 ? maxCorner.y : minCorner.y, zFar.C >= 0 ? maxCorner.z : minCorner.z);
	if (zFar.getDist(point) < 0)
		return (false);

	return (true);
}

void	Camera::Plane::normalize()
{
	float	ratio = std::sqrt(A * A + B * B + C * C);

	A /= ratio;
	B /= ratio;
	C /= ratio;
	D /= ratio;
}
