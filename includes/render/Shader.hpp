/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:17:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/26 11:22:23 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

class Shader
{
	public:
		unsigned int	ID;

		Shader(unsigned int ID);
		Shader(const char *vertexPath, const char *fragmentPath);

		void	use();
		void	setBool(const std::string &name, bool value) const;
		void	setInt(const std::string &name, int value) const;
		void	setFloat(const std::string &name, float value) const;
		void	setMat4(const std::string &name, glm::mat4 value) const;
		void	setVec3(const std::string &name, glm::vec3 value) const;
};
