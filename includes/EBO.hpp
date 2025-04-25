/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EBO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:05:20 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/25 14:05:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

class EBO
{
	public:
		EBO(const unsigned int *indices, GLsizeiptr size)
		{
			glGenBuffers(1, &this->ID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
		}

		GLuint getId() const
		{
			return (this->ID);
		}
		void bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
		}
		void unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		void free()
		{
			glDeleteBuffers(1, &this->ID);
		}
	private:
		GLuint ID;
};
