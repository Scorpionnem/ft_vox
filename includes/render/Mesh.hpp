/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:42:05 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/26 14:40:32 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec2 texOffset;
};

enum class FaceDirection {
    Top,
    Bottom,
    Left,
    Right,
    Front,
    Back
};

class Mesh
{
	public:
		std::vector<Vertex>	vertices;
		std::vector<unsigned int> indices;

		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;

		Mesh(){
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);			
			glGenBuffers(1, &EBO);
		}

		void addFace(const glm::vec3& bottomLeft, const glm::vec3& bottomRight, const glm::vec3& topRight, const glm::vec3& topLeft, const glm::vec3& normal, glm::vec2 baseUV) {
			unsigned int startIndex = vertices.size();
		
			Vertex	tmp;
			tmp.normal = normal;
			tmp.texOffset = baseUV;

			tmp.position = bottomLeft;
			tmp.texCoords = glm::vec2(0.0f, 0.0f);
			vertices.push_back(tmp);
			
			tmp.position = bottomRight;
			tmp.texCoords = glm::vec2(1.0f, 0.0f);
			vertices.push_back(tmp);

			tmp.position = topRight;
			tmp.texCoords = glm::vec2(1.0f, 1.0f);
			vertices.push_back(tmp);
			
			tmp.position = topLeft;
			tmp.texCoords = glm::vec2(0.0f, 1.0f);
			vertices.push_back(tmp);
		
			indices.push_back(startIndex);
			indices.push_back(startIndex + 1);
			indices.push_back(startIndex + 2);
		
			indices.push_back(startIndex);
			indices.push_back(startIndex + 2);
			indices.push_back(startIndex + 3);
		}
		void addFace(const glm::vec3& blockPosition, FaceDirection dir, glm::vec2 atlasCoord) {
			glm::vec3 bottomLeft, bottomRight, topRight, topLeft, normal;
		
			float x = blockPosition.x;
			float y = blockPosition.y;
			float z = blockPosition.z;
		
			switch (dir) {
				case FaceDirection::Top:
					bottomRight  = glm::vec3(x,     y + 1, z);
					bottomLeft = glm::vec3(x + 1, y + 1, z);
					topLeft    = glm::vec3(x + 1, y + 1, z + 1);
					topRight     = glm::vec3(x,     y + 1, z + 1);
					normal      = glm::vec3(0, 1, 0);
					break;
		
				case FaceDirection::Bottom:
					bottomLeft  = glm::vec3(x,     y, z);
					bottomRight = glm::vec3(x + 1, y, z);
					topRight    = glm::vec3(x + 1, y, z + 1);
					topLeft     = glm::vec3(x,     y, z + 1);
					normal      = glm::vec3(0, -1, 0);
					break;
		
				case FaceDirection::Left:
					bottomLeft  = glm::vec3(x, y,     z);
					bottomRight = glm::vec3(x, y,     z + 1);
					topRight    = glm::vec3(x, y + 1, z + 1);
					topLeft     = glm::vec3(x, y + 1, z);
					normal      = glm::vec3(-1, 0, 0);
					break;
		
				case FaceDirection::Right:
					bottomRight  = glm::vec3(x + 1, y,     z);
					bottomLeft = glm::vec3(x + 1, y,     z + 1);
					topLeft    = glm::vec3(x + 1, y + 1, z + 1);
					topRight     = glm::vec3(x + 1, y + 1, z);
					normal      = glm::vec3(1, 0, 0);
					break;
		
				case FaceDirection::Front:
					bottomLeft  = glm::vec3(x,     y, z + 1);
					bottomRight = glm::vec3(x + 1, y, z + 1);
					topRight    = glm::vec3(x + 1, y + 1, z + 1);
					topLeft     = glm::vec3(x,     y + 1, z + 1);
					normal      = glm::vec3(0, 0, 1);
					break;
		
				case FaceDirection::Back:
					bottomRight  = glm::vec3(x,     y, z);
					bottomLeft = glm::vec3(x + 1, y, z);
					topLeft    = glm::vec3(x + 1, y + 1, z);
					topRight     = glm::vec3(x,     y + 1, z);
					normal      = glm::vec3(0, 0, -1);
					break;
			}
			float texSize = 1.0 / 16.0f;
			
			glm::vec2 baseUV = atlasCoord * texSize;
		
			// Now reuse the basic face adder:
			addFace(bottomLeft, bottomRight, topRight, topLeft, normal, baseUV);
		}
		void	upload(){
			glBindVertexArray(VAO);
		
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		
			// Position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);
		
			// Normal
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(1);
		
			// TexCoords
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
			glEnableVertexAttribArray(2);
		
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texOffset));
			glEnableVertexAttribArray(3);

			glBindVertexArray(0);
		}
		void draw() {
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
};
