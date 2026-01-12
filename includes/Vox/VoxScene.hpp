/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VoxScene.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:13:58 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/12 17:15:48 by mbatty           ###   ########.fr       */
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
		void	_attack();
		void	_interact();
		void	_castRay();
		void	_drawChunks(std::shared_ptr<Shader> shader, Mat4 view, Mat4 proj);
		void	_drawSelectedBlock(std::shared_ptr<Shader> shader, Mat4 view, Mat4 proj);

		std::shared_ptr<Shader>	_shader;

		Camera	_camera;
		std::unique_ptr<World>	_world;
		std::shared_ptr<Light>	_light;
		std::vector<float>		_fpss;

		bool	_cursorMode = false;
		bool	_lockedFPS = true;

		worldVec3i	_targetedBlock;
		// The block before targetedBlock hit
		worldVec3i	_prevTargetedBlock;
		bool		_hitBlock = false;

		std::shared_ptr<Mesh>	_targetedBlockModel;
		std::shared_ptr<Shader>	_targetedBlockShader;

		uint	_FBO;
		std::shared_ptr<Mesh>	_frameMesh;
		std::shared_ptr<Shader>	_postProcessShader;
		uint	_RBO;
		uint	_FBOTexture;

		uint	_shadowFBO;
		uint	_shadowFBOTexture;
		std::shared_ptr<Shader>	_shadowShader;
		
		bool	focus = false;
};
