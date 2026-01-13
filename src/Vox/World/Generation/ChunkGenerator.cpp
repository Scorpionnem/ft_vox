/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkGenerator.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:05:17 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/13 13:53:39 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChunkGenerator.hpp"

void	ChunkGenerator::gen(std::shared_ptr<Chunk> chunk)
{
	std::unique_lock<std::mutex> lock(_queue_mutex);
	_tasks.emplace_back(chunk);
	_cv_task.notify_one();
}

void	ChunkGenerator::gen(std::vector<std::shared_ptr<Chunk>> chunks)
{
	std::unique_lock<std::mutex> lock(_queue_mutex);
	for (auto chunk : chunks)
		_tasks.emplace_back(chunk);
	_cv_task.notify_all();
}

void	ChunkGenerator::sort(Vec3 pos)
{
	std::unique_lock<std::mutex> lock(_queue_mutex);
	_sort = true;
	_camPos = pos;
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
		_cv_task.wait(latch, [this](){ return (_stop || !_tasks.empty()); }); // Waits until it is notified (using _cv_task.notify_*) and the lambda returns true
		if (!_stop && !_tasks.empty())
		{
			if (_sort)
			{
				std::sort(_tasks.begin(), _tasks.end(),
				[this](std::shared_ptr<Chunk> c1, std::shared_ptr<Chunk> c2)
				{
					return (dist(_camPos, (c1->getPos() * CHUNK_SIZE) + CHUNK_SIZE / 2) < dist(_camPos, (c2->getPos() * CHUNK_SIZE) + CHUNK_SIZE / 2));
				});
				_sort = false;
			}

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
