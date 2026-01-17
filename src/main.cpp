/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:38:48 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/17 19:57:28 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.hpp"
#include "VoxScene.hpp"

int	main(void)
{
	Engine	engine;

	engine.start(std::make_unique<VoxScene>(engine));
}
