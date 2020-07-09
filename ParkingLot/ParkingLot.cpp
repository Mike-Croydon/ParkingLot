// This program creates a virtual parking lot, and is meant as an exercise in OOP

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

class Spot {
private:
	bool occupied;
	int xPos, yPos;
public:
	Spot(int x, int y)
	{
		occupied = false;
		xPos = x;
		yPos = y;
	}
	void changexPos(int x)
	{
		xPos = x;
	}
	void changeyPos(int y)
	{
		yPos = y;
	}
};

class Row {
private:
	int size;
	int id;
	vector<Spot> spots;
public:
	Row(int s, int id)
	{
		size = s;
		id = id;
		for (int i = 0; i < size; i++)
		{
			Spot nspot = Spot(i, 2 * id);
			spots.push_back(nspot);
		}
	}
};
class Parkinglot {
private:
	int size, numRows, spotsPerRow;
	vector<Row> rows;
public:
	Parkinglot(int nRows, int sPerRow)
	{
		numRows = nRows;
		spotsPerRow = sPerRow;
		for (int i = 0; i < numRows; i++)
		{
			Row nrow = Row(spotsPerRow, numRows);
			rows.push_back(nrow);
		}
	}
};

class Vehicle {
private:
	int vehicleID;
	char vehicleType; //c, m, or b
public:

};



int main()
{
	Parkinglot lotA = Parkinglot(3, 15);
}


