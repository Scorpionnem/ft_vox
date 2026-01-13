/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkGenerator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:31:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:39:56 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <atomic>
#include <deque>
#include <functional>
#include <condition_variable>

#include "Chunk.hpp"

/*
	@brief Handles the thread pool used for chunk generation.
*/
class	ChunkGenerator
{
	public:
		ChunkGenerator(MeshCache &cache) : _cache(cache) {}
		~ChunkGenerator() {}

		void	start(uint32_t workers);
		void	stop();
		// Adds the chunk to the generation queue
		void	gen(std::shared_ptr<Chunk> chunk);
		// Adds the chunks to the generation pool in 1 mutex lock
		void	gen(std::vector<std::shared_ptr<Chunk>> chunks);
		// Updates the position used to sort and tells a thread to sort the chunks
		void	sort(Vec3 pos);
	private:
		void	_generatorWorker();

		std::deque<std::shared_ptr<Chunk>>	_tasks;
		std::condition_variable 			_cv_task;
		std::mutex							_queue_mutex;

		std::vector<std::thread>			_workers;

		std::atomic_bool					_stop = false;

		std::atomic_bool					_sort = false;
		Vec3								_camPos;

		MeshCache 							&_cache;
};
