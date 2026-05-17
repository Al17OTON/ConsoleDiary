#pragma once
#include <string>
#include <vector>

using namespace std;

class diary 
{
private:
	int m_id;					// 고유 식별자
	string m_date;				// 작성 일자
	string m_weather;			// 날씨
	string m_title;				// 제목
	string m_content;			// 내용
	bool m_is_delete;				// 삭제 표시

public:
	diary(int id, const string& date, const string& weather, const string& title, const string& content);
	diary(const vector<uint8_t>& buf);

	int get_id() const;
	string get_date() const;
	string get_weather() const;
	string get_title() const;
	string get_content() const;
	bool get_is_delete() const;

	void set_date(const string& date);
	void set_weather(const string& weather);
	void set_title(const string& title);
	void set_content(const string& content);
	void set_is_delete();

	string to_string_short() const;
	string to_string() const;

	bool operator < (const diary& o) const;

	vector<uint8_t> serialize_diary() const;
};