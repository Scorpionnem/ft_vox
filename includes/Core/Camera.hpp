/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:04:06 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/07 16:10:20 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Math.hpp"

class	Camera
{
	private:
		struct	Plane
		{
			float	A, B, C, D;
			void	normalize();
			Vec3	getNormal()
			{
				return (Vec3(A, B, C));
			}
			float	getDist(Vec3 point)
			{
				return (dot(getNormal(), point) + D);
			}
		};
		struct	Frustum
		{
			Plane top, bottom, right, left, zNear, zFar;
			bool	isInside(Vec3 minCorner, Vec3 maxCorner);
		};
	public:
		Camera() : Camera(Vec3(0)) {}
		Camera(Vec3 pos)
		{
			this->pos = pos;
			front = Vec3(0.0f, 0.0f, -1.0f);
			up = Vec3(0.0f, 1.0f, 0.0f);
		}
		
		void	update(float aspectRatio);

		Mat4	getViewMatrix()
		{
			return (lookAt(Vec3(0), Vec3(0) + front, up));
		}
		
		float	yaw = -90;
		float	pitch = 0;
		Vec3d	pos;
		Vec3	front;
		Vec3	up;
		Frustum	frustum;
	private:
		void	_updatePlaneNormals(float aspectRatio);
		Vec3	_direction;
};
