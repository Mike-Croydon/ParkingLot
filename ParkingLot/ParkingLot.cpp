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
	int occupyingID;
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
	bool isOccupied() {
		return occupied;
	}
	void occupy() {
		occupied = true;
	}
	void open() {
		occupied = false;
	}
};

class Row {
private:
	int size;
	int id;
public:
	vector<Spot> spots;
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

class Vehicle {
private:
	int vehicleID;
	char vehicleType; //c, m, or b
public:
	Vehicle(int id, char type)
	{
		vehicleID = id;
		vehicleType = type;
	}
	char getVehicleType() {
		return vehicleType;
	}
	int getVehicleID() {
		return vehicleID;
	}
};


class Parkinglot {
private:
	int size, numRows, spotsPerRow, numVehicles, openSpots, totalSpots;
	vector<Row> rows;
	vector<Vehicle> vehicles;
public:
	Parkinglot(int nRows, int sPerRow)
	{
		numRows = nRows;
		spotsPerRow = sPerRow;
		totalSpots = numRows * spotsPerRow;
		openSpots = totalSpots;
		for (int i = 0; i < numRows; i++)
		{
			Row nrow = Row(spotsPerRow, numRows);
			rows.push_back(nrow);
		}
	}
	//This method checks if there are 5 consecutive spaces available anywhere, and if so returns the index of the first space. If not, it returns the first space in the lot
	//The space returned must be checked when this function is implemented to make sure it isn't occupied
	vector<int> busSpaceAvailable()
	{
		bool busSpaceAvail;
		vector<int> space;
		int i = 0;
		int j = 0;
		for (i = 0; i < numRows; i++)
		{
			for (j = 0; j < spotsPerRow; j++)
			{
				for (int k = 0; k < 5; k++)
				{
					if (j + 5 > spotsPerRow) { break; }
					else if (rows[i].spots[j + k].isOccupied())
					{
						busSpaceAvail = false;
						break;
					}
					else {
						busSpaceAvail = true;
					}
				}
				if (busSpaceAvail) { break; }
			}
			if (busSpaceAvail)
			{
				space.push_back(i);
				space.push_back(j);
				break;
			}
			else {
				space.push_back(0);
				space.push_back(0);
				break;
			}
		}
		return space;
	}

	//returns the first available spot
	vector<int> spaceAvailable()
	{
		bool spaceAvail;
		vector<int> space;
		int i = 0;
		int j = 0;
		for (i = 0; i < numRows; i++)
		{
			for (j = 0; j < spotsPerRow; j++)
			{
				if (rows[i].spots[j].isOccupied())
				{
					spaceAvail = false;
				}
				else {
					spaceAvail = true;
					break;
				}
			}
			if (spaceAvail)
			{
				space.push_back(i);
				space.push_back(j);
				break;
			}
			else {
				space.push_back(0);
				space.push_back(0);
				break;
			}
		}
		return space;
	}
	void addVehicle(Vehicle vehicle)
	{
		if (vehicle.getVehicleType() == 'b')
		{
			vector<int> spacePos = busSpaceAvailable();
			Spot & busSpot = rows[spacePos[0]].spots[spacePos[1]];
			if (!busSpot.isOccupied())
			{
				int counter = 0;
				while (counter < 5)
				{
					Spot & busSpot = rows[spacePos[0]].spots[spacePos[1]+counter];
					busSpot.occupyingID = vehicle.getVehicleID();
					busSpot.occupy();
					counter++;
				}
			}
		
		}
		else
		{
			vector<int> spacePos = spaceAvailable();
			Spot & busSpot = rows[spacePos[0]].spots[spacePos[1]];
			if (!busSpot.isOccupied())
			{
				Spot & busSpot = rows[spacePos[0]].spots[spacePos[1]];
				busSpot.occupyingID = vehicle.getVehicleID();
				busSpot.occupy();
			}
		}
	}
};





int main()
{
	Parkinglot lotA = Parkinglot(3, 15);
	for (int i = 1; i < 20; i++)
	{
		if (i % 4 == 0)
		{
			Vehicle veh = Vehicle(i, 'b');
			lotA.addVehicle(veh);
		}
		else
		{
			Vehicle veh = Vehicle(i, 'c');
			lotA.addVehicle(veh);
		}
	}
}


