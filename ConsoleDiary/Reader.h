#pragma once
#include <vector>
#include <string>

using namespace std;

class reader 
{
public:
	static vector<vector<uint8_t>> load_binary();
	static vector<vector<string>> load_scv();

private:
	static vector<string> parse_row(const string& line);
};