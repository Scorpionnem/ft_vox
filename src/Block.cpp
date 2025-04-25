/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Block.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:17:29 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 16:18:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

std::vector<glm::vec3>		vertex;
std::vector<unsigned int>	indices;

void Block::draw(glm::vec3 chunkCoords)
{
	if (this->_id == "air" || glm::distance(pos, _coords + chunkCoords * 16.0f) > 160)
		return ;
	
	Shader(assets.getShader("block")).use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->_coords + chunkCoords * 16.0f);
	Shader(assets.getShader("block")).setMat4("model", model);

	glBindTexture(GL_TEXTURE_2D, assets.getTexture(this->_texture[0]).ID);	
	
	// glDrawArrays(GL_TRIANGLES, 0, 36);
	for (int i = 0; i < 6; i++)
		if (drawFace[i])
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *) (i * 6 * sizeof(GLuint)));
}
