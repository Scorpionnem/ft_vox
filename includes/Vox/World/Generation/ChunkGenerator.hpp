/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkGenerator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:31:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/07 16:06:29 by mbatty           ###   ########.fr       */
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

class	ChunkGenerator
{
	public:
		ChunkGenerator(MeshCache &cache) : _cache(cache) {}
		~ChunkGenerator() {}

		void	start(uint32_t workers);
		void	stop();
		void	gen(std::shared_ptr<Chunk> chunk);
	private:
		void	_generatorWorker();

		std::vector<std::thread>			_workers;
		std::deque<std::shared_ptr<Chunk>>	_tasks;
		std::mutex							_queue_mutex;
		std::condition_variable 			_cv_task;
		std::atomic_bool					_stop = false;
		MeshCache 							&_cache;
};
