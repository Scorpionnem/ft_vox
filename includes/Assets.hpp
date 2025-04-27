/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Assets.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:44:38 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 12:46:55 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class	Assets
{
	public:
		Assets(){}
		void free(){
			for (std::map<std::string, Texture>::iterator it = this->textures.begin(); it != this->textures.end(); it++)
				glDeleteTextures(1, &it->second.ID);
			for (std::map<std::string, Shader>::iterator it = this->shaders.begin(); it != this->shaders.end(); it++)
				glDeleteProgram(it->second.ID);	
		}
		void loadTexture(const std::string &key, const std::string &path)
		{
			std::map<std::string, Texture>::iterator res = this->textures.find(key);
			
			if (res != textures.end())
				return ;

			this->textures.insert(std::make_pair(key, Texture(path.c_str())));
		}
		Texture &getTexture(const std::string &key)
		{
			std::map<std::string, Texture>::iterator res = this->textures.find(key);
			
			if (res == textures.end())
				return (this->textures.find("missing")->second);
			return (res->second);
		}

		void loadAtlasMap(const std::string &key, int id)
		{
			std::map<std::string, int>::iterator res = this->atlasMap.find(key);
			
			if (res != atlasMap.end())
				return ;

			this->atlasMap.insert(std::make_pair(key, id));
		}
		int getAtlasMap(const std::string &key)
		{
			std::map<std::string, int>::iterator res = this->atlasMap.find(key);
			
			if (res == atlasMap.end())
				return (3);
			return (res->second);
		}
		
		void loadShader(const std::string &key, unsigned int ID)
		{
			std::map<std::string, Shader>::iterator res = this->shaders.find(key);
			
			if (res != shaders.end())
				return ;

			this->shaders.insert(std::make_pair(key, Shader(ID)));
		}
		Shader getShader(const std::string &key)
		{
			std::map<std::string, Shader>::iterator res = this->shaders.find(key);
			
			if (res == shaders.end())
				return (0);
			return (res->second.ID);
		}
	private:
		std::map<std::string, Texture>	textures;
		std::map<std::string, int>		atlasMap;
		std::map<std::string, Shader>	shaders;
};

void	loadAssets();

extern Assets	assets;
