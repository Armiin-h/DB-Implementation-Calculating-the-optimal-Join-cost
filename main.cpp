#include "Relation.h"

using namespace std;

int main()
{
	int relNum = 0;
	cout << "Enter number of relations: ";
	cin >> relNum;
	cout << endl;
	vector<Relation> relations(relNum);
	for (int i = 0; i < relNum; i++)
	{
		cout << "Relation number " << i + 1 << endl;
		cin >> relations[i];
		cout << endl;
	}

	cout << "\n\n| relations";
	SetCursorPos_X(20);
	cout << "| size";
	SetCursorPos_X(40);
	cout << "| cost";
	SetCursorPos_X(60);
	cout << "| best order" << endl;
	cout << "---------------------------------------------------------------------------" << endl;

	for (int i = 0; i < relNum; i++)
	{
		cout << "| [" << relations[i].name << "]";
		SetCursorPos_X(20);
		cout << "| " << fixed << setprecision(1) << relations[i].relationSize;
		SetCursorPos_X(40);
		cout << "| 0";
		SetCursorPos_X(60);
		cout << "| " << relations[i].name << endl;
	}

	vector<map<vector<int>, RelationSolution> > dynamicHelper(relNum - 1);

	Relation relMax;
	vector<vector<int> > g = SubsetIndex(relNum, 2);

	for (auto it = g.begin();it != g.end(); it++)
	{
		relMax = relations[(*it)[0]] + relations[(*it)[1]];
		dynamicHelper[0][*it] = {relMax, 0};

		cout << "| [" << relations[(*it)[0]].name << ", " << relations[(*it)[1]].name << "]";
		SetCursorPos_X(20);
		cout << "| " << fixed << setprecision(1) << relMax.relationSize;
		SetCursorPos_X(40);
		cout << "| 0";
		SetCursorPos_X(60);
		cout << "| " << relMax.name << endl;
	}

	double min;
	double temp;
	int index;

	for (int i = 1; i < relNum - 1; i++)
	{
		vector<vector<int> > g = SubsetIndex(relNum, i + 2);

		for (auto it = g.begin(); it != g.end(); it++)
		{
			vector<int> tempVec = *it;
			int minIndex = 0;
			min = INFINITE;
			for (int j = 0; j <= i + 1; j++)
			{
				tempVec.erase(tempVec.begin() + j);
				temp = dynamicHelper[i - 1][tempVec].relation.relationSize + dynamicHelper[i - 1][tempVec].cost;
				if (temp < min)
				{
					minIndex = j;
					min = temp;
				}

				tempVec = *it;
			}
			tempVec.erase(tempVec.begin() + minIndex);
			relMax = dynamicHelper[i - 1][tempVec].relation + relations[(*it)[minIndex]];
			dynamicHelper[i][*it] = {relMax, min};

			cout << "| [" << relations[(*it)[0]].name;
			for (int j = 1; j <= i + 1; j++)
				cout << ", " << relations[(*it)[j]].name;
			cout << "]";
			SetCursorPos_X(20);
			cout << "| " << fixed << setprecision(1) << relMax.relationSize;
			SetCursorPos_X(40);
			cout << "| " << fixed << setprecision(1) << min;
			SetCursorPos_X(60);
			cout << "| " << relMax.name << endl;
		}
	}
}
