/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VoxScene.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:15:34 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/07 21:45:23 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VoxScene.hpp"
#include "Math.hpp"

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

void	Cube::addFace(std::shared_ptr<Mesh> mesh, Vec3i pos, Direction dir)
	{
		Mesh::Face	Face1;
		Mesh::Face	Face2;

		switch (dir)
		{
			case Direction::NORTH:
				Face1 = NORTH_FACE1;
				Face2 = NORTH_FACE2;
				break ;
			case Direction::SOUTH:
				Face1 = SOUTH_FACE1;
				Face2 = SOUTH_FACE2;
				break ;
			case Direction::EAST:
				Face1 = EAST_FACE1;
				Face2 = EAST_FACE2;
				break ;
			case Direction::WEST:
				Face1 = WEST_FACE1;
				Face2 = WEST_FACE2;
				break ;
			case Direction::TOP:
				Face1 = TOP_FACE1;
				Face2 = TOP_FACE2;
				break ;
			case Direction::BOTTOM:
				Face1 = BOTTOM_FACE1;
				Face2 = BOTTOM_FACE2;
				break ;
		}
		Face1.v1.pos = Face1.v1.pos + pos;
		Face1.v2.pos = Face1.v2.pos + pos;
		Face1.v3.pos = Face1.v3.pos + pos;

		Face2.v1.pos = Face2.v1.pos + pos;
		Face2.v2.pos = Face2.v2.pos + pos;
		Face2.v3.pos = Face2.v3.pos + pos;
		mesh->addFace("default", Face1);
		mesh->addFace("default", Face2);
	}

void	VoxScene::build()
{
	_camera.pos = Vec3d(0, 0, 0);
	_camera.pitch = 0;

	_shader = _engine.loadShader("assets/shaders/core/mesh");
}

float	getFpsFromArray(void *tab, int id)
{
	return (((float*)tab)[id]);
}

void	VoxScene::update(float delta, const Window::Events &events)
{
	// int	windowWidth = _engine.getWindow().width();
	// int	windowHeight = _engine.getWindow().height();

	// if (events.getMouseBtn(SDL_BUTTON_LEFT))
	// 	_engine.getWindow().setMousePos(windowWidth / 2, windowHeight / 2);

	if (events.getKey(SDLK_ESCAPE))
		requestStop();

	if (events.getKeyPressed(SDLK_r) && events.getKey(SDLK_LCTRL))
	{
		std::cout << "Reloading shader" << std::endl;
		_shader->reload();
	}

	_updateCamera(delta, events);

	_world.update(_camera);

	static double lastFpsUpdate = 0;
	static double lastMinMaxFpsUpdate = 0;
	static double maxFPS = 0;
	static double minFPS = 0;

	double FPS = 1.0 / delta;

	if (_engine.getTime() - lastFpsUpdate > 0.1)
	{
		_fpss.push_back(FPS);
		if (_fpss.size() > 16)
			_fpss.erase(_fpss.begin());
		lastFpsUpdate = _engine.getTime();
	}
	if (_engine.getTime() - lastMinMaxFpsUpdate > 1)
	{
		lastMinMaxFpsUpdate = _engine.getTime();
		minFPS = FPS;
		maxFPS = FPS;
	}

	if (FPS > maxFPS)
		maxFPS = FPS;
	if (FPS < minFPS)
		minFPS = FPS;

	if (ImGui::Begin("Scene Info", (bool *)__null))
	{
		ImGui::Text("FPS: %.3f Min: %.3f Max: %.3f", FPS, minFPS, maxFPS);
		ImGui::PlotLines("FPS Graph", getFpsFromArray, (void*)_fpss.data(), _fpss.size(), 0, __null, 50, 70, ImVec2(180, 48));
		ImGui::Text("Time: %.3f", _engine.getTime());
		ImGui::Text("Loaded chunks: %zu", _world.getLoadedChunks().size());
		ImGui::Text("Visible chunks: %zu", _world.getVisibleChunks().size());
		ImGui::ProgressBar((float)_world.getLoadedChunks().size() / (float)_world.getMaxLoadedChunks());
	}
	ImGui::End();
}

void	VoxScene::_updateCamera(float delta, const Window::Events &events)
{
	float	speed = 50 * delta;
	// float	sensitivity = 0.3;

	if (events.getKey(SDLK_w))
		_camera.pos = _camera.pos + _camera.front * speed;
	if (events.getKey(SDLK_s))
		_camera.pos = _camera.pos - _camera.front * speed;
	if (events.getKey(SDLK_SPACE))
		_camera.pos = _camera.pos + _camera.up * speed;
	if (events.getKey(SDLK_LSHIFT))
		_camera.pos = _camera.pos - _camera.up * speed;
	if (events.getKey(SDLK_a))
		_camera.pos = _camera.pos - normalize(cross(_camera.front, _camera.up)) * speed;
	if (events.getKey(SDLK_d))
		_camera.pos = _camera.pos + normalize(cross(_camera.front, _camera.up)) * speed;
	if (events.getKey(SDLK_UP))
		_camera.pitch += speed * 2;
	if (events.getKey(SDLK_DOWN))
		_camera.pitch -= speed * 2;
	if (events.getKey(SDLK_RIGHT))
		_camera.yaw += speed * 2;
	if (events.getKey(SDLK_LEFT))
		_camera.yaw -= speed * 2;

	// if (events.getMouseBtnPressed(SDL_BUTTON_LEFT))
	// 	SDL_ShowCursor(SDL_DISABLE);
	// if (events.getMouseBtnLifted(SDL_BUTTON_LEFT))
	// 	SDL_ShowCursor(SDL_ENABLE);
	// if (events.getMouseBtn(SDL_BUTTON_LEFT))
	// {
	// 	_camera.pitch -= events.getMouseDeltaY() * sensitivity;
	// 	_camera.yaw += events.getMouseDeltaX() * sensitivity;
	// }

	_camera.update(_engine.getWindow().aspectRatio());
}

void	VoxScene::display()
{
	Mat4	model(1);
	Mat4	view = _camera.getViewMatrix();
	Mat4	projection = perspective(70, _engine.getWindow().aspectRatio(), 0.01, 1000);

	_engine.getLightCache().setUniforms(_shader, _camera.pos);

	_shader->use();
	_shader->setMat4("uView", view);
	_shader->setMat4("uProjection", projection);

	_shader->setFloat("horizontalRenderDistance", _world.getHorizontalRenderDistance() * CHUNK_SIZE);
	_shader->setFloat("verticalRenderDistance", _world.getVerticalRenderDistance() * CHUNK_SIZE);

	_shader->setFloat("uTime", _engine.getTime());
	_shader->setVec3("uViewPos", Vec3(0));

	auto chunks = _world.getVisibleChunks();
	for (auto chunk : chunks)
	{
		if (chunk->upload())
			continue ;
		_shader->use();
		_shader->setMat4("uModel", translate(Vec3d(chunk->_pos * CHUNK_SIZE) - _camera.pos));
		chunk->draw(_shader);
	}

	_engine.getLightCache().draw(view, projection, _camera.pos);
}
