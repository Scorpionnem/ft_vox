/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VoxScene.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:15:34 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/11 19:03:46 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VoxScene.hpp"
#include "Math.hpp"

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

Vec2	getAtlasUV(Vec2 uv, int textureId)
{
		Vec2	baseUV = uv;

		int row = 15 - (textureId / 16);;
		int col = textureId % 16;

		Vec2 cellSize = Vec2(16.0 / 256.0);
		Vec2 atlasOffset;
		atlasOffset.x = (float)col * cellSize.x;
		atlasOffset.y = (float)row * cellSize.y;
		Vec2 atlasUV;
		atlasUV.x = atlasOffset.x + baseUV.x * cellSize.x;
		atlasUV.y = atlasOffset.y + baseUV.y * cellSize.y;

		return (atlasUV);
}

void	Cube::addFace(std::shared_ptr<Mesh> mesh, Vec3i pos, Direction dir, int textureId)
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

		Face1.v1.uv = getAtlasUV(Face1.v1.uv, textureId);
		Face1.v2.uv = getAtlasUV(Face1.v2.uv, textureId);
		Face1.v3.uv = getAtlasUV(Face1.v3.uv, textureId);

		Face2.v1.uv = getAtlasUV(Face2.v1.uv, textureId);
		Face2.v2.uv = getAtlasUV(Face2.v2.uv, textureId);
		Face2.v3.uv = getAtlasUV(Face2.v3.uv, textureId);

		mesh->addFace("default", Face1);
		mesh->addFace("default", Face2);
	}

void	VoxScene::build()
{
	SDL_ShowCursor(SDL_DISABLE);

	_camera.pos = Vec3d(0, 0, 0);
	_camera.pitch = 0;

	_shader = _engine.loadShader("assets/shaders/core/mesh");
	_targetedBlockShader = _engine.loadShader("assets/shaders/core/targeted_block");

	_world = std::make_unique<World>(_engine.getMeshCache());

	_targetedBlockModel = _engine.getMeshCache().gen();
	Cube::addFace(_targetedBlockModel, Vec3i(0), Cube::Direction::TOP, 0);
	Cube::addFace(_targetedBlockModel, Vec3i(0), Cube::Direction::BOTTOM, 0);
	Cube::addFace(_targetedBlockModel, Vec3i(0), Cube::Direction::NORTH, 0);
	Cube::addFace(_targetedBlockModel, Vec3i(0), Cube::Direction::SOUTH, 0);
	Cube::addFace(_targetedBlockModel, Vec3i(0), Cube::Direction::EAST, 0);
	Cube::addFace(_targetedBlockModel, Vec3i(0), Cube::Direction::WEST, 0);
	_targetedBlockModel->upload();
}

float	getFpsFromArray(void *tab, int id)
{
	return (((float*)tab)[id]);
}

void	VoxScene::update(float delta, const Window::Events &events)
{
	int	windowWidth = _engine.getWindow().width();
	int	windowHeight = _engine.getWindow().height();

	if (events.getKeyPressed(SDLK_LALT))
	{
		_cursorMode = true;
		SDL_ShowCursor(SDL_ENABLE);
	}
	if (events.getKeyReleased(SDLK_LALT))
	{
		_cursorMode = false;
		SDL_ShowCursor(SDL_DISABLE);
	}

	if (!_cursorMode)
		_engine.getWindow().setMousePos(windowWidth / 2, windowHeight / 2);

	if (events.getKey(SDLK_ESCAPE))
		requestStop();

	if (events.getKeyPressed(SDLK_r) && events.getKey(SDLK_LCTRL))
	{
		std::cout << "Reloading shader" << std::endl;
		_shader->reload();
	}
	if (events.getKeyPressed(SDLK_F3))
	{
		if (_lockedFPS)
			SDL_GL_SetSwapInterval(0);
		else
			SDL_GL_SetSwapInterval(1);
		_lockedFPS = !_lockedFPS;
	}
	if (!_cursorMode && events.getMouseBtnPressed(SDL_BUTTON_LEFT))
		_attack();
	if (!_cursorMode && events.getMouseBtnPressed(SDL_BUTTON_RIGHT))
		_interact();

	_updateCamera(delta, events);
	_castRay();

	_world->update(_camera);

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
		ImGui::Text("Loaded chunks: %zu", _world->getLoadedChunks().size());
		ImGui::Text("Visible chunks: %zu", _world->getVisibleChunks().size());
		ImGui::ProgressBar((float)_world->getLoadedChunks().size() / (float)_world->getMaxLoadedChunks());
	}
	ImGui::End();


	worldVec2i	wp(_camera.pos.x, _camera.pos.z);
	float	continentalness = _world->wgen.getNoise("continentalness", wp);
	float	riverness = _world->wgen.getNoise("riverness", wp);
	float	erosion = _world->wgen.getNoise("erosion", wp);
	float	mountainness = _world->wgen.getNoise("mountainness", wp);
	std::string	terrainShape = "Unknown";
	if (isPlains(continentalness, riverness, erosion, mountainness))
		terrainShape = "Plains";
	else if (isRiver(continentalness, riverness, erosion, mountainness))
		terrainShape = "River";
	else if (isShallowOcean(continentalness, riverness, erosion, mountainness))
		terrainShape = "ShallowOcean";
	if (events.getKeyPressed(SDLK_r))
	{
		std::cout << continentalness << " " << riverness << " " << erosion << " " << mountainness << std::endl;
	}


	if (ImGui::Begin("Generation Info", (bool *)__null))
	{
		ImGui::Text("Continental: %.3f Rivers: %.3f Erosion: %.3f Mountains: %.3f", continentalness, riverness, erosion, mountainness);
		ImGui::Text("Terrain Type: %s", terrainShape.c_str());
	}
	ImGui::End();
}

