#ifndef DATA_H
#define DATA_H

#include <vector>

struct static_data {
	std::vector<std::string> uid;
	// expand 
};


struct dynamic_data {
	std::vector<std::string> uid;
	std::vector<float> income;
	std::vector<float> assets;
	std::vector<float> debt;
};


#endif DATA_H
