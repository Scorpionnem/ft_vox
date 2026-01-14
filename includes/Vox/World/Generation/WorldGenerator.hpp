/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldGenerator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:35:35 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/14 17:56:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define CONTINENTALNESS_SPLINE_PATH "assets/generation/splines.json"

#include "Spline.hpp"
#include <fstream>
#include <unordered_map>
#include <string>
#include "Math.hpp"

/*
	Uses min/max values of a set of points in a world
*/

inline bool isRiver(float cont, float river, float erosion, float mountain)
{
	float	minCont = -0.336806;
	float	maxCont = 0.208036;

	float	minRiver = 0.0;
	float	maxRiver = 0.0109034;

	float	minErosion = 0.000566016;
	float	maxErosion = 0.40052;

	float	minMountain = 0.000783141;
	float	maxMountain = 0.39734;
	return
		cont >= minCont && cont <= maxCont &&
		river >= minRiver && river <= maxRiver &&
		erosion >= minErosion && erosion <= maxErosion &&
		mountain >= minMountain && mountain <= maxMountain;
}

inline bool isPlains(float cont, float river, float erosion, float mountain)
{
	float	minCont = -0.120821;
	float	maxCont = 0.197561;

	float	minRiver = 0.0344283;
	float	maxRiver = 0.523291;

	float	minErosion = 0.00056894;
	float	maxErosion = 0.137739;

	float	minMountain = 0.00178662;
	float	maxMountain = 0.364877;
	return
		cont >= minCont && cont <= maxCont &&
		river >= minRiver && river <= maxRiver &&
		erosion >= minErosion && erosion <= maxErosion &&
		mountain >= minMountain && mountain <= maxMountain;
}

inline bool isShallowOcean(float cont, float river, float erosion, float mountain)
{
	float	minCont = -0.560036;
	float	maxCont = 0.098303;

	float	minRiver = 0.0339143;
	float	maxRiver = 0.241044;

	float	minErosion = 0.00537582;
	float	maxErosion = 0.387939;

	float	minMountain = 0.0118302;
	float	maxMountain = 0.421158;
	return
		cont >= minCont && cont <= maxCont &&
		river >= minRiver && river <= maxRiver &&
		erosion >= minErosion && erosion <= maxErosion &&
		mountain >= minMountain && mountain <= maxMountain;
}

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

		float	getSplineValue(const std::string &id, Vec2i pos) const
		{
			auto find = _splines.find(id);
			if (find == _splines.end())
				return (0);

			const Spline	&spline = find->second;

			float noise = Noise::calcNoise(pos, spline.freq, spline.amp, spline.noisiness);
			if (spline.abs)
				noise = std::abs(noise);
			return (getValueInSpline(spline, noise));
		}
		float	getNoise(const std::string &id, Vec2i pos) const
		{
			auto find = _splines.find(id);
			if (find == _splines.end())
				return (0);

			const Spline	&spline = find->second;

			float noise = Noise::calcNoise(pos, spline.freq, spline.amp, spline.noisiness);
			if (spline.abs)
				noise = std::abs(noise);
			return (noise);
		}
	private:
		std::unordered_map<std::string, Spline>	_splines;
};
