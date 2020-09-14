// The Order Book class which handle the orders and trades

#include "OrderBook.h"
#include "DataDefine.h"

void OrderBook::HandleIncomingOrder(Order& order)
{
	if (order.operation == Operation::New)
	{
		order.count = ExcuteOrder(order.side, order.count, order.price);
		if (order.count > 0)
		{
			// There are still some shares left, add it to the order book
			AddOrderToBook(order);
		}
	}
	else if (order.operation == Operation::Delete)
	{
		DeleteOrderFromBook(order);
	}
}

void OrderBook::PrintOrderBookStatus()
{
	std::cout << "=================" << std::endl;
	std::cout << "ASK" << std::endl;

	std::map<double, std::string, std::less<double>> order_book_ask_entry = std::map<double, std::string, std::less<double>>();
	for (auto it = ask_map.begin(); it != ask_map.end(); ++it)
	{
		if (order_book_ask_entry.find(it->first) == order_book_ask_entry.end())
		{
			order_book_ask_entry.insert({ it->first, std::to_string(it->second.count) + " " });
		}
		else
		{
			order_book_ask_entry[it->first] = order_book_ask_entry[it->first] + std::to_string(it->second.count) + " ";
		}
	}

	for (auto it = order_book_ask_entry.rbegin(); it != order_book_ask_entry.rend(); it++)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}

	std::cout << "------------" << std::endl;
	
	std::map<double, std::string, std::greater<double>> order_book_bid_entry = std::map<double, std::string, std::greater<double>>();
	for (auto it = bid_map.begin(); it != bid_map.end(); ++it)
	{
		if (order_book_bid_entry.find(it->first) == order_book_bid_entry.end())
		{
			order_book_bid_entry.insert({ it->first, std::to_string(it->second.count) + " " });
		}
		else
		{
			order_book_bid_entry[it->first] = order_book_bid_entry[it->first] + std::to_string(it->second.count) + " ";
		}
	}

	for (auto it = order_book_bid_entry.begin(); it != order_book_bid_entry.end(); it++)
	{
		std::cout << it->first << ": " << it->second << std::endl;
	}

	std::cout << "BID" << std::endl;
	std::cout << "=================" << std::endl;	
}

int OrderBook::ExcuteOrder(Side side, int count, double price)
{
	int ret = count;
	if (side == Side::Buy)
	{
		auto it = ask_map.begin();
		while (it != ask_map.end() && it->second.price <= price && ret != 0)
		{
			int completed_count = std::min(it->second.count, ret);
			it->second.count -= completed_count;
			ret -= completed_count;

			Trade trade = {completed_count, it->second.price};
			trade.Print();

			if (it->second.count == 0)
			{
				auto deleted_it = it;
				it++;
				DeleteOrderFromBook(deleted_it->second);
			}
			else
			{
				it++;
			}	
		}
	}
	else if (side == Side::Sell)
	{
		auto it = bid_map.begin();
		while (it != bid_map.end() && it->second.price >= price && ret != 0)
		{
			int completed_count = std::min(it->second.count, ret);
			it->second.count -= completed_count;
			ret -= completed_count;

			Trade trade = { completed_count, it->second.price };
			trade.Print();

			if (it->second.count == 0)
			{
				auto deleted_it = it;
				it++;
				DeleteOrderFromBook(deleted_it->second);
			}
			else
			{
				it++;
			}
		}
	}

	return ret;
}

void OrderBook::AddOrderToBook(const Order& order)
{
	std::multimap<double, Order>::iterator it;
	if (order.side == Side::Buy)
	{
		it = bid_map.insert({ order.price, order });
	}
	else
	{
		it = ask_map.insert({ order.price, order });
	}
	auto ret = id_iter_map.insert({ order.orderid, it });
	if (!ret.second)
	{
		std::cout << "Error: Duplicated order id " << order.orderid;
	}
}

void OrderBook::DeleteOrderFromBook(const Order& order)
{
	auto iter = id_iter_map.find(order.orderid);
	if (iter != id_iter_map.end())
	{
		if (order.side == Side::Buy)
		{
			bid_map.erase(iter->second);
		}
		else
		{
			ask_map.erase(iter->second);
		}

		id_iter_map.erase(iter);
	}
}
