/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Assets.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:30:46 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 12:54:15 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Assets.hpp"

Assets	assets; //Global

void	loadAssets()
{
	assets.loadTexture("atlas", "textures/atlas.png");
	assets.loadAtlasMap("grass_top", 0);
	assets.loadAtlasMap("grass_side", 1);
	assets.loadAtlasMap("dirt", 2);
	assets.loadShader("block", Shader("shaders/block_shader.vs", "shaders/block_shader.fs").ID);
}
