///////////////////////////////////////////////////////////////////////////////
// File: main.cpp
// Date: 29.02.2020
// Version: 1
// Author: Christian Steinbrecher
// Description: Runs Game of Life
///////////////////////////////////////////////////////////////////////////////

#include "Flower.h"

#include "ParticleRenderer.h"
#include "DynamicPointRenderObject.h"
#include "Array3DShader.h"

#include <iostream>
#include <thread>
#include <limits>
#include <chrono>
#include <numeric>
#include <vector>
#include <execution>

using namespace std;


using ShaderType = Array3DShader<eShader::Pong>;
using RenderObj = DynamicPointRenderObject<ShaderType>;
using Vertices = std::vector<RenderObj::Vertex>;

size_t const N = 128;
Flower field1[N][N][N];
Flower field2[N][N][N];
Vertices fieldVertices1(N* N* N);

void createVertices(Flower field[N][N][N], Vertices& fieldVertices)
{
	if (fieldVertices.size() < N * N * N)
	{
		return;
	}

	size_t i = 0;
	for (size_t z = 0; z < N; ++z)
	{
		for (size_t y = 0; y < N; ++y)
		{
			for (size_t x = 0; x < N; ++x)
			{
				fieldVertices[i++].color = field[z][y][x].getColor();
			}
		}
	}
}


Flower::Neighbours getNeighbours(Flower field[N][N][N], size_t const z, size_t const y, size_t const x)
{
	Flower::Neighbours neighbours =
	{
		&field[z+1][y][x],
		&field[z-1][y][x],
		&field[z][y+1][x],
		&field[z][y-1][x],
		&field[z][y][x +1],
		&field[z][y][x-1],
	};

	return neighbours;
}

void gameOfLife(Flower current[N][N][N], Flower next[N][N][N])
{
	std::vector<size_t> range(N-2);
	std::iota(range.begin(), range.end(), 1);
	std::for_each(std::execution::par_unseq, range.cbegin(), range.cend(), [&](auto z)
		{
			for (size_t y = 1; y < N - 1; ++y)
			{
				for (size_t x = 1; x < N - 1; ++x)
				{
					auto const neighbours = getNeighbours(current, z, y, x);
					Flower thisFlower = current[z][y][x];
					thisFlower.changeState(neighbours, 1.0);
					next[z][y][x] = thisFlower;
				}
			}
		});
}

