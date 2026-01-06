/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 11:18:50 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/03 11:23:11 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>
#include "SDL2/SDL.h"
#include <glad/glad.h>

#include "stb_image.h"

class	Texture
{
	public:
		Texture() {}
		~Texture() {}

		void	load(std::string path)
		{
			int	channels;
			stbi_set_flip_vertically_on_load(true);
			unsigned char *data = stbi_load(path.c_str(), &_width, &_height, &channels, 0);
			if (!data)
				throw std::runtime_error("Failed to load texture " + path);

			_format = GL_RGB;
			if (channels == 1)
				_format = GL_RED;
			else if (channels == 3)
				_format = GL_RGB;
			else if (channels == 4)
				_format = GL_RGBA;

			_pixels = std::vector<unsigned char>(data, data + _width * _height * channels);
		}
		void	upload()
		{
			glGenTextures(1, &_id);

			glBindTexture(GL_TEXTURE_2D, _id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, _pixels.data());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		void	bind(int offset)
		{
			glActiveTexture(GL_TEXTURE0 + offset);
			glBindTexture(GL_TEXTURE_2D, _id);
		}
	private:
		int							_format;
		int							_width;
		int							_height;
		std::vector<unsigned char>	_pixels;
		uint32_t					_id;
};
