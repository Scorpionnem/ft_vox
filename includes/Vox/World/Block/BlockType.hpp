/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 22:53:45 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 19:33:23 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <cmath>
#include <memory>
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
		BlockState(BlockType *parent, BlockStateHash properties)
		{
			this->parent = parent;
			_properties = properties;
			_id = _globalId++;
		}

		BlockStateId	id() {return (_id);}

		uint8_t	getProperty(const std::string &prop);
		BlockType					*parent;
	private:
		uint8_t	_bitMask(uint8_t n)
		{
			return ((1u << n) - 1u);
		}
		BlockStateHash				_properties;

		BlockStateId				_id;
		static BlockStateId			_globalId;
};

class	BlockType
{
	public:
		BlockType(const std::string &name, std::vector<Property> properties, bool solid)
		{
			_name = name;
			for (Property &prop : properties)
				_properties.insert(std::make_pair(prop.name, prop));
			_solid = solid;
			_processHashLayout();
			_genBlockStates();
		}
		~BlockType()
		{
			std::cout << "destroyed blocktype" << std::endl;
		}
		std::shared_ptr<BlockState>	getBlockState(std::map<std::string, uint8_t> properties)
		{
			auto find = _blockStates.find(_getBlockStateHash(properties));
			if (find == _blockStates.end())
				return (nullptr);
			return (find->second);
		}
		std::shared_ptr<BlockState>	getDefault()
		{
			auto find = _blockStates.find(0);
			if (find == _blockStates.end())
				return (nullptr);
			return (find->second);
		}

		std::string	name() {return (_name);}
		uint8_t	offsetOf(const std::string &prop)
		{
			return (_offsets[prop]);
		}
		uint8_t	sizeOf(const std::string &prop)
		{
			auto find = _properties.find(prop);
			if (find == _properties.end())
				return (0);
			return (find->second.bitCount);
		}
		std::unordered_map<BlockStateHash, std::shared_ptr<BlockState>>	&getBlockStates()
		{
			return (_blockStates);
		}
		bool	isSolid()
		{
			return (_solid);
		}
	private:
		void			_genBlockStates()
		{
			_blockStates.insert({0, std::make_shared<BlockState>(this, 0)});
		}
		BlockStateHash	_getBlockStateHash(std::map<std::string, uint8_t> properties);
		BlockStateHash	_setBits(BlockStateHash hash, uint8_t offset, uint8_t val);
		void			_processHashLayout();

		bool											_solid;
		std::string										_name;

		std::unordered_map<BlockStateHash, std::shared_ptr<BlockState>>	_blockStates;
		std::unordered_map<std::string, uint8_t>		_offsets;
		std::unordered_map<std::string, Property>		_properties;
};

/*
	World.registerBlock(BlockType);
		BlockType._genBlockStates()
		returns all blockStates of the blocktype

	World.getBlock(string id)
		Block.getState()
*/
