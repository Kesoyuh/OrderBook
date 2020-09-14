// File parser and data provider

#pragma once

#include <string>
#include <vector>

#include "DataDefine.h"

class FileParser
{

public: 
	FileParser();
	bool ReadFileData(const std::string& fileName);
	bool FecthNextOrder(Order& nextOrder);

private:
	std::vector<std::string> lines;
	std::vector<std::string>::iterator current_line;
	
};

