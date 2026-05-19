#pragma once
#include <vector>
#include <string>

using namespace std;

class writer 
{
public:
	static void save_binary(const vector<vector<uint8_t>> chunks);
	static void save_csv(const vector<vector<string>>& chunks);

private:
	static string escape_csv(const string& field);
};