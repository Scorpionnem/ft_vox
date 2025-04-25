/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:15:39 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 14:24:17 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

class	Block
{
	public:
		Block()
		{
			this->_id = "air";
			this->_coords = glm::vec3(0, 0, 0);
			for (int i = 0; i < 6; i++)
				drawFace[i] = true;
		}
		Block(const glm::vec3 &coords, const std::string &id, const std::string &texture)
		{
			this->_id = id;
			this->_coords = coords;
			this->_texture[0] = texture;
			for (int i = 0; i < 6; i++)
				drawFace[i] = true;
		}
		~Block()
		{
			
		}

		void draw(glm::vec3 chunkCoords);

		std::string		_id;
		glm::vec3		_coords;
		std::string		_texture[6];
		bool			drawFace[6];
};
