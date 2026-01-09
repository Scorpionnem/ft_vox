/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldGenerator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:35:35 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/09 15:22:47 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define CONTINENTALNESS_SPLINE_PATH "assets/generation/splines.json"

#include "Spline.hpp"
#include <fstream>
#include <unordered_map>
#include <string>
#include "Math.hpp"

class	WorldGenerator
{
	public:
		WorldGenerator() {}
		~WorldGenerator() {}

		void	load()
		{
			std::ifstream	file(CONTINENTALNESS_SPLINE_PATH);
			if (!file.is_open())
				throw std::runtime_error("Failed to load generation splines");

			json	data;

			try {
				data = json::parse(file);
			} catch (const std::exception &e) {
				throw std::runtime_error("Failed to parse " + std::string(CONTINENTALNESS_SPLINE_PATH));
			}

			for (auto &[name, spline] : data.items())
				_splines.insert(std::make_pair(name, spline.get<Spline>()));
		}

		void	reload()
		{
			_splines.clear();
			load();
		}

		float	getNoise(const std::string &id, Vec2i pos)
		{
			Spline	&spline = _splines[id];

			float noise = Perlin2D::calcNoise(pos, spline.freq, spline.amp, spline.noisiness);
			if (spline.abs)
				noise = std::abs(noise);
			return (getValueInSpline(spline, noise));
		}
	private:
		std::unordered_map<std::string, Spline>	_splines;
};
