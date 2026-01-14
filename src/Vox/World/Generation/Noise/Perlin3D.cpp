/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Perlin3D.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:01:51 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/14 18:31:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Perlin3D.hpp"

float	Noise::perlin3D(float x, float y, float z)
{
	float ab = Noise::perlin2D(x, y);
	float bc = Noise::perlin2D(y, z);
	float ac = Noise::perlin2D(x, z);

	return (ab + bc + ac) / 3.0;
}

float	Noise::calcNoise(const Vec3i &pos, float freq, float amp, int noisiness)
{
	float	res = 0;
	for (int i = 0; i < noisiness; i++)
	{
		res += Noise::perlin3D(pos.x * freq, pos.y * freq, pos.z * freq) * amp;

		freq *= 2;
		amp /= 2;
	}

	if (res > 1.0f)
		res = 1.0f;
	else if (res < -1.0f)
		res = -1.0f;

	return (res);
}