void	VoxScene::_updateCamera(float delta, const Window::Events &events)
{
	float	speed = 50 * delta;
	float	sensitivity = 0.5;

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

	if (!_cursorMode)
	{
		_camera.pitch -= events.getMouseDeltaY() * sensitivity;
		_camera.yaw += events.getMouseDeltaX() * sensitivity;
	}

	_camera.update(delta, _engine.getWindow().aspectRatio());
}

void	moveRay(Vec3i &mapPos, Vec3 &sideDist, const Vec3 &deltaDist, const Vec3i &rayStep)
{
	if (sideDist.x < sideDist.y)
	{
		if (sideDist.x < sideDist.z)
		{
			sideDist.x += deltaDist.x;
			mapPos.x += rayStep.x;
		}
		else
		{
			sideDist.z += deltaDist.z;
			mapPos.z += rayStep.z;
		}
	}
	else
	{
		if (sideDist.y < sideDist.z)
		{
			sideDist.y += deltaDist.y;
			mapPos.y += rayStep.y;
		}
		else
		{
			sideDist.z += deltaDist.z;
			mapPos.z += rayStep.z;
		}
	}
}

void	VoxScene::_attack()
{
	auto chunk = _world->getChunk(_targetedBlock/ CHUNK_SIZE);

	if (_hitBlock && chunk)
	{
		chunk->setBlock(chunk->getLocalPos(_targetedBlock), Blocks::AIR);
		chunk->remesh(_engine.getMeshCache());
		chunk->upload();
	}
}

void	VoxScene::_interact()
{
	auto chunk = _world->getChunk(_prevTargetedBlock / CHUNK_SIZE);

	if (_hitBlock && chunk)
	{
		chunk->setBlock(chunk->getLocalPos(_prevTargetedBlock), Blocks::STONE);
		chunk->remesh(_engine.getMeshCache());
		chunk->upload();
	}
}

void	VoxScene::_castRay()
{
	Vec3	rayDir = _camera.front;
	Vec3	rayPos = _camera.pos;
	Vec3i	mapPos = _camera.pos;
	Vec3i	prevMapPos;
	Vec3	deltaDist = abs(Vec3(length(rayDir)) / rayDir);
	Vec3i	rayStep = Vec3i(sign(rayDir));
	Vec3	sideDist = (sign(rayDir) * (Vec3(mapPos) - rayPos) + (sign(rayDir) * 0.5f) + 0.5f) * deltaDist;

	int	MAX_RAY_STEPS = 8;
	_hitBlock = false;
	for (int i = 0; i < MAX_RAY_STEPS; ++i)
	{
		prevMapPos = mapPos;
		moveRay(mapPos, sideDist, deltaDist, rayStep);
		auto chunk = _world->getChunk(mapPos / CHUNK_SIZE);
		if (!chunk || !chunk->isMeshed())
			continue ;
		if (chunk->getBlock(chunk->getLocalPos(mapPos)) != Blocks::AIR)
		{
			_hitBlock = true;
			break ;
		}
	}
	_targetedBlock = mapPos;
	_prevTargetedBlock = prevMapPos;
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

	_shader->setFloat("horizontalRenderDistance", _world->getHorizontalRenderDistance() * CHUNK_SIZE);
	_shader->setFloat("verticalRenderDistance", _world->getVerticalRenderDistance() * CHUNK_SIZE);

	_shader->setFloat("uTime", _engine.getTime());
	_shader->setVec3("uViewPos", Vec3(0));

	auto chunks = _world->getVisibleChunks();
	for (auto chunk : chunks)
	{
		if (chunk->upload())
			continue ;
		_shader->use();
		_shader->setMat4("uModel", translate(Vec3d(chunk->getPos() * CHUNK_SIZE) - _camera.pos));
		chunk->draw(_shader);
	}

	if (_hitBlock)
	{
		Vec3	blockPos = Vec3d(_targetedBlock) - _camera.pos;
		Vec3	center = Vec3(0.5);

		Mat4	model = translate(blockPos + center) * scale(Vec3(1.01)) * translate(center * -1);

		_targetedBlockShader->use();
		_targetedBlockShader->setMat4("uView", view);
		_targetedBlockShader->setMat4("uProjection", projection);
		_targetedBlockShader->setMat4("uModel", model);
		_targetedBlockShader->setFloat("uTime", _engine.getTime());
		_targetedBlockModel->draw(_targetedBlockShader);
	}

	_engine.getLightCache().draw(view, projection, _camera.pos);
}
