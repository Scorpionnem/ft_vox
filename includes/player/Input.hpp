/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:59:23 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 13:16:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

extern bool 		isTyping;
extern std::string	playerInput;

void	char_callback(GLFWwindow *window, unsigned int codepoint);
void	use_input();
void	special_callback(GLFWwindow *window, int key, int scancode, int action, int mods);