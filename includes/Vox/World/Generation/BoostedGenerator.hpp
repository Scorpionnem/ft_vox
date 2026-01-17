/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BoostedGenerator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:41:08 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/17 21:20:06 by mbatty           ###   ########.fr       */
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
			(void)chunks;
			uint32_t	size = chunks.size();
			uint32_t	*blocks = new uint32_t[chunks.size() * CHUNK_VOLUME];
			std::memset(blocks, 0, chunks.size() * CHUNK_VOLUME * sizeof(uint32_t));

			/*
				Need to have 2 buffers, 1 to store all the blocks and 1 to store all the positions of chunks (in the same order)

				when the compute is started, it will take its idx and from it take the right chunk position and offset in the blocks
			*/
			glCreateBuffers(1, &_chunksBuf);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _chunksBuf);
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(uint32_t) * size * CHUNK_VOLUME, blocks, GL_DYNAMIC_DRAW);

			_computeShader->use();

			_computeShader->setInt("chunksCount", 1);

			glDispatchCompute(size, 1, 1);
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _chunksBuf);
			glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(uint32_t) * size * CHUNK_VOLUME, blocks); // function to get data back from the gpu
			glDeleteBuffers(1, &_chunksBuf);

			int	i = 0;
			for (auto chunk : chunks)
			{
				std::vector<uint32_t>	tmp(blocks + i * CHUNK_VOLUME, blocks + i * CHUNK_VOLUME + CHUNK_VOLUME);
				chunk->vectorToChunk(tmp);
				i++;
			}
			delete [] blocks;
			generator.gen(chunks);
		}
	private:
		std::vector<std::shared_ptr<Chunk>>	_tasks;
		std::shared_ptr<Shader>				_computeShader;
		uint								_chunksBuf;
};
