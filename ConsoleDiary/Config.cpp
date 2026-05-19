#include "Config.h"

string config::m_file_name = "test";

string config::get_csv_file_path()
{
	return m_file_name + ".csv";
}

string config::get_binary_file_path()
{
	return m_file_name + ".data";
}
