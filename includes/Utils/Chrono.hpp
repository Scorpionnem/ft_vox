/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chrono.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:32:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/05 20:38:02 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>
#include <iostream>
#include <string>

class	Chrono
{
	public:
		Chrono(const std::string id)
		{
			_id = id;
			_start = getTime();
		}
		double	get()
		{
			return (getTime() - _start);
		}
		~Chrono()
		{
			std::cout << _id << " time: " << get() << std::endl;
		}
		static double getTime()
		{
			double	res;
			struct timespec	current;
			clock_gettime(CLOCK_MONOTONIC, &current);
			res = (current.tv_sec) + (current.tv_nsec) * 1e-9;
			return (res);
		}
	private:
		double		_start;
		std::string	_id;
};
