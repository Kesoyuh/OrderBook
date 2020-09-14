// Parse file to orders

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "FileParser.h"

FileParser::FileParser()
{
	lines = std::vector<std::string>();
	current_line = lines.begin();
}


bool FileParser::ReadFileData(const std::string& fileName)
{
	lines.clear();

	std::ifstream instream(fileName.c_str());
	std::string line;

	if (!instream)
	{
		std::cout << "Error: Failed to open file " << fileName.c_str();
		return false;
	}
	
	// Read lines in the file and store them into a vector
	while (!instream.eof())
	{
		std::getline(instream, line);
		lines.push_back(line);
	}

	instream.close();

	// Let the current_line_ iter point at the first elem
	current_line = lines.begin();

	return true;
}

bool FileParser::FecthNextOrder(Order& nextOrder)
{
	if (current_line == lines.end())
	{
		return false;
	}

	std::string orderstr = *current_line;
	if (orderstr.empty())
	{
		return false;
	}

	current_line++;

	// Split a line into vector by ','
	std::istringstream in(orderstr);
	std::vector<std::string> vec;
	std::string str;
	while (std::getline(in, str, ','))
	{
		vec.push_back(str);
	}

	// Construct an order
	if (vec.size() != 5)
	{
		std::cout << "Error: Failed to parse the order, please check the input format!" << std::endl;
		return false;
	}

	// A,100000,S,1,1075
	if (vec[0] == "A")
	{
		nextOrder.operation = Operation::New;
	}
	else if (vec[0] == "X")
	{
		nextOrder.operation = Operation::Delete;
	}
	else
	{
		std::cout << "Error: Failed to parse the order, wrong operation!";
		return false;
	}
	
	if (vec[2] == "B")
	{
		nextOrder.side = Side::Buy;
	}
	else if (vec[2] == "S")
	{
		nextOrder.side = Side::Sell;
	}
	else
	{
		std::cout << "Error: Failed to parse the order, wrong side!";
		return false;
	}

	nextOrder.orderid = vec[1];
	nextOrder.count = std::atoi(vec[3].c_str());
	nextOrder.price = std::atof(vec[4].c_str());

	return true;
}


