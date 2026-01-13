/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockType.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 23:36:34 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:14:24 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BlockType.hpp"

BlockStateHash	BlockType::_getBlockStateHash(std::map<std::string, uint8_t> properties)
{
	BlockStateHash	res = 0;

	for (auto &pair : properties)
	{
		auto find = _properties.find(pair.first);
		if (find != _properties.end())
		{
			BlockProperty	&prop = find->second;

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
		BlockProperty &prop = pair.second;

		_offsets[prop.name] = offset;
		offset += prop.bitCount;
	}
}

BlockStateHash	BlockType::_setBits(BlockStateHash hash, uint8_t offset, uint8_t val)
{
	return (hash |= val << offset);
}
