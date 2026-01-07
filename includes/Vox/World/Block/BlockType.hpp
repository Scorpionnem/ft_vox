/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 22:53:45 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 00:13:04 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

class	Property
{
};

class	BlockType;

class	BlockState
{
	public:
		BlockState(BlockType *parent, std::vector<Property> properties)
		{
			this->parent = parent;
			_properties = properties;
			_id = _gId++;
		}
		BlockState()
		{
		}
		BlockState(const BlockState &cpy)
		{
			_properties = cpy._properties;
			parent = cpy.parent;
			_id = cpy._id;
		}
		uint32_t	id() {return (_id);}
		BlockType				*parent;
		private:
		std::vector<Property>	_properties;
		uint32_t				_id;
		static uint32_t			_gId;
};

class	BlockType
{
	public:
		BlockType()
		{
		}
		BlockType(const std::string &id, bool solid)
		{
			_id = id;
			_solid = solid;
		}
		BlockType(const BlockType &cpy)
		{
			_solid = cpy._solid;
			_properties = cpy._properties;
			_blockStates = cpy._blockStates;
			_id = cpy._id;
		}
		std::vector<BlockState>	genBlockStates()
		{
			std::vector<BlockState>	blockstates;
			
			BlockState	bs(this, _properties);
			
			_blockStates.insert(std::make_pair(bs.id(), bs));
			blockstates.push_back(bs);
			return (blockstates);
		}
		uint32_t	getDefault()
		{
			return (_blockStates.begin()->first);
		}
		bool													_solid;
		std::string	id() {return (_id);}
	private:
		std::string												_id;
		std::vector<Property>									_properties;
		std::unordered_map<uint32_t, BlockState>				_blockStates;
};
