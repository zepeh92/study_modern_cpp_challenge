// 34. 텍스트 파일에서 공백 제거

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		return 1;
	}

	fs::path path = argv[1];
	fs::path tempPath = path;
	tempPath += ".temp";

	ifstream ifs(path);
	ofstream ofs(tempPath);

	if (ifs.is_open() && ofs.is_open())
	{
		ifs >> noskipws;

		string line;
		if (!ifs.eof())
		{
			while (true)
			{
				ifs >> line;
				ofs << line;
				if (ifs.eof()) break;
				ofs << endl;
			}
		}

		ifs.close();
		ofs.close();

		std::error_code err;
		fs::remove(path, err);
		fs::rename(tempPath, path, err);
	}
	
	return 0;
}