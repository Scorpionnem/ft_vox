/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 21:44:54 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 11:16:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "SDL2/SDL.h"
#include <glad/glad.h>
#include <stdint.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>

class	Window
{
	public:
		class	Events
		{
			public:
				Events() {}
				~Events() {}

				bool	getKey(int key) const
				{
					auto find = _keys.find(key);
					if (find == _keys.end())
						return (false);
					return (find->second);
				}
				bool	getMouseBtn(int key) const
				{
					auto find = _mouseBtn.find(key);
					if (find == _mouseBtn.end())
						return (false);
					return (find->second);
				}
				bool	getMouseBtnPressed(int key) const
				{
					auto find = _mouseBtnPressed.find(key);
					if (find == _mouseBtnPressed.end())
						return (false);
					return (find->second);
				}
				bool	getMouseBtnLifted(int key) const
				{
					auto find = _mouseBtnLifted.find(key);
					if (find == _mouseBtnLifted.end())
						return (false);
					return (find->second);
				}
				bool	getKeyPressed(int key) const
				{
					auto find = _keysPressed.find(key);
					if (find == _keysPressed.end())
						return (false);
					return (find->second);
				}
				float	getMouseScroll() const {return (_mouseScroll);}
				void	setKey(int key, bool state)
				{
					_keys[key] = state;
				}
				void	setMouseBtn(int key, bool state)
				{
					_mouseBtn[key] = state;
				}
				void	setMouseBtnPressed(int key)
				{
					_mouseBtnPressed[key] = true;
				}
				void	setMouseBtnLifted(int key)
				{
					_mouseBtnLifted[key] = true;
				}
				void	setKeyPressed(int key)
				{
					_keysPressed[key] = true;
				}
				float	getMouseDeltaX() const {return (_mouseDeltaX);}
				float	getMouseDeltaY() const {return (_mouseDeltaY);}
				void	setMouseDeltaX(float val) {_mouseDeltaX = val;}
				void	setMouseDeltaY(float val) {_mouseDeltaY = val;}
				void	setMouseScroll(float val) {_mouseScroll = val;}
				void	reset()
				{
					_mouseDeltaX = 0;
					_mouseDeltaY = 0;
					_mouseScroll = 0;
					_keysPressed.clear();
					_mouseBtnPressed.clear();
					_mouseBtnLifted.clear();
				}
			private:
				float	_mouseDeltaX = 0;
				float	_mouseDeltaY = 0;
				float	_mouseScroll = 0;
				std::map<int, bool>	_keys;
				std::map<int, bool>	_keysPressed;
				std::map<int, bool>	_mouseBtn;
				std::map<int, bool>	_mouseBtnPressed;
				std::map<int, bool>	_mouseBtnLifted;
		};
		void	setMousePos(int x, int y) const
		{
			SDL_WarpMouseInWindow(_window, x, y);
		}
	public:
		Window() {}
		~Window() {}

		void	open(uint32_t width, uint32_t height, const std::string &title);
		void	close();
		void	pollEvents();
		void	display();
		bool	running() {return (_running);}
		float	aspectRatio() const
		{
			return ((float)_width / (float)_height);
		}
		uint32_t	width() const
		{
			return (_width);
		}
		uint32_t	height() const
		{
			return (_height);
		}
		const Events	&getEvents() {return (_events);}
	private:
		Events			_events;
		SDL_Window		*_window = NULL;
		SDL_GLContext	_GLContext;

		bool			_running = true;

		uint32_t			_width = 0;
		uint32_t			_height = 0;

		std::string		_title;
};
