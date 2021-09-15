#pragma once

#include <map>
#include <vector>
#include <exception>
#include <Windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

vector<vector <int> > SubsetIndex(int n, int k);

void SetCursorPos_X(int x);

class Relation
{
public:
	Relation(double size = 1);
	Relation operator+(Relation& relation2);
	friend istream& operator>>(istream& iStream, Relation& rel);
	double relationSize;
	string name;

private:
	std::map<string, double> properties;
};

struct RelationSolution {
	Relation relation;
	double cost;
};

