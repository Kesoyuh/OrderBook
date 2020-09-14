// Entry point

#include <iostream>
#include <string>

#include "FileParser.h"
#include "DataDefine.h"
#include "OrderBook.h"

const std::string kFileName = "feedText.txt";

int main()
{
	FileParser fileparser;

	if (fileparser.ReadFileData(kFileName))
	{
		OrderBook orderbook;

		while (true)
		{
			Order order;
			if (!fileparser.FecthNextOrder(order))
			{
				break;
			}

			orderbook.HandleIncomingOrder(order);
		}

		orderbook.PrintOrderBookStatus();
	}

	
}