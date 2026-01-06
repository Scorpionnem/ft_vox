/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkGenerator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:31:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/05 13:58:23 by mbatty           ###   ########.fr       */
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

		void	start(uint32_t workers)
		{
			for (uint32_t i = 0; i < workers; ++i)
				_workers.emplace_back(std::bind(&ChunkGenerator::_generatorWorker, this));
			std::cout << "Started generation threads" << std::endl;
		}
		void	stop()
		{
			std::unique_lock<std::mutex> latch(_queue_mutex);
			_stop = true;
			_cv_task.notify_all();
			latch.unlock();

			for (auto& thread : _workers)
				thread.join();
			std::cout << "Stopped generation threads" << std::endl;
		}
		void	gen(std::shared_ptr<Chunk> chunk)
		{
			std::unique_lock<std::mutex> lock(_queue_mutex);
			_tasks.emplace_back(chunk);
			_cv_task.notify_one();
		}
	private:
		void	_generatorWorker()
		{
			while (true)
			{
				std::unique_lock<std::mutex> latch(_queue_mutex);
				_cv_task.wait(latch, [this](){ return _stop || !_tasks.empty(); });
				if (!_stop && !_tasks.empty())
				{
					std::shared_ptr<Chunk>	chunk = _tasks.front();
					_tasks.pop_front();

					latch.unlock();

					chunk->generate();
					chunk->genMesh(_cache);

					latch.lock();
				}
				else if (_stop)
					break ;
			}
		}

		std::vector<std::thread>			_workers;
		std::deque<std::shared_ptr<Chunk>>	_tasks;
		std::mutex							_queue_mutex;
		std::condition_variable 			_cv_task;
		std::atomic_bool					_stop = false;
		MeshCache 							&_cache;
};
