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

uint seed = 42;

vec2 randomGradient(int ix, int iy)
{
	uint w = 8 * 4;
	uint s = w / 2;
	uint a = ix;
	uint b = iy;
	a *= 3284157443 + (seed + 1);

	b ^= a << s | a >> (w - s);
	b *= 1911520717;

	a ^= b << s | b >> (w - s);
	a *= 2048419325;
	float random = (float(a) / float(4294967295)) * 2.0f * 3.14159f;

	vec2 v;
	v.x = sin(random);
	v.y = cos(random);

	return v;
}

float dotGridGradient(int ix, int iy, float x, float y)
{
	vec2 gradient = randomGradient(ix, iy);

	float dx = x - float(ix);
	float dy = y - float(iy);

	return (dx * gradient.x + dy * gradient.y);
}

float interpolate(float a0, float a1, float w)
{
	return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float perlin2D(float x, float y)
{
	int x0 = int(floor(x));
	int y0 = int(floor(y));
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	float sx = x - float(x0);
	float sy = y - float(y0);

	float n0 = dotGridGradient(x0, y0, x, y);
	float n1 = dotGridGradient(x1, y0, x, y);
	float ix0 = interpolate(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	float ix1 = interpolate(n0, n1, sx);

	float value = interpolate(ix0, ix1, sy);

	return (value);
}

float	calcNoise(ivec2 pos, float freq, float amp, int noisiness)
{
	float	res = 0;
	for (int i = 0; i < noisiness; i++)
	{
		res += perlin2D(float(pos.x) * freq, float(pos.y) * freq) * amp;

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

void	main()
{
	uint id = gl_GlobalInvocationID.x;

	ivec3 chunkPos = positions[id];

	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
			for (int y = 0; y < CHUNK_SIZE; y++)
				if (y < calcNoise(ivec2(x, z), 0.01, 1, 1) * 100)
					setBlock(ivec3(x, y, z), 1, id);
}
