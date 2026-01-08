/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Perlin2D.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:32:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 22:25:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Math.hpp"

namespace Perlin2D
{
	float	perlin2D(float x, float y);
	float	calcNoise(const Vec2i &pos, float freq, float amp, int noisiness);
};
