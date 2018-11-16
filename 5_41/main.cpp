// 41. 날짜가 주어지면 요일을 출력하는 함수

#include <iostream>
#include <string>
#include <sstream>

enum class day_of_week : int
{
	none = 0,
	monday = 1,
	tuesday = 2,
	wednesday = 3,
	thusday = 4,
	friday = 5,
	saturday = 6,
	sunday = 7,
};

class datetime
{
public:

	datetime()
	{
	}

	datetime(int years, int months, int days, int hour, int min, int sec) :
		years(years), months(months), days(days), hours(hour), mins(min), secs(sec)
	{
	}

	std::string to_string() const
	{
		std::stringstream ss;
		ss << std::to_string(years);
		ss << '-';
		ss << std::to_string(months);
		ss << '-';
		ss << std::to_string(days) << ' ';
		ss << hours << ':' << mins << ':' << secs << ' ' << to_string(get_day_of_week());
		return ss.str();
	}

	day_of_week get_day_of_week() const
	{
		const int dow = get_total_days() % 7;
		return static_cast<day_of_week>(dow == 0 ? 7 : dow);
	}

	int get_total_days(int startYear = 1990) const
	{
		int totalDays = 0;
		for (int i = startYear; i < years; ++i)
		{
			totalDays += is_leap_year(i) ? 366 : 365;
		}

		const bool leap = is_leap_year(years);

		for (int i = 1; i < months; ++i)
		{
			totalDays += month_total_days(i, leap);
		}
		totalDays += days;

		return totalDays;
	}

private:

	std::string to_string(day_of_week dow) const
	{
		switch (dow)
		{
		case day_of_week::sunday: return "sun";
		case day_of_week::monday: return "mon";
		case day_of_week::tuesday: return "tue";
		case day_of_week::wednesday: return "wed";
		case day_of_week::thusday: return "thu";
		case day_of_week::friday: return "fri";
		case day_of_week::saturday: return "sat";
		}
		return "?";
	}

	int month_total_days(int months, bool isLeap) const
	{
		constexpr int month_days[]{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (months == 2 && isLeap) ? 29 : month_days[months - 1];
	}

	bool is_leap_year(int years) const
	{
		return ((years % 4 == 0) && (years % 100 != 0)) || (years % 400 == 0);
	}

	int years = 1990;
	int months = 1;
	int days = 1;
	int hours = 0;
	int mins = 0;
	int secs = 0;
};

int main()
{
	using namespace std;

	datetime dt(2018, 11, 16, 7, 40, 0);
	int totalDays = dt.get_total_days();
	day_of_week dow = dt.get_day_of_week();

	cout << dt.to_string() << endl;
	cout << totalDays << endl;

	return 0;
}