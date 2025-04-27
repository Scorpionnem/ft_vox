/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hooks.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:41:04 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 13:13:32 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

void resize_hook(GLFWwindow* window, int width, int height);
void	key_hook(GLFWwindow *window);
void	move_mouse_hook(GLFWwindow* window, double xpos, double ypos);
