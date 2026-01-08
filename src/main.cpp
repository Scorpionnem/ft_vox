/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 14:28:14 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"
#include "VoxScene.hpp"

/*
void	printBits(uint32_t n)
{
	int	i = 0;
	while (i < 32)
	{
		std::cout << ((n >> i) & 1);
		i++;
	}
	std::cout << std::endl;
}

	Property	FACING(
		"facing",
		0,
		5
	);
	Property	WATERLOGGED(
		"waterlogged",
		0,
		1
	);
	Property	REDSTONE_LEVEL(
		"redstone_level",
		0,
		15
	);
	Property	WATER_LEVEL(
		"water_level",
		0,
		15
	);
	Property	LIT(
		"lit",
		0,
		1
	);

	BlockType	dirt(
		"dirt",
		{FACING, WATERLOGGED, REDSTONE_LEVEL, WATER_LEVEL, LIT}
	);

	printBits(dirt.getBlockStateHash({{"facing", 1}, {"waterlogged", 1}, {"water_level", 13}, {"lit", 1}}));
	printBits(dirt.getBlockStateHash({{"facing", 4}, {"waterlogged", 0}, {"redstone_level", 13}}));

	return (0);
*/

int	main(void)
{
	Engine	engine;

	engine.start(std::make_unique<VoxScene>(engine));
}
