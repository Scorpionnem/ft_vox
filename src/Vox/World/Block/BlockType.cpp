/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockType.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 23:36:34 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 19:29:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BlockType.hpp"

BlockStateId	BlockState::_globalId = 0;

uint8_t	BlockState::getProperty(const std::string &prop)
{
	(void)prop;
	return (0);
	// return ((_properties >> parent->offsetOf(prop)) & _bitMask(parent->sizeOf(prop)));
}

BlockStateHash	BlockType::_getBlockStateHash(std::map<std::string, uint8_t> properties)
{
	BlockStateHash	res = 0;

	for (auto &pair : properties)
	{
		auto find = _properties.find(pair.first);
		if (find != _properties.end())
		{
			Property	&prop = find->second;

			res = _setBits(res, _offsets[prop.name], properties.find(prop.name)->second);
		}
	}
	return (res);
}

void	BlockType::_processHashLayout()
{
	uint32_t	offset = 0;

	for (auto &pair : _properties)
	{
		Property &prop = pair.second;

		_offsets[prop.name] = offset;
		offset += prop.bitCount;
	}
}

BlockStateHash	BlockType::_setBits(BlockStateHash hash, uint8_t offset, uint8_t val)
{
	return (hash |= val << offset);
}
