/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:58:29 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 12:11:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include "SDL2/SDL.h"
#include <glad/glad.h>
#include <string>
#include "Math.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <map>

class	Shader
{
	public:
		Shader() {}
		~Shader() {}

		void	use();
		void	load(GLenum type, const std::string &path);
		void	reload()
		{
			unlink();
			for (const auto &file : _files)
				load(file.first, file.second);
			link();
		}
		void	link();
		void	unlink()
		{
			glDeleteProgram(_id);
			_id = 0;
		}
		void	setInt(const std::string &name, int val);
		void	setFloat(const std::string &name, float val);
		void	setVec3(const std::string &name, Vec3 val);
		void	setMat4(const std::string &name, Mat4 val);
	private:
		std::string	_readShader(const std::string &path);
		std::map<GLenum, std::string>	_files;
		uint32_t	_id = 0;
};
