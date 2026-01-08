/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldGenerator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:35:35 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/08 22:45:01 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define CONTINENTALNESS_SPLINE_PATH "assets/generation/splines.json"

#include "Spline.hpp"
#include <fstream>

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

			if (data.contains("continentalness"))
				_continentalness = data["continentalness"].get<Spline>();

			if (data.contains("peaks_valleys"))
				_peaksValleys = data["peaks_valleys"].get<Spline>();
		}

		void	reload()
		{
			_continentalness.points.clear();
			_peaksValleys.points.clear();
			load();
		}

		float	getContinentalnessFreq() {return (_continentalness.freq);}
		int	getContinentalnessAmp() {return (_continentalness.amp);}
		int	getContinentalnessNoisiness() {return (_continentalness.noisiness);}
		float	getContinentalness(float val) {return (getValueInSpline(_continentalness, val));}
		float	getPeaksValleys(float val) {return (getValueInSpline(_peaksValleys, val));}
	private:
		Spline	_continentalness;
		Spline	_peaksValleys;
};
