#pragma once
#include <string>

using namespace std;

class config
{
public:
	static string get_csv_file_path();
	static string get_binary_file_path();

private:
	static string m_file_name;
};