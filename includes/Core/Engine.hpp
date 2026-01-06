/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:42:51 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/05 20:32:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>
#include "Scene.hpp"
#include "MeshCache.hpp"
#include "TextureCache.hpp"
#include "ShaderCache.hpp"
#include "LightCache.hpp"

class	Engine
{
	public:
		Engine() : _textures(this), _meshes(this), _shaders(this), _lights(this) {}
		~Engine() {}
		void	start(std::unique_ptr<Scene> scene);

		TextureCache	&getTextureCache() const {return (_textures);}
		MeshCache		&getMeshCache() const {return (_meshes);}
		ShaderCache		&getShaderCache() const {return (_shaders);}
		LightCache		&getLightCache() const {return (_lights);}

		std::shared_ptr<Mesh>	loadMesh(const std::string &path) const {return (_meshes.get(path));}
		std::shared_ptr<Shader>	loadShader(const std::string &path) const {return (_shaders.get(path));}

		const Window	&getWindow() const {return (_window);}

		// Time since engine.start was called
		double getTime() const
		{
			double	res;

			struct timespec	current;

			clock_gettime(CLOCK_MONOTONIC, &current);
			res = (current.tv_sec) + (current.tv_nsec) * 1e-9;
			return (res - _startTime);
		}
	private:
		void	_loop();
		std::unique_ptr<Scene>	_scene;
		Window	_window;
		mutable TextureCache	_textures;
		mutable MeshCache		_meshes;
		mutable ShaderCache		_shaders;
		mutable LightCache		_lights;

		struct timespec	_lastFrame = {0, 0};
		double	_startTime = 0;
};
