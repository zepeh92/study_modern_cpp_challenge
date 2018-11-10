// 32. ÆÄ½ºÄ® »ï°¢Çü

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class pascal_triangle
{
public:

	void build(int height)
	{
		m_arr.clear();

		m_height = height;

		int total = 0;
		for (int i = 0; i < m_height; ++i)
		{
			total += 1 + (i * 1);
		}
		m_arr.reserve(total);

		m_arr.push_back(1);

		int previdx = 0;
		for (int i = 1; i < m_height; ++i)
		{
			m_arr.push_back(1);
			for (int j = 0; j < i - 1; ++j)
			{
				int idx = previdx + j;
				int sumprev = 0;
				if (idx < m_arr.size())
				{
					sumprev += m_arr[idx];
					if ((idx + 1) < m_arr.size())
					{
						sumprev += m_arr[idx + 1];
					}
				}
				m_arr.push_back(sumprev);
			}
			m_arr.push_back(1);

			previdx += i;
		}
	}

	void print(std::ostream& os)
	{
		const int cnt = m_height;
		const int maxval = m_arr[m_arr.size() - (cnt / 2) - 1];
		const std::streamsize padding = std::to_string(maxval).length();

		int begidx = 0;
		int endidx = 0;
		for (int height = 0; height < m_height; ++height)
		{
			begidx = begidx + height;
			endidx = begidx + height + 1;

			const auto blank = m_height - height + 1;
			for (int i = 0; i < blank; ++i)
			{
				os << setw(padding) << ' ';
			}

			for (int i = begidx; i < endidx; ++i)
			{
				os << setw(padding) << m_arr[i];
				os << setw(padding) << ' ';
			}
			os << endl;
		}
	}

private:

	int m_height = 0;
	std::vector<int> m_arr;
};


int main()
{
	int height = 15;
	cin >> height;
	
	pascal_triangle ptri;
	ptri.build(height);
	ptri.print(std::cout);

	return 0;
}