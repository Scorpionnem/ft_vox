/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:51:52 by mbatty            #+#    #+#             */
/*   Updated: 2025/04/26 11:15:22 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vox.hpp"

class	Texture
{
	public:
		Texture(const char *path);
		Texture(const Texture &cpy);
		Texture	&operator=(const Texture &cpy);
		void	bind()
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ID);
		}
		unsigned int	ID;
	private:
		unsigned char	*data;
		int width;
		int height;
		int nrChannels;
};
