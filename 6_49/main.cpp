/*
49. Text histogram
Write a program that, given a text, determines and prints a histogram with the frequency of each letter of the alphabet. 
The frequency is the percentage of the number of appearances of each letter from the total count of letters. 
The program should count only the appearances of letters and ignore digits, signs, and other possible characters. 
The frequency must be determined based on the count of letters and not the text size.
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <regex>

using namespace std;

vector<pair<string, int>> get_histogram(string text)
{
	for (auto& ch : text)
	{
		if (!isalpha(ch))
		{
			ch = ' ';
		}
	}

	map<string, int> m;
	
	string key;
	size_t start = 0;
	size_t end = text.find(' ');
	while(end != string::npos)
	{
		key.assign(&text[start], end - start);
		if (!key.empty())
		{
			m[key] += 1;
		}
		start = end + 1;
		end = text.find(' ', start);
	}
	if (start < text.size())
	{
		key.assign(&text[start]);
		m[key] += 1;
	}
	
	vector<pair<string, int>> strs;
	strs.reserve(m.size());
	
	transform(m.begin(), m.end(), back_inserter(strs), [](const auto& elem) {
		return std::make_pair(elem.first, elem.second);
	});

	sort(strs.begin(), strs.end(), [](const auto& a, const auto& b) {
		return b.second < a.second;
	});
	
	return strs;
}

int main()
{
	string text{
R"(
49. Text histogram
Write a program that, given a text, determines and prints a histogram with the frequency of each letter of the alphabet. 
The frequency is the percentage of the number of appearances of each letter from the total count of letters. 
The program should count only the appearances of letters and ignore digits, signs, and other possible characters. 
The frequency must be determined based on the count of letters and not the text size.
)"
	};

	for (auto&& [letter, count] : get_histogram(text))
	{
		cout << letter << ": " << count << endl;
	}

	return 0;
}