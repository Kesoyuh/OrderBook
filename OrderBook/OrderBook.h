// The Order Book class which handle the orders and trades

#pragma once

#include <map>
#include <unordered_map>

#include "DataDefine.h"

class OrderBook
{

public:
	void HandleIncomingOrder(Order& order);
	
	void PrintOrderBookStatus();

private:
	// Execute the incoming order, try to generate trades, and return the remaining quantity
	int ExcuteOrder(Side side, int count, double price);

	void AddOrderToBook(const Order& order);

	void DeleteOrderFromBook(const Order& order);

	std::multimap<double, Order, std::less<double>> ask_map;
	std::multimap<double, Order, std::greater<double>> bid_map;

	// id -> iter map, for O(1) delete and modify operation
	std::unordered_map<std::string, std::multimap<double, Order>::iterator> id_iter_map;
};

