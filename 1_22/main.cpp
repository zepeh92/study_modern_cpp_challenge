/*
���� ���� ���Ǵ� ����, ȭ��, Kelvin�� �� ���� �µ� �������� ǥ���ϰ� ��ȯ�� �� �ֵ��� �� �� ���̺귯���� �ۼ��϶�. �� ���̺귯���� ����� 36.5_deg�� ������, 97.7f�� ȭ����, �׸� �� 309.65_K�� Kelvin�� �µ� ���� ǥ������ �ۼ��� �� �ְ� �ؾ� �Ѹ�, �� ����� ������ ���� �ϰ� ������ �Ѵ�
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