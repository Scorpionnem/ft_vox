/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkGenerator.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:05:17 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/10 16:09:01 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChunkGenerator.hpp"

void	ChunkGenerator::gen(std::shared_ptr<Chunk> chunk)
{
	std::unique_lock<std::mutex> lock(_queue_mutex);
	_tasks.emplace_back(chunk);
	_cv_task.notify_one();
}

void	ChunkGenerator::start(uint32_t workers)
{
	for (uint32_t i = 0; i < workers; ++i)
		_workers.emplace_back(std::bind(&ChunkGenerator::_generatorWorker, this));
	std::cout << "Started generation threads" << std::endl;
}

void	ChunkGenerator::stop()
{
	std::unique_lock<std::mutex> latch(_queue_mutex);
	_stop = true;
	_cv_task.notify_all();
	latch.unlock();

	for (auto& thread : _workers)
		thread.join();
	std::cout << "Stopped generation threads" << std::endl;
}

void	ChunkGenerator::_generatorWorker()
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
			chunk->mesh(_cache);

			latch.lock();
		}
		else if (_stop)
			break ;
	}
}
