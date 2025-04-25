/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:45:19 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 13:16:01 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

class VAO
{
	public:
		VAO()
		{
			glGenVertexArrays(1, &this->ID);
		}
		void free()
		{
			glDeleteVertexArrays(1, &this->ID);
		}
		
		void attribInt(VBO &vbo, GLuint layout, GLuint nbComponents, GLenum type, GLsizeiptr stride, void *offset)
		{
			vbo.bind();
			glVertexAttribPointer(layout, nbComponents, type, GL_FALSE, stride, offset);
			glEnableVertexAttribArray(layout);
			vbo.unbind();
		}
		void attribFloat(VBO &vbo, GLuint layout, GLuint nbComponents, GLenum type, GLsizeiptr stride, void *offset)
		{
			vbo.bind();
			glVertexAttribPointer(layout, nbComponents, type, GL_FALSE, stride, offset);
			glEnableVertexAttribArray(layout);
			vbo.unbind();
		}

		void bind()
		{
			glBindVertexArray(this->ID);
		}
		void unbind()
		{
			glBindVertexArray(0);
		}
		unsigned int	getID() const
		{
			return (this->ID);
		}
	private:
		unsigned int	ID;
};