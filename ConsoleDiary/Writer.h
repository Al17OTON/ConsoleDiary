#pragma once
#include <vector>

using namespace std;

class writer 
{
public:
	static void save(const vector<vector<uint8_t>> chunks);
};