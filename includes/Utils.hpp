/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:43:48 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 13:06:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//Init
GLFWwindow	*initWindow(void);
int	convertIndex(int x, int y, int z);
glm::vec2	getAtlasOffset(int HorizontalOffset, int VerticalOffset);
std::string	format_coords(glm::vec3 coords);
