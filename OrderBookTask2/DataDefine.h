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

	bool operator< (const Order& order) const
	{
		if (price < order.price)
		{
			return true;
		}
		else if (price > order.price)
		{
			return false;
		}
		else
		{
			//same price
			return count < order.count;
		}
	}

	void Print()
	{
		std::string opstr;
		switch (operation)
		{
		case Operation::New:
			opstr = "A";
			break;
		case Operation::Delete:
			opstr = "X";
			break;
		case Operation::Modify:
			opstr = "M";
			break;
		default:
			break;
		}

		std::string sidestr;
		switch (side)
		{
		case Side::Sell:
			sidestr = "S";
			break;
		case Side::Buy:
			sidestr = "B";
			break;
		default:
			break;
		}

		std::cout << opstr << "," << orderid << "," << sidestr << "," << count << "," << price << std::endl;
	}
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