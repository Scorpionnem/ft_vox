/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockState.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:09:58 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/15 17:44:48 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <string>

using BlockStateId = uint32_t;
using BlockStateHash = uint32_t;

class	BlockType;

class	BlockState
{
	public:
		BlockState(BlockType *parent, BlockStateHash properties)
		{
			_parent = parent;
			_properties = properties;
			_id = _globalId++;
		}

		uint8_t	getProperty(const std::string &prop);

		BlockStateId	id() {return (_id);}
		BlockType	*getParent() {return (_parent);}

		static BlockStateId	getGlobalId() {return (_globalId);}
	private:
		BlockType					*_parent;

		BlockStateHash				_properties;

		BlockStateId				_id;
		static BlockStateId			_globalId;
};
