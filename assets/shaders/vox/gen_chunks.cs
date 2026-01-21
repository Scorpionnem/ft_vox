#version 430

layout (local_size_x = 1) in;

layout(std430, binding = 0) buffer Blocks
{
	uint	blocks[];
};

layout(std430, binding = 1) buffer Positions
{
	int	positions[];
};

uint seed = 42;

float	randVec3ToFloat(vec3 pos, vec3 dotDir = vec3(12.9898, 78.233, 37.719))
{
	vec3 smallValue = sin(pos);
	float random = dot(smallValue, dotDir);
	random = fract(sin(random) * 143758.5453);
	return (random);
}

float randVec2ToFloat(vec2 value, vec2 dotDir = vec2(12.9898, 78.233))
{
	vec2 smallValue = sin(value);
	float random = dot(smallValue, dotDir);
	random = fract(sin(random) * 143758.5453);
	return (random);
}

float hash(vec2 p)
{
	return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453);
}

float perlin2D(vec2 p)
{
	vec2 i = floor(p);
	vec2 f = fract(p);

	float a = hash(i);
	float b = hash(i + vec2(1.0, 0.0));
	float c = hash(i + vec2(0.0, 1.0));
	float d = hash(i + vec2(1.0, 1.0));

	vec2 u = f * f * (3.0 - 2.0 * f);

	return (mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y);
}

float	calcNoise(vec2 pos, float freq, float amp, int noisiness)
{
	float	res = 0;
	for (int i = 0; i < noisiness; i++)
	{
		res += perlin2D(vec2(pos.x * freq, pos.y * freq)) * amp;

		freq *= 2;
		amp /= 2;
	}

	res = clamp(res, -1.0f, 1.0f);

	return (res);
}

#define CHUNK_SIZE 32
#define CHUNK_VOLUME CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE

bool	isInBounds(ivec3 pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.z < 0 || pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE || pos.z >= CHUNK_SIZE)
		return (false);
	return (true);
}

void	setBlock(ivec3 pos, uint block, uint id)
{
	if (!isInBounds(pos))
		return ;

	uint index = id * CHUNK_VOLUME + pos.x + pos.y * CHUNK_SIZE + pos.z * CHUNK_SIZE * CHUNK_SIZE;

	blocks[index] = block;
}

vec3	worldPos(vec3 pos, ivec3 chunkPos)
{
	return (pos + chunkPos * CHUNK_SIZE);
}

void	main()
{
	uint idx = gl_GlobalInvocationID.x;

	ivec3 chunkPos = ivec3(positions[idx * 3], positions[idx * 3 + 1], positions[idx * 3 + 2]);

	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				vec3	wp = worldPos(vec3(x, y, z), chunkPos);

				if (wp.y < calcNoise(vec2(wp.x, wp.z), 0.00125, 1, 6) * 100)
					setBlock(ivec3(x, y, z), 1, idx);
			}
}
