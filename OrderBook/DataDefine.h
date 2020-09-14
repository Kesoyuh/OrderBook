// Structure of an order, trade

#pragma once

#include <string>
#include <iostream>

enum class Side : int
{
	Sell = 0,
	Buy = 1
};

enum class Operation : int
{
	New = 0,
	Delete = 1,
	Modify = 2
};

struct Order
{
	Operation operation;
	std::string orderid;
	Side side;
	int count;
	double price;	
};

struct Trade
{
	int count;
	double price;

	void Print()
	{
		std::cout << count << (count == 1 ? " share" : " shares")
			<< " of XYZ were sold at " << price << " USD" << std::endl;
	}
};