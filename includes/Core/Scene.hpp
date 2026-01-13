/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:43:28 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:51:18 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Window.hpp"
#include <memory>

class Engine;

/*
	Abstract Scene class, it has access to a const ref to engine, every frame update and display functions are called,
	when switching/starting on a scene build is called.
*/
class	Scene
{
	public:
		Scene(const Engine &engine) : _engine(engine) {}
		virtual ~Scene() {}
		virtual void build() = 0;
		virtual void update(float delta, const Window::Events &events) = 0;
		virtual void display() = 0;

		bool	requestedStop()
		{
			return (_stopRequest);
		}
		bool	requestedScene()
		{
			return (_sceneRequest != nullptr);
		}
		std::unique_ptr<Scene>	sceneRequest()
		{
			return (std::move(_sceneRequest));
		}
	protected:
		void	requestStop()
		{
			_stopRequest = true;
		}
		void	requestScene(std::unique_ptr<Scene> scene)
		{
			_sceneRequest = std::move(scene);
		}
		const Engine &_engine;
	private:
		std::unique_ptr<Scene>	_sceneRequest = nullptr;
		bool					_stopRequest = false;
};
