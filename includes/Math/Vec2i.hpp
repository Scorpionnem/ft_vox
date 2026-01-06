/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec2i.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:59:53 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/06 19:31:11 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct	Vec2i
{
	Vec2i()
	{
		this->x = 0;
		this->y = 0;
	}
	Vec2i(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Vec2i(int xy)
	{
		this->x = xy;
		this->y = xy;
	}
	int	x, y;
};
