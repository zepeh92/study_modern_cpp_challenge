/*
가장 많이 사용되는 섭씨, 화씨, Kelvin의 세 가지 온도 스케일을 표현하고 변환할 수 있도록 작 은 라이브러리를 작성하라. 이 라이브러리는 당신이 36.5_deg로 섭씨를, 97.7f로 화씨를, 그리 고 309.65_K로 Kelvin을 온도 문자 표현으로 작성할 수 있게 해야 한며, 이 값들로 연산을 수행 하고 변한을 한다
*/

class temperature
{
public:
	temperature()
	{
	}

	temperature(float cel) :
		cel(cel)
	{
	}

	float to_fahrenheit() const
	{
		return 32 + (1.8f * cel);
	}

	float to_celsius() const
	{
		return cel;
	}

	float to_kelvin() const
	{
		return 273.15f + cel;
	}

	temperature operator+(const temperature& rhs) const
	{
		temperature temp(cel + rhs.cel);
		return temp;
	}

	temperature& operator+=(const temperature& rhs)
	{
		cel += rhs.cel;
		return *this;
	}

	temperature operator-(const temperature& rhs) const
	{
		temperature temp(cel - rhs.cel);
		return temp;
	}

	temperature& operator-=(const temperature& rhs)
	{
		cel -= rhs.cel;
		return *this;
	}

private:

	float cel = 0.0f;
};

temperature operator"" _deg(long double f)
{
	temperature t(static_cast<float>(f));
	return t;
}

temperature operator"" _K(long double f)
{
	temperature t(f - 273.15f);
	return t;
}

temperature operator"" _f(long double f)
{
	const float cel = (f - 32) / 1.8;
	temperature t(cel);
	return t;
}


int main()
{
	auto f = 77.0_f;
	auto k = 373.15_K;
	return 0;
}