int main()
{
	auto current = field1;
	auto next = field2;

	//for (size_t z = 0; z < N; ++z)
	//{
	//	for (size_t y = 0; y < N; ++y)
	//	{
	//		for (size_t x = 0; x < N; ++x)
	//		{
	//			field1[z][N / 2][N / 2].setAlive(true);
	//			field1[z][N / 2][N / 2].setEnergy(-99);
	//		}
	//	}
	//}


	for (size_t z = 1; z < N - 1; ++z)
	{
		for (size_t y = 1; y < N - 1; ++y)
		{
			for (size_t x = 1; x < N - 1; ++x)
			{
				field1[z][y][N/2].setAlive(true);
				field1[z][y][N / 2].setEnergy(0);
			}
		}
	}

	// init
	/*field1[N / 2 - 3][N / 2][N / 2].setAlive(true);
	field1[N / 2 - 3][N / 2][N / 2].setEnergy(100);

	field1[N / 2 - 2][N / 2][N / 2].setAlive(true);
	field1[N / 2 - 2][N / 2][N / 2].setEnergy(0);

	field1[N / 2 - 1][N / 2][N / 2].setAlive(true);
	field1[N / 2 - 1][N / 2][N / 2].setEnergy(0);

	field1[N / 2][N / 2][N / 2].setAlive(true);
	field1[N / 2][N / 2][N / 2].setEnergy(0);

	field1[N / 2+1][N / 2][N / 2].setAlive(true);
	field1[N / 2+1][N / 2][N / 2].setEnergy(0);

	field1[N / 2+2][N / 2][N / 2].setAlive(true);
	field1[N / 2+2][N / 2][N / 2].setEnergy(0);

	field1[N / 2 + 3][N / 2][N / 2].setAlive(true);
	field1[N / 2 + 3][N / 2][N / 2].setEnergy(0);



	field1[N / 2 - 3][N / 2+1][N / 2].setAlive(true);
	field1[N / 2 - 3][N / 2 + 1][N / 2].setEnergy(100);

	field1[N / 2 - 2][N / 2 + 1][N / 2].setAlive(true);
	field1[N / 2 - 2][N / 2 + 1][N / 2].setEnergy(0);

	field1[N / 2 - 1][N / 2 + 1][N / 2].setAlive(true);
	field1[N / 2 - 1][N / 2 + 1][N / 2].setEnergy(0);

	field1[N / 2][N / 2 + 1][N / 2].setAlive(true);
	field1[N / 2][N / 2 + 1][N / 2].setEnergy(0);

	field1[N / 2 + 1][N / 2 + 1][N / 2].setAlive(true);
	field1[N / 2 + 1][N / 2 + 1][N / 2].setEnergy(0);

	field1[N / 2 + 2][N / 2 + 1][N / 2].setAlive(true);
	field1[N / 2 + 2][N / 2 + 1][N / 2].setEnergy(0);

	field1[N / 2 + 3][N / 2 + 1][N / 2].setAlive(true);
	field1[N / 2 + 3][N / 2 + 1][N / 2].setEnergy(0);



	field1[N / 2 - 3][N / 2 - 1][N / 2].setAlive(true);
	field1[N / 2 - 3][N / 2 - 1][N / 2].setEnergy(100);

	field1[N / 2 - 2][N / 2 - 1][N / 2].setAlive(true);
	field1[N / 2 - 2][N / 2 - 1][N / 2].setEnergy(0);

	field1[N / 2 - 1][N / 2 - 1][N / 2].setAlive(true);
	field1[N / 2 - 1][N / 2 - 1][N / 2].setEnergy(0);

	field1[N / 2][N / 2 - 1][N / 2].setAlive(true);
	field1[N / 2][N / 2 - 1][N / 2].setEnergy(0);

	field1[N / 2 + 1][N / 2 - 1][N / 2].setAlive(true);
	field1[N / 2 + 1][N / 2 - 1][N / 2].setEnergy(0);

	field1[N / 2 + 2][N / 2 - 1][N / 2].setAlive(true);
	field1[N / 2 + 2][N / 2 - 1][N / 2].setEnergy(0);

	field1[N / 2 + 3][N / 2 - 1][N / 2].setAlive(true);
	field1[N / 2 + 3][N / 2 - 1][N / 2].setEnergy(0);*/

	current[1][1][N / 2].setEnergy(1);

	// physik
	bool end = false;
	size_t maxN = N / 2;
	auto physik = [&]()
	{
		//current[N / 2][N / 2][N / 2].setEnergy(1);

		gameOfLife(current, next);
		auto tmp = current;
		current = next;
		next = tmp;

		//current[N-2][N-2][N/2].setEnergy(1);
		
		//current[1][2][N / 2].setEnergy(1);
		//current[1][3][N / 2].setEnergy(1);
		//current[1][4][N / 2].setEnergy(1);
		//current[1][N - 2][N / 2].setEnergy(1);
		//current[N - 2][1][N / 2].setEnergy(1);
		//current[1][1][N / 2].setEnergy(1);

		current[N / 2][N / 2][N / 2].setEnergy(0);
		createVertices(current, fieldVertices1);
		//cout << std::to_string(current[N / 2 - 3][N / 2][N / 2].getEnergy()) << " ";
		//cout << std::to_string(current[N / 2 - 2][N / 2][N / 2].getEnergy()) << " ";
		//cout << std::to_string(current[N / 2 - 1][N / 2][N / 2].getEnergy()) << " ";
		//cout << std::to_string(current[N / 2][N / 2][N / 2].getEnergy()) << " ";
		//cout << std::to_string(current[N / 2 + 1][N / 2][N / 2].getEnergy()) << " ";
		//cout << std::to_string(current[N / 2 + 2][N / 2][N / 2].getEnergy()) << " ";
		//cout << std::to_string(current[N / 2 + 3][N / 2][N / 2].getEnergy()) << " ";

		//static int count = 0;
		//cout << count++;
		//cout << endl;
	};


	// render
	createVertices(current, fieldVertices1);
	auto app = ParticleRenderer::createVulkan();
	auto obj = RenderObj::createVulkan();

	auto render = [&]() -> Vertices
	{
		typedef std::chrono::high_resolution_clock Time;
		typedef std::chrono::duration<float> fsec;
		static auto t0 = Time::now();
		auto t1 = Time::now();
		fsec fs = t1 - t0;
		float count = fs.count() * 0.2f;

		//float const x = N / 2 + (3 * maxN + 10);// *sin(count);
		////float const y = N / 2 + (3 * maxN + 10);// *cos(count);
		//float const y = 50;
		//float const z = N / 2.0f + (3.0f * maxN + 10.0f) / 2.0f + (maxN / 2.0f);// *sin(count * 0.7f);;

		float const x = N * 1.7f;
		float const y = N / 2;
		float const z = N / 2;


		app->setView({ x, y, z }, { N / 2, N / 2, N / 2 });

		return fieldVertices1;
	};

	obj->setVertices(render, fieldVertices1.size());
	obj->setPosition({ 0.0f, 0.0f, 0.0f });
	ShaderType::UniformBufferObject ubo;
	ubo.maxIndex = glm::uvec3(N, N, N);
	obj->setUbo(ubo);

	app->add(std::move(obj));

	// start
	float const x = N / 2.0f + (3.0f * maxN + 10.0f) * sin(0.0f);
	float const y = N / 2.0f + (3.0f * maxN + 10.0f) * cos(0.0f);
	float const z = N / 2.0f + (3.0f * maxN + 10.0f) / 2.0f + (maxN / 2.0f) * sin(0 * 0.7f);;
	app->setView({ x, y, z }, { N / 2, N / 2, N / 2 });
	app->setWindowSize(3440, 1440, true);

	thread phyisk = thread([&]()
		{
			while (!end)
			{
				typedef std::chrono::high_resolution_clock Time;
				typedef std::chrono::duration<float> fsec;
				static auto t0 = Time::now();
				auto t1 = Time::now();
				fsec fs = t1 - t0;

				//if (fs > 0.05s)
				{
					t0 = Time::now();
					physik();
				}
			}
		});

	app->run();

	end = true;
	phyisk.join();
}
