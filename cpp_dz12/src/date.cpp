#include "date.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <cctype>

const uint8_t date::day_in_mon[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

date::date(uint8_t p_mday, uint8_t p_mon, uint16_t p_year)
	: mday(p_mday)
	, mon(p_mon)
	, year(p_year)
{
}

date::date(const date& p_dat)
	: mday(p_dat.mday)
	, mon(p_dat.mon)
	, year(p_dat.year)
{
}

date date::cur()
{
	auto t = time(nullptr);
	tm st;
	gmtime_s(&st, &t);
	date res(st.tm_mday, st.tm_mon, st.tm_year);
	return res;
}

date& date::operator+=(uint32_t p_day)
{
	while (mday + p_day > day_in_mon[mon]) {
		p_day -= day_in_mon[mon] - mday + 1;
		mday = 1;
		if (++mon > 11) {
			++year;
			mon = 0;
		}
	}
	mday += p_day;
	return *this;
}

date date::operator+(uint32_t rhs) const
{
	date tmp = *this;
	return tmp += rhs;
}

bool date::operator==(const date& rhs) const
{
	return rhs.mday == mday && rhs.mon == mon && rhs.year == year;
}

#define tf(date)                                                                                  \
	uint32_t((uint32_t((date).year) << 16) + (uint32_t((date).mon) << 8) + (date).mday)

bool date::operator<(const date& rhs) const
{
	auto a = tf(*this), b = tf(rhs);
	return a < b;
}

#undef tf

std::ostream& operator<<(std::ostream& lhs, const date& rhs)
{
	return lhs << std::setfill('0') << std::setw(4) << rhs.year + 1990 << "-" << std::setw(2)
			   << rhs.mon + 1 << "-" << std::setw(2) << rhs.mday << std::setfill(' ');
}

std::istream& skip_nd(std::istream& is)
{
	char c;
	while (!std::isdigit(c = is.get()) && is)
		;
	is.putback(c);
	return is;
}

std::istream& operator>>(std::istream& lhs, date& rhs)
{
	lhs >> rhs.year >> skip_nd >> rhs.mon >> skip_nd >> rhs.mday;
	rhs.year -= 1990;
	rhs.mon %= 12;
	rhs.mday %= date::day_in_mon[rhs.mon];
	return lhs;
}

std::string std::to_string(const date& p_date) {
	std::string res;
	std::ostringstream r(res);
	r << p_date;
	return res;
}
