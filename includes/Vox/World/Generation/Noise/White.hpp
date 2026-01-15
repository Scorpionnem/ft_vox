/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   White.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:04:56 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/15 16:34:57 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Math.hpp"

extern uint seed;

namespace Noise
{
	float	White(Vec3i pos);
};
