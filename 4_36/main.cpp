// 36. 특정 날짜보다 오래된 파일들을 지우기
/*
	auto next = it;
	++next; 하면 기존의 it까지 변경된다.
*/

#include <filesystem>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std::filesystem;

void remove_recursively(directory_iterator it, const filesystem::file_time_type::clock::time_point& point)
{
	if (it == directory_iterator()) return;

	std::filesystem::file_time_type fileTime = last_write_time(*it);
	if (fileTime.time_since_epoch() < point.time_since_epoch())
	{
		if (it->is_directory())
		{
			remove_all(*it);
		}
		else
		{
			remove(*it);
		}
	}
	else if(it->is_directory())
	{
		remove_recursively(directory_iterator(it->path()), point);
	}
	remove_recursively(++it, point);
}

void remove(const path& path, milliseconds ms)
{
	auto fpoint = filesystem::file_time_type::clock::now() + ms;
	remove_recursively(directory_iterator(path), fpoint);
}

int main()
{
	remove(path{R"(C:\Users\Jeon PilGyu\Desktop\asdasd)"}, +10s);
	return 0;
}