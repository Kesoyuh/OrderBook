#include "OrderCache.h"

const long long kOrderIdStart = 9000000000;

void OrderCache::TransferWithinMinSteps()
{
	auto it_cur = cur_order_set.begin();
	auto it_desired = desired_order_set.begin();

	// first remove matched orders (same price and count)
	while (it_cur != cur_order_set.end() && it_desired != desired_order_set.end())
	{
		if (it_cur->price < it_desired->price)
		{
			it_cur++;
		}
		else if (it_cur->price > it_desired->price)
		{
			it_desired++;
		}
		else
		{
			// equal price
			if (it_cur->count < it_desired->count)
			{
				it_cur++;
			}
			else if (it_cur->count > it_desired->count)
			{
				it_desired++;
			}
			else
			{
				// equal price and count, delete both orders
				auto it_delete_cur = it_cur;
				it_cur++;
				cur_order_set.erase(it_delete_cur);

				auto it_delete_desired = it_desired;
				it_desired++;
				desired_order_set.erase(it_delete_desired);
			}
		}
	}


	// then handle other orders
	long long cur_order_id = kOrderIdStart;

	it_cur = cur_order_set.begin();
	it_desired = desired_order_set.begin();
	while (!(it_cur == cur_order_set.end() && it_desired == desired_order_set.end()))
	{
		if (it_cur == cur_order_set.end() 
			|| (it_cur != cur_order_set.end() && it_desired != desired_order_set.end() && it_cur->price > it_desired->price))
		{
			// Add new order to the desired order list
			Order new_order;
			new_order.operation = Operation::New;
			new_order.orderid = std::to_string(cur_order_id);
			new_order.side = it_desired->side;
			new_order.count = it_desired->count;
			new_order.price = it_desired->price;
			cur_order_id++;

			new_order.Print();

			it_desired++;
		}
		else if (it_desired == desired_order_set.end() 
			|| (it_cur != cur_order_set.end() && it_desired != desired_order_set.end() && it_cur->price < it_desired->price))
		{
			// Delete this cur order 
			Order new_order;
			new_order.operation = Operation::Delete;
			new_order.orderid = it_cur->orderid;
			new_order.side = it_cur->side;
			new_order.count = it_cur->count;
			new_order.price = it_cur->price;

			new_order.Print();

			it_cur++;
		}
		else if (it_cur->price == it_desired->price)
		{
			// Modify this order
			Order new_order;
			new_order.operation = Operation::Modify;
			new_order.orderid = it_cur->orderid;
			new_order.side = it_cur->side;
			new_order.count = it_desired->count;
			new_order.price = it_cur->price;

			new_order.Print();

			it_cur++;
			it_desired++;
		}
		else
		{
			std::cout << "Error: Something weired happened!" << std::endl;
		}
	}
}
