/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chrono.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:32:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:50:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>
#include <iostream>
#include <string>

/*
	Simple chrono to get and measure time
*/
class	Chrono
{
	public:
		Chrono() {}
		~Chrono() {}

		void	start()
		{
			_start = getTime();
		}
		// Returns time since chrono was started
		double	get()
		{
			return (getTime() - _start);
		}

		// Returns current time, if you want time since startup use engine.getTime()
		static double getTime()
		{
			double	res;
			struct timespec	current;
			clock_gettime(CLOCK_MONOTONIC, &current);
			res = (current.tv_sec) + (current.tv_nsec) * 1e-9;
			return (res);
		}
	private:
		double		_start = 0;
};
