/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:30:52 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 12:25:56 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

void	getMouseRealPos(GLFWwindow* window, double *width, double *height, double xpos, double ypos)
{
	int	wwidth;
	int	wheight;
	
	glfwGetWindowSize(window, &wwidth, &wheight);
	(*width) = xpos / wwidth * 2 - 1;
	(*height) = (wheight - ypos) / wheight * 2 - 1;
}

int	convertIndex(int x, int y, int z)
{
	return (x + z * 16 + y * 16 * 16);
}

glm::vec2	getAtlasOffset(int HorizontalOffset, int VerticalOffset)
{
	return (glm::vec2((float)HorizontalOffset * 4.0, (float)VerticalOffset * 4.0));
}

void display_fps(GLFWwindow	*window, struct timeval start_time, int target_fps)
{
    struct timeval        end_time;
    int                    start;
    int                    end;

    gettimeofday(&end_time, NULL);
    start = start_time.tv_sec;
    end = end_time.tv_sec;
    while (abs(end - start + 1) > target_fps)
    {
        gettimeofday(&end_time, NULL);
        end = end_time.tv_sec;
    }
    gettimeofday(&end_time, NULL);
    end = end_time.tv_sec;

	std::stringstream	strs;
	strs << 1000000 / abs(end - start + 1) << " fps";

	glfwSetWindowTitle(window, strs.str().c_str());
}

std::string	format_coords(glm::vec3 coords)
{
	std::stringstream	strs;

	strs << (int)coords.x << "|" << (int)coords.y << "|" << (int)coords.z;
	return (strs.str());
}
