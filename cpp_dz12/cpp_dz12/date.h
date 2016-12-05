#pragma once

#include <cstdint>
#include <iostream>
#include <string>

struct date {
	uint8_t mday;
	uint8_t mon;
	uint16_t year;

	date(uint8_t p_mday = 0, uint8_t p_mon = 1, uint16_t p_year = 0);
	date(const date& p_dat);
	static date cur();
	bool operator==(const date& rhs) const;
	bool operator<(const date& rhs) const;
	date& operator+=(uint32_t p_day);
	date operator+(uint32_t rhs) const;
	friend std::ostream& operator<<(std::ostream& lhs, const date& rhs);
	friend std::istream& operator>>(std::istream& lhs, date& rhs);

private:
	const static uint8_t day_in_mon[12];
};

namespace std {
	std::string to_string(const date& p_date);
}
