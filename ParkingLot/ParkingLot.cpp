// This program creates a virtual parking lot, and is meant as an exercise in OOP

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Spot {
private:
	bool occupied;
	int xPos, yPos;
public:
	int occupyingID;
	char occupyingType;
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
		occupyingID = NULL;
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
			Spot nspot = Spot(i, id);
			spots.push_back(nspot);
		}
	}
};

class Vehicle {
protected:
	int vehicleID;
	char vehicleType; //c, m, or b
public:
	Vehicle();
	Vehicle(int id)
	{
		vehicleID = id;
	}
	char getVehicleType() {
		return vehicleType;
	}
	int getVehicleID() {
		return vehicleID;
	}
};

Vehicle::Vehicle() {};

class Car : public Vehicle {
private:
public:
	Car();
	Car(int id)
	{
		vehicleID = id;
		vehicleType = 'c';
	}
};

class Bus : public Vehicle {
private:
public:
	Bus();
	Bus(int id)
	{
		vehicleID = id;
		vehicleType = 'b';
	}

};

class Lot {
private:
	int size, numRows, spotsPerRow, numVehicles, openSpots, totalSpots;
	vector<Row> rows;
	vector<Vehicle> vehicles;
public:
	Lot(int nRows, int sPerRow)
	{
		numRows = nRows;
		spotsPerRow = sPerRow;
		totalSpots = numRows * spotsPerRow;
		openSpots = totalSpots;
		for (int i = 0; i < numRows; i++)
		{
			Row nrow = Row(spotsPerRow, i);
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
				break;
			}
		}
		if (busSpaceAvail)
		{
			space.push_back(i);
			space.push_back(j);
		}
		else {
			space.push_back(0);
			space.push_back(0);
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
				break;
			}
		}
		if (spaceAvail)
		{
			space.push_back(i);
			space.push_back(j);
		}
		else {
			space.push_back(0);
			space.push_back(0);
		}
		return space;
	}
	void addVehicle(Bus & bus)
	{
		vector<int> spacePos = busSpaceAvailable();
		Spot & busSpot = rows[spacePos[0]].spots[spacePos[1]];
		if (!busSpot.isOccupied())
		{
			int counter = 0;
			while (counter < 5)
			{
				Spot & busSpot = rows[spacePos[0]].spots[spacePos[1]+counter];
				busSpot.occupyingID = bus.getVehicleID();
				busSpot.occupyingType = 'b';
				busSpot.occupy();
				counter++;
			}
			vehicles.push_back(bus);
		}
	}
	void addVehicle(Car & car)
	{
		vector<int> spacePos = spaceAvailable();
		Spot & spot = rows[spacePos[0]].spots[spacePos[1]];
		if (!spot.isOccupied())
		{
			Spot & spot = rows[spacePos[0]].spots[spacePos[1]];
			spot.occupyingID = car.getVehicleID();
			spot.occupyingType = 'c';
			spot.occupy();
			vehicles.push_back(car);
		}
	
	}
	vector<int> findSpace(int id)
	{
		vector<int> space;
		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0; j < spotsPerRow; j++)
			{
				if (rows[i].spots[j].occupyingID == id)
				{
					space.push_back(i);
					space.push_back(j);
					return space;
				}
			}
		}
		space.push_back(0);
		space.push_back(0);
		return space;
	}
	void removeVehicle(int id)
	{
		//removes the vehicle from the list of vehicles
		for (int i = 0; i < vehicles.size(); i++)
		{
			if (vehicles[i].getVehicleID() == id)
			{
				vehicles.erase(vehicles.begin()+i);
			}
		}
		vector<int> remSpace = findSpace(id);
		Spot & remSpot = rows[remSpace[0]].spots[remSpace[1]];
		if (remSpot.isOccupied())
		{
			remSpot.open();
		}

	}
};


int main()
{
	Lot lotA = Lot(3, 15);
	for (int i = 1; i < 20; i++)
	{
		if (i % 4 == 0)
		{
			Bus bus = Bus(i);
			lotA.addVehicle(bus);
		}
		else
		{
			Car car = Car(i);
			lotA.addVehicle(car);
		}
	}
	lotA.removeVehicle(6);
}
