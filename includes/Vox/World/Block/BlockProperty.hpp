/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockProperty.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:11:13 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:28:46 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <cmath>

struct	BlockProperty
{
	public:
		BlockProperty(const char *name, uint8_t minVal, uint8_t maxVal);

		const char	*name;

		uint8_t		minVal = 0;
		uint8_t		maxVal = 0;

		uint8_t		bitCount = 0;
};
