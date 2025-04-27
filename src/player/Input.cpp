/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:56:22 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 14:15:18 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "World.hpp"

bool		isTyping = false;
bool		ignoreNext = false;
std::string	playerInput;

void	special_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;(void)key;(void)scancode;(void)action;(void)mods;
	if (action == GLFW_PRESS)
	{
		if (isTyping)
		{
			if (key == GLFW_KEY_BACKSPACE && playerInput.size())
				playerInput.pop_back();
			if (key == GLFW_KEY_ENTER)
			{
				use_input();
				isTyping = false;
				playerInput.clear();
			}
		}
		else
		{
			if (key == GLFW_KEY_T)
			{
				isTyping = true;
				ignoreNext = true;
			}
			else if (key == GLFW_KEY_SLASH)
				isTyping = true;
		}
	}
}

void	char_callback(GLFWwindow *window, unsigned int codepoint)
{
	(void)window;
	if (isTyping && !ignoreNext)
	{
		if (codepoint >= 32 && codepoint <= 126)
			playerInput += (char)codepoint;
		std::cout << playerInput << "_" << std::endl;
	}
	ignoreNext = false;
}

void	use_input()
{
	std::istringstream	iss(playerInput);
	std::string	command;

	iss >> command;
	if (command == "/tp")
	{
		int x, y, z;
		if (iss >> x >> y >> z)
		{
			pos.x = x;
			pos.y = y;
			pos.z = z;
		}
		else
			std::cout << "/tp, wrong input" << std::endl;
	}
	if (command == "/setblock")
	{
		int x, y, z;
		if (iss >> x >> y >> z)
			world.setBlock(x, y, z, false);
		else
			std::cout << "/setblock, wrong input" << std::endl;
	}
	if (command == "/getblock")
	{
		int x, y, z;
		if (iss >> x >> y >> z)
			std::cout << world.getBlock(x, y, z) << std::endl;
		else
			std::cout << "/getblock, wrong input" << std::endl;
	}
	std::cout << "Command: " << command << std::endl;
}
