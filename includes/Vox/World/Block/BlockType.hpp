/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 22:53:45 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:29:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <memory>

#include "BlockState.hpp"
#include "BlockProperty.hpp"

using BlockTypeId = uint32_t;

class	BlockType
{
	public:
		BlockType(const std::string &name, int textureId, std::vector<BlockProperty> properties, bool solid)
		{
			_name = name;
			for (BlockProperty &prop : properties)
				_properties.insert(std::make_pair(prop.name, prop));
			_solid = solid;
			_textureId = textureId;
			_processHashLayout();
			_genBlockStates();
		}
		~BlockType() {}

		std::shared_ptr<BlockState>	getState(std::map<std::string, uint8_t> properties)
		{
			auto find = _blockStates.find(_getBlockStateHash(properties));
			if (find == _blockStates.end())
				return (nullptr);
			return (find->second);
		}
		std::shared_ptr<BlockState>	getDefaultState()
		{
			auto find = _blockStates.find(0);
			if (find == _blockStates.end())
				return (nullptr);
			return (find->second);
		}

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

		std::unordered_map<BlockStateHash, std::shared_ptr<BlockState>>	&getBlockStates() {return (_blockStates);}
		bool isSolid() {return (_solid);}
		std::string	name() {return (_name);}
		int	textureId() {return (_textureId);}
	private:
		void			_genBlockStates()
		{
			_blockStates.insert({0, std::make_shared<BlockState>(this, 0)});
		}

		BlockStateHash	_getBlockStateHash(std::map<std::string, uint8_t> properties);
		BlockStateHash	_setBits(BlockStateHash hash, uint8_t offset, uint8_t val);
		void			_processHashLayout();

		bool		_solid;
		std::string	_name;
		int			_textureId;

		std::unordered_map<BlockStateHash, std::shared_ptr<BlockState>>	_blockStates;
		std::unordered_map<std::string, uint8_t>						_offsets;
		std::unordered_map<std::string, BlockProperty>					_properties;
};
