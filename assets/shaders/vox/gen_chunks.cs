#version 430

layout (local_size_x = 10) in;

layout(std430, binding = 0) buffer Blocks
{
	uint	blocks[];
};

layout(std430, binding = 1) buffer Positions
{
	ivec3	positions[];
};

#define CHUNK_SIZE 32
#define CHUNK_VOLUME CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE

bool	isInBounds(ivec3 pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE)
		return (false);
	return (true);
}

void	setBlock(ivec3 pos, uint block)
{
	if (!isInBounds(pos))
		return ;

	// Need to ajust to use thread's idx to place it in the right chunk
	int index = pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;

	blocks[index] = block;
}

void	main()
{
	uint id = gl_GlobalInvocationID.x;

	ivec3 chunkPos = positions[id];
}
