/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockState.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:13:56 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:19:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BlockState.hpp"
#include "BlockType.hpp"
#include <Bits.hpp>

BlockStateId	BlockState::_globalId = 0;

uint8_t	BlockState::getProperty(const std::string &prop)
{
	return ((_properties >> _parent->offsetOf(prop)) & bitMask(_parent->sizeOf(prop)));
}
