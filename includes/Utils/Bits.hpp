/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bits.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:18:30 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:41:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

// Creates a bitmask with n 1's, bitMask(5) -> 00011111
inline uint8_t	bitMask(uint8_t n)
{
	return ((1u << n) - 1u);
}
