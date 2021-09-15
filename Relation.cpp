#include "Relation.h"

Relation::Relation(double size)
	:relationSize(size)
{
}

Relation Relation::operator+(Relation& relation2)
{
	Relation appendRelation;
	double temp;
	double den = 1;
	for (auto i = properties.begin(); i != properties.end(); i++) {
		try {
			temp = relation2.properties.at(i->first);
			if (temp > (i->second)) {
				appendRelation.properties.insert({ i->first, temp });
				den *= temp;
			}
			else {
				appendRelation.properties.insert({ i->first, (i->second) });
				den *= (i->second);
			}
		}

		catch(exception e){
			appendRelation.properties.insert({ i->first, (i->second) });
		}
	}

	for (auto i = relation2.properties.begin(); i != relation2.properties.end(); i++) {
		try {
			temp = properties.at(i->first);
		}

		catch (exception e) {
			appendRelation.properties.insert({ i->first, (i->second) });
		}
	}

	appendRelation.relationSize = (relationSize * relation2.relationSize) / den;

			appendRelation.name = "(" + name + "*" + relation2.name + ")";
	
	return appendRelation;
}

vector<vector<int>> SubsetIndex(int n, int k)
{
	if (k == 1) {
		vector<vector<int>> result(n);
		for (int i = 0; i < n; i++)
			result[i].push_back(i);
		return result;
	}
	if (k == n) {
		vector<vector<int>> result = {vector<int>(n)};
		for (int i = 0; i < n; i++)
			result[0][i] = i;
		return result;
	}
	vector<vector<int>> res1 = SubsetIndex(n - 1, k);
	vector<vector<int>> res2 = SubsetIndex(n - 1, k - 1);
	for (int i = 0; i < res2.size(); i++)
		res2[i].push_back(n - 1);
	res1.insert(res1.end(), res2.begin(), res2.end());
	return res1;
}

void SetCursorPos_X(int x) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	GetConsoleScreenBufferInfo(hStdout, &cbsi);
	SetConsoleCursorPosition(hStdout, { (SHORT)x, cbsi.dwCursorPosition.Y });
}

istream& operator>>(istream& iStream, Relation& rel)
{
	int n, val;
	string c;
	cout << "Enter relation Name: ";
	iStream >> rel.name;
	cout << "Enter relation size: ";
	iStream >> rel.relationSize;
	cout << "Enter number of properties: ";
	iStream >> n;
	for (int i = 0; i < n; i++) {
		cout << "property number " << i + 1 << endl;
		cout << "property name (string): ";
		iStream >> c;
		cout << "property value (double): ";
		iStream >> val;
		rel.properties[c] = val;
	}
	return iStream;
}
