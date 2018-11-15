// 37. 정규표현식에 맞는 파일들을 디렉토리에서 찾기

#include <iostream>
#include <regex>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

vector<fs::path> get_match_pathes(const fs::path& entry, const wregex& reg, bool recursively = true)
{
	const auto begin = fs::directory_iterator(entry);
	const auto end = fs::directory_iterator();

	std::vector<fs::path> pathes;
	std::wcmatch match;
	
	for (auto i = begin; i != end; ++i)
	{
		const auto name = i->path().filename();
		if (std::regex_match(name.c_str(), match, reg))
		{
			pathes.emplace_back(*i);
		}

		if (i->is_directory() && recursively)
		{
			const auto subdir = get_match_pathes(*i, reg, recursively);
			pathes.insert(pathes.end(), subdir.begin(), subdir.end());
		}
	}

	pathes.shrink_to_fit();

	return pathes;
}

int main()
{
	fs::path path = R"(C:\Users\Jeon PilGyu\Desktop\dev)";
	wregex reg{ LR"(F.*)" };
	for (auto&& path : get_match_pathes(path, reg))
	{
		cout << path << endl;
	}
	
	return 0;
}