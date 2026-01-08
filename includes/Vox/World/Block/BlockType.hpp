/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 22:53:45 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 14:27:32 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <cmath>
#include <iostream>

using BlockStateId = uint32_t;
using BlockStateHash = uint32_t;
using BlockTypeId = uint32_t;

class	Property
{
	public:
		Property(const char *name, uint8_t minVal, uint8_t maxVal)
		{
			this->name = name;
			this->minVal = minVal;
			this->maxVal = maxVal;
			bitCount = (int)(log(maxVal) / log(2) + 1);
			std::cout << name << " uses " << (int)bitCount << std::endl;
		}

		const char	*name;
		
		uint8_t		minVal = 0;
		uint8_t		maxVal = 0;

		uint8_t		bitCount = 0;
};

class	BlockType;

class	BlockState
{
	public:
		BlockState(BlockType *parent, std::vector<Property> properties)
		{
			this->parent = parent;
			_properties = properties;
			_id = _globalId++;
		}

		BlockStateId	id() {return (_id);}

		BlockType					*parent;
	private:
		std::vector<Property>		_properties;

		BlockStateId				_id;
		static BlockStateId			_globalId;
};

class	BlockType
{
	public:
		BlockType(const std::string &id, std::vector<Property> properties, bool solid = true)
		{
			_id = id;
			_properties = properties;
			_solid = solid;
			_processHashLayout();
		}
		std::string	id() {return (_id);}
		BlockStateHash	getBlockStateHash(std::map<std::string, uint8_t> properties)
		{
			BlockStateHash	res = 0;
			for (Property &prop : _properties)
			{
				if (properties.find(prop.name) != properties.end())
				{
					res = setValue(res, _offsets[prop.name], properties.find(prop.name)->second);
				}
			}
			return (res);
		}
		BlockStateHash	setValue(BlockStateHash hash, uint8_t offset, uint8_t val)
		{
			return (hash |= val << offset);
		}
	private:
		void	_processHashLayout()
		{
			uint32_t	offset = 0;
			for (Property &prop : _properties)
			{
				std::cout << prop.name << " bits used at offset " << offset << std::endl;
				_offsets[prop.name] = offset;
				offset += prop.bitCount;
			}
		}
		bool											_solid;
		std::string										_id;
		std::vector<Property>							_properties;
		std::unordered_map<std::string, uint8_t>		_offsets;
};
