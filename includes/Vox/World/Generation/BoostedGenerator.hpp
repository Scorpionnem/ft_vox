/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BoostedGenerator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:41:08 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/18 13:14:41 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Window.hpp"
#include "Chunk.hpp"
#include "ChunkGenerator.hpp"
#include <vector>

class	BoostedGenerator
{
	public:
		BoostedGenerator() {}
		~BoostedGenerator() {}

		void	init(std::shared_ptr<Shader> computeShader)
		{	
			_computeShader = computeShader;
		}
		/*
			gen(std::vector<std::shared_ptr<Chunk>> chunks)
				adds chunks to the queue to be generated.

			update()
				checks if the last compute launched is done, if so, get the buffer data and spread to the right chunks.
		*/
		void	dispatch(std::vector<std::shared_ptr<Chunk>> chunks, ChunkGenerator &generator)
		{
			uint32_t	size = chunks.size();
			uint32_t	*blocks = new uint32_t[size * CHUNK_VOLUME];
			int			*positions = new int[size * 3];
			std::memset(blocks, 0, size * CHUNK_VOLUME * sizeof(uint32_t));

			int	i = 0;
			for (auto chunk : chunks)
			{
				positions[i * 3] = chunk->getPos().x;
				positions[i * 3 + 1] = chunk->getPos().y;
				positions[i * 3 + 2] = chunk->getPos().z;
				i++;
			}

			glCreateBuffers(1, &_chunksBuf);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _chunksBuf);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(uint32_t) * size * CHUNK_VOLUME, blocks, GL_DYNAMIC_DRAW);

			glCreateBuffers(1, &_positionsBuf);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, _positionsBuf);
			glBufferData(GL_SHADER_STORAGE_BUFFER, 3 * sizeof(int) * size, positions, GL_DYNAMIC_DRAW);

			_computeShader->use();

			glDispatchCompute(size, 1, 1);
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _chunksBuf);
			glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(uint32_t) * size * CHUNK_VOLUME, blocks); // function to get data back from the gpu
			glDeleteBuffers(1, &_chunksBuf);

			glDeleteBuffers(1, &_positionsBuf);

			i = 0;
			for (auto chunk : chunks)
			{
				std::vector<uint32_t>	tmp(blocks + i * CHUNK_VOLUME, blocks + i * CHUNK_VOLUME + CHUNK_VOLUME);
				chunk->vectorToChunk(tmp);
				i++;
			}
			delete [] blocks;
			delete [] positions;
			generator.gen(chunks);
		}
	private:
		std::vector<std::shared_ptr<Chunk>>	_tasks;
		std::shared_ptr<Shader>				_computeShader;
		uint								_chunksBuf;
		uint								_positionsBuf;
};
