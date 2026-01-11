/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VoxScene.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:13:58 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/11 14:54:29 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Scene.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Engine.hpp"
#include "LightCache.hpp"

#include "World.hpp"

class	VoxScene : public Scene
{
	public:
		VoxScene(const Engine &engine) : Scene(engine) {}
		~VoxScene() {}
		void	build();
		void	update(float delta, const Window::Events &events);
		void	display();
	private:
		void	_updateCamera(float delta, const Window::Events &events);

		std::shared_ptr<Shader>	_shader;

		Camera	_camera;
		std::unique_ptr<World>	_world;
		std::shared_ptr<Light>	_light;
		std::vector<float>		_fpss;

		bool	_cursorMode = false;
		bool	_lockedFPS = true;
};
