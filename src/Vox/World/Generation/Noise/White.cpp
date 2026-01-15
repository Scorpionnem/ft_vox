/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   White.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:34:25 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/15 16:47:16 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "White.hpp"
#include <iostream>

float	Noise::White(Vec3i pos)
{
	Vec3 dotDir = Vec3(12.9898, 78.233, 37.719);
	
	Vec3 smallValue = sin(pos);
	float random = dot(smallValue, dotDir);
	random = frac(sin(random) * 143758.5453);
	return (random);
}
