// 35. 디렉토리 크기 계산하기

#include <filesystem>
#include <iostream>
#include <numeric>

using namespace std;
namespace fs = std::filesystem;

size_t get_dir_size(fs::path path, bool sym = false)
{
	return std::accumulate(
		fs::directory_iterator(path), fs::directory_iterator(),
		static_cast<size_t>(0), [](size_t v, const fs::directory_entry& entry) {
		if (entry.is_symlink()) 
			return v + get_dir_size(fs::read_symlink(entry));
		else if (entry.is_directory())
			return v + get_dir_size(entry);
		return v + entry.file_size();
	});
}

int main(int argc, char* argv[])
{
	fs::path path{ argc < 2 ? "./" : argv[1] };
	
	const size_t totalBytes = get_dir_size(path);
	
	cout << totalBytes << "bytes";

	return 0;
}