/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Spline.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:25:16 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 22:39:24 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
# include "json.h"
using json = nlohmann::json;

struct	SplinePoint
{
	float	x;
	float	y;
};

struct	Spline
{
	float						freq;
	int							amp;
	int							noisiness;
	std::vector<SplinePoint>	points;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SplinePoint, x, y)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Spline, freq, amp, noisiness, points)

float	getValueInSpline(const Spline &spline, float value);
