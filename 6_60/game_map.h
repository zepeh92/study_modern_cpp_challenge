#pragma once

#include <vector>

class game_map
{
public:

	game_map(int row, int col) :
		m_row(row), m_col(col)
	{
	}

	game_map(const game_map& rhs)
	{
		*this = rhs;
	}

	void init()
	{
		m_cells.clear();
		m_cells.resize(m_row * m_col);
	}

	template < typename Func >
	void for_each(Func&& func)
	{
		for (int row = 0; row != m_row; ++row)
		{
			for (int col = 0; col != m_col; ++col)
			{
				func(col, row, *get_cell(col, row));
			}
		}
	}

	int count_all(cell_state countingState)
	{
		int count = 0;
		for_each([&count, countingState](int x, int y, const cell_state& state)
		{
			if (countingState == state)
			{
				++count;
			}
		});
		return count;
	}

	int get_near_cell_count(int x, int y, cell_state state) const
	{
		const cell_state* nearCells[]
		{
			get_cell(x - 1, y - 1),
			get_cell(x,			y - 1),
			get_cell(x + 1, y - 1),
			get_cell(x - 1, y),
			get_cell(x + 1, y),
			get_cell(x - 1,	y + 1),
			get_cell(x,			y + 1),
			get_cell(x + 1,	y + 1)
		};

		int count = 0;
		for (const cell_state* nearCell : nearCells)
		{
			if (nearCell)
			{
				if (*nearCell == state)
				{
					++count;
				}
			}
		}
		return count;
	}

	const cell_state* get_cell(int x, int y) const
	{
		const int idx = y * m_row + x;
		return 0 <= idx && idx < m_cells.size() ? &m_cells[idx] : nullptr;
	}

	cell_state* get_cell(int x, int y)
	{
		return const_cast<cell_state*>(static_cast<const game_map*>(this)->get_cell(x, y));
	}

	game_map& operator=(const game_map& rhs)
	{
		m_row = rhs.m_row;
		m_col = rhs.m_col;
		m_cells = rhs.m_cells;

		return *this;
	}

private:

	int m_row;
	int m_col;
	std::vector<cell_state> m_cells;
};