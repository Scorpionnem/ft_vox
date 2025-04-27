/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:15:39 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/27 12:52:36 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

extern float cube_vertices[];
#include "Chunk.hpp"

class	Block
{
	public:
		Block()
		{
			this->_id = "air";
			this->_coords = glm::vec3(0, 0, 0);
		}
		Block(const glm::vec3 &coords, const std::string &id, const std::string &texture)
		{
			this->_id = id;
			this->_coords = coords;
			textures.insert(std::make_pair(FaceDirection::Top, texture));
		}
		~Block()
		{
			
		}

		glm::vec2	getTexture(FaceDirection face);
		void draw(glm::vec3 chunkCoords);

		std::string		_id;
		glm::vec3		_coords;
		std::map<FaceDirection, std::string>	textures;
};
