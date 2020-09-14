// A container which store current order lists

#pragma once

#include <map>
#include <set>

#include "DataDefine.h"

class OrderCache
{

public:
	//std::multimap<double, Order> cur_order_map;
	//std::multimap<double, Order> desired_order_map;

	// sorted set, sort by price and count
	std::multiset<Order> cur_order_set;
	std::multiset<Order> desired_order_set;
	void TransferWithinMinSteps();
};

