/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:51:41 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/17 16:13:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

void	Window::open(uint32_t width, uint32_t height, const std::string &title)
{
	_width = width;
	_height = height;
	_title = title;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw (std::runtime_error(SDL_GetError()));

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height,
				SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!_window)
	{
		SDL_Quit();
		throw (std::runtime_error(SDL_GetError()));
	}

	_GLContext = SDL_GL_CreateContext(_window);
	if (!_GLContext)
	{
		SDL_DestroyWindow(_window);
		SDL_Quit();
		throw (std::runtime_error(SDL_GetError()));
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		SDL_GL_DeleteContext(_GLContext);
		SDL_DestroyWindow(_window);
		SDL_Quit();
		throw (std::runtime_error("Failed to initialize GLAD"));
	}

	glViewport(0, 0, _width, _height);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CW);

	// glEnable(GL_MULTISAMPLE);

	SDL_GL_SetSwapInterval(1);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(_window, _GLContext);
	ImGui_ImplOpenGL3_Init();


	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void	Window::close()
{
	SDL_GL_DeleteContext(_GLContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void	Window::pollEvents()
{
	SDL_Event	event;

	_events.reset();
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				_running = false;
				break ;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					_width = event.window.data1;
					_height = event.window.data2;

					glViewport(0, 0, _width, _height);
				}
				break ;
			case SDL_KEYDOWN:
				_events.setKey(event.key.keysym.sym, true);
				_events.setKeyPressed(event.key.keysym.sym);
				break ;
			case SDL_KEYUP:
				_events.setKey(event.key.keysym.sym, false);
				_events.setKeyReleased(event.key.keysym.sym);
				break ;
			case SDL_MOUSEMOTION:
				_events.setMouseDeltaX(event.motion.xrel);
				_events.setMouseDeltaY(event.motion.yrel);
				break ;
			case SDL_MOUSEBUTTONDOWN:
				_events.setMouseBtn(event.button.button, true);
				_events.setMouseBtnPressed(event.button.button);
				break ;
			case SDL_MOUSEBUTTONUP:
				_events.setMouseBtn(event.button.button, false);
				_events.setMouseBtnLifted(event.button.button);
				break ;
			case SDL_MOUSEWHEEL:
				_events.setMouseScroll(event.wheel.y);
				break ;
		}
	}
}

void	Window::display()
{
	SDL_GL_SwapWindow(_window);
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
