/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VBO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:45:35 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/26 12:23:28 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_vox.hpp"

class VBO
{
	public:
		template <typename T>
		VBO(T *vertices, GLsizeiptr size)
		{
			glGenBuffers(1, &this->ID);
			glBindBuffer(GL_ARRAY_BUFFER, this->ID);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		}
		VBO()
		{
			ID = 0;
		}
		void free()
		{
			glDeleteBuffers(1, &this->ID);
		}

		unsigned int	getID() const
		{
			return (this->ID);
		}
		void bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->ID);
		}
		void unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	private:
		unsigned int	ID;
};
