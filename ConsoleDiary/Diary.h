#pragma once
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class diary 
{
public:

	struct diary_data
	{
		//char m_uuid[37];		//36글자
		int m_id;
		time_t m_date;
		char m_weather[16];		// 5글자
		char m_title[64];		// 21글자
		char m_content[2048];	// 682글자
	};

	diary(const diary_data& data);
	diary();
	//diary(int id, const string& date, const string& weather, const string& title, const string& content);
	//diary(int id, const string& date, const string& weather, const string& title, const string& content, time_t timestamp);
	//diary(const vector<uint8_t>& buf);
	//diary(const vector<string>& fields);

	int get_id() const;
	//string get_uuid() const;
	time_t get_date() const;
	const char* get_weather() const;
	const char* get_title() const;
	const char* get_content() const;
	time_t get_timestamp() const;

	//void set_date(time_t date);
	//void set_weather(const char* weather);
	//void set_title(const char* title);
	//void set_content(const char* content);

	string to_string_short() const;
	string to_string() const;

	bool operator < (const diary& o) const;

	vector<uint8_t> serialize_diary_binary() const;
	vector<string> serialize_diary_csv() const;
private:
	diary_data m_data;
};