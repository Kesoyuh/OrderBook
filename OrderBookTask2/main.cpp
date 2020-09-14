// Entry point

#include <iostream>
#include <string>

#include "FileParser.h"
#include "DataDefine.h"
#include "OrderCache.h"

const std::string kCurOrdersFile = "curOrders.txt";
const std::string kDesiredOrdersFile = "desiredOrders.txt";

int main()
{
	OrderCache ordercache;
	FileParser fileparser;

	// read cur order file
	if (fileparser.ReadFileData(kCurOrdersFile))
	{
		while (true)
		{
			Order order;
			if (!fileparser.FecthNextOrder(order))
			{
				break;
			}
			ordercache.cur_order_set.insert(order);
		}
	}

	// read desired order file
	if (fileparser.ReadFileData(kDesiredOrdersFile))
	{
		while (true)
		{
			Order order;
			if (!fileparser.FecthNextOrder(order))
			{
				break;
			}
			ordercache.desired_order_set.insert(order);
		}
	}

	ordercache.TransferWithinMinSteps();

	std::cout << std::endl;
}