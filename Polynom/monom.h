#pragma once

#include <stdexcept>
#include <string>
#include <iostream>
#include <regex>

using namespace std;

class Monom 
{
	double k;
	int degX = 0,
		degY = 0,
		degZ = 0;
	void set_coeffitient(const string& str);
	void set_degree(const char& c, const string& degree);
	void match_pattern(const string& str) const;
	void parse_monom(const string& str);
public:
	Monom();
	Monom(double K, int X, int Y, int Z);
	Monom(const Monom& m);
	Monom(const string& s);
	double get_coef() const;
	int get_x() const;
	int get_y() const;
	int get_z() const;

	double calculate(double x, double y, double z) const;
	bool equal(const Monom& m)const;
	bool operator<(const Monom& m) const;
	bool operator<=(const Monom& m) const;
	bool operator>(const Monom& m)const;
	bool operator>=(const Monom& m)const;
	bool operator==(const Monom& m)const;
	bool operator!=(const Monom& m)const;
	Monom operator+(const Monom& m)const;
	Monom& operator+=(const Monom& m);
	Monom operator-(const Monom& m)const;
	Monom& operator-=(const Monom& m);
	Monom operator*(const Monom& m)const;
	Monom& operator*=(const Monom& m);
	Monom operator/(const Monom& m)const;
	Monom& operator/=(const Monom& m);
	Monom operator*(const double& k)const;
	Monom& operator*=(const double& k);
	Monom operator/(const double& k)const;
	Monom& operator/=(const double& k);
	friend ostream& operator<<(ostream& os, const Monom& m);
};
