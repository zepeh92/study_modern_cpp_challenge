/*
60. The Game of Life
Write a program that implements the Game of Life cellular automaton proposed by John Horton Conway. The universe of this game is a grid of square cells that could have one of two states: dead or alive. Every cell interacts with its adjacent neighbors, with the following transactions occurring on every step:
* Any live cell with fewer than two live neighbors dies, as if caused by under-population
* Any live cell with two or three live neighbors lives on to the next generation
* Any live cell with more than three live neighbors dies, as if by overpopulation
* Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction
The status of the game on each iteration should be displayed on the console, and for convenience, you should pick a reasonable size, such as 20 rows x 50 columns.

*/

#include <iostream>
#include <sstream>
#include <vector>
#include <random>

#include "cell.h"
#include "game_map.h"

using namespace std;

class game
{
public:

	game(int row, int col) :
		m_row(row), m_col(col),
		m_mapFront(row, col),
		m_mapBack(row, col)
	{
	}

	void init()
	{
		m_mapFront.init();
		m_mapBack.init();
		m_renderbuf.clear();
		m_renderbuf.reserve(m_row * m_col);

		std::random_device rd;
		std::mt19937 mt(rd());

		cell_state states[]{
			cell_state::nil,
			cell_state::live,
			cell_state::dead,
		};

		std::uniform_int_distribution<> rng(0, sizeof(states) / sizeof(cell_state) - 1);

		m_mapFront.for_each([&](int col, int row, cell& c) {
			const int idx = rng(mt);
			c.state = states[idx];
		});

		m_mapBack = m_mapFront;
	}

	void update()
	{
		m_mapFront.for_each([&](int col, int row, cell& c){

			*m_mapBack.get_cell(col, row) = c;

			if (c.state == cell_state::live)
			{
				const int liveCount = m_mapFront.get_near_cell_count(col, row, cell_state::live);

				if (liveCount < 2 || 3 < liveCount)
				{// dead
					m_mapBack.get_cell(col, row)->state = cell_state::dead;
				}
			}
			else if(c.state == cell_state::dead)
			{
				const int liveCount = m_mapFront.get_near_cell_count(col, row, cell_state::live);

				if (liveCount == 3)
				{
					m_mapBack.get_cell(col, row)->state = cell_state::live;
				}
			}
		});

		m_mapFront = m_mapBack;
	}

	void render()
	{
		m_renderbuf.clear();
		
		for (int row = 0; row != m_row; ++row)
		{
			for (int col = 0; col != m_col; ++col)
			{
				char c;
				switch (m_mapFront.get_cell(col, row)->state)
				{
				case cell_state::dead:
					c = 'X';
					break;
				case cell_state::live:
					c = 'O';
					break;
				case cell_state::nil:
					c = ' ';
					break;
				default:
					c = 'E';
					break;
				}
				m_renderbuf += c;
			}
			m_renderbuf += '\n';
		}

		system("cls");

		cout << m_renderbuf;
		
		const int liveCellCount = m_mapFront.count_all(cell_state::live);
		const int deadCellCount = m_mapFront.count_all(cell_state::dead);

		printf("live: %d, dead: %d\n", liveCellCount, deadCellCount);
	}

private:

	game_map m_mapFront;
	game_map m_mapBack;
	int m_row = 10;
	int m_col = 10;
	string m_renderbuf;
};

int main()
{
	game g(10, 20);
	
	g.init();

	while (true)
	{
		g.update();
		g.render();
	}

	return 0;
}