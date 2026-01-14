/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Perlin3D.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:57:18 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/14 18:05:04 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Perlin2D.hpp"

namespace Noise
{
	float	perlin3D(float x, float y, float z);
	float	calcNoise(const Vec3i &pos, float freq, float amp, int noisiness);
};
