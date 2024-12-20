#pragma once

#include <vector>
#include <regex>
#include <map>
#include "sorted_list.h"
#include "monom.h"
#include <functional>


using namespace std;

struct Point 
{
	double x, y, z;
	friend istream& operator>>(istream& is, Point& p) 
	{
		is >> p.x >> p.y >> p.z;
		return is;
	}

	friend ostream& operator<<(ostream& os, const Point& p) 
	{
		os << p.x;
		os << " ";
		os << p.y;
		os << " ";
		os << p.z;
		return os;
	}
};



class Polynom 
{

	SortedList<Monom> monoms;
	void parse_polynom(const string& str);
	string erase_spaces(const string& str);

public:

	static map<string, function<Polynom(const Polynom&, const Polynom&)> > binary_operations;
	static map<string, function<Polynom(const Polynom&)> > unary_operations;
	static map<string, function<double(const Polynom&, Point&)> > ternary_operations;
	static map<string, function<double(const Polynom&, Point&, Point&)> > integrals;
 
	Polynom();
	Polynom(const string& str);
	Polynom(const Polynom& p);

	void add(const Monom& m);
	double calculate(double x, double y, double z) const;
	double calculate(Point& p) const;
	Polynom differential(char variable) const;
	Polynom primitive(char variable) const;
	const LinkedList<Monom>& get_monoms() const;

	Polynom operator+(const Polynom& p)const;
	Polynom& operator+=(const Polynom& p);
	Polynom operator-(const Polynom& p)const;
	Polynom& operator-=(const Polynom& p);
	Polynom operator+(const Monom& m)const;
	Polynom& operator+=(const Monom& m);
	Polynom operator-(const Monom& m)const;
	Polynom& operator-=(const Monom& m);
	Polynom operator*(const Polynom& p)const;
	Polynom& operator*=(const Polynom& p);
	Polynom operator/(const Monom& p)const;
	Polynom& operator/=(const Monom& p);
	Polynom operator*(const Monom& m)const;
	Polynom& operator*=(const Monom& m);
	Polynom operator*(const double& k)const;
	Polynom& operator*=(const double& k);
	Polynom operator/(const Polynom& p)const;
	Polynom& operator/=(const Polynom& p);

	bool operator==(const Polynom& p)const;
	bool operator!=(const Polynom& p)const;
	bool operator>(const Polynom& p)const;
	bool operator>=(const Polynom& p)const;
	bool operator<(const Polynom& p)const;
	bool operator<=(const Polynom& p)const;
	friend ostream& operator<<(ostream& os, const Polynom& p);
};
