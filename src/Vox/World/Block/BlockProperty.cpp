/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BlockProperty.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 13:13:51 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:15:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BlockProperty.hpp"

BlockProperty::BlockProperty(const char *name, uint8_t minVal, uint8_t maxVal)
{
	this->name = name;
	this->minVal = minVal;
	this->maxVal = maxVal;
	bitCount = (int)(log(maxVal) / log(2) + 1);
}
