/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EBO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:05:20 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/26 12:23:02 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

class EBO
{
	public:
		template <typename T>
		EBO(const T *indices, GLsizeiptr size)
		{
			glGenBuffers(1, &this->ID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
		}
		EBO(){
			ID = 0;
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
