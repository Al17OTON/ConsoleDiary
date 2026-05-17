#include "Diary.h"
#include "Util.h"

diary::diary(int id, const string& date, const string& weather, const string& title, const string& content) 
{
	this->m_id = id;
	this->m_date = date;
	this->m_weather = weather;
	this->m_title = title;
	this->m_content = content;
	this->m_is_delete = false;
}

diary::diary(const vector<uint8_t>& buf) 
{
	size_t offset = 0;
	util::read_bytes(buf, offset, m_id);
	util::read_bytes(buf, offset, m_date);
	util::read_bytes(buf, offset, m_weather);
	util::read_bytes(buf, offset, m_title);
	util::read_bytes(buf, offset, m_content);
	m_is_delete = false;
}

diary::diary(const vector<string>& fields)
{
	m_id = std::stoi(fields[0]);
	m_date = fields[1];
	m_weather = fields[2];
	m_title = fields[3];
	m_content = fields[4];
	m_is_delete = false;
}

int diary::get_id() const 
{
	return m_id;
}

string diary::get_date() const 
{
	return m_date;
}

string diary::get_weather() const 
{
	return m_weather;
}

string diary::get_title() const 
{
	return m_title;
}

string diary::get_content() const 
{
	return m_content;
}

bool diary::get_is_delete() const 
{
	return m_is_delete;
}

void diary::set_date(const string& date) 
{
	this->m_date = date;
}

void diary::set_weather(const string& weather) 
{
	this->m_weather = weather;
}

void diary::set_title(const string& title) 
{
	this->m_title = title;
}

void diary::set_content(const string& content) 
{
	this->m_content = content;
}

void diary::set_is_delete() 
{
	m_is_delete = true;
}

string diary::to_string_short() const 
{
	return std::to_string(m_id) + " " + m_date + " " + m_title;
}

string diary::to_string() const 
{
	return std::to_string(m_id) + " " + m_date + " " + m_weather + " " + m_title + " " + m_content;
}

bool diary::operator<(const diary& o) const 
{
	return this->m_id < o.m_id;
}

vector<uint8_t> diary::serialize_diary_binary() const 
{
	vector<uint8_t> buf;

	util::write_bytes(buf, m_id);
	util::write_bytes(buf, m_date);
	util::write_bytes(buf, m_weather);
	util::write_bytes(buf, m_title);
	util::write_bytes(buf, m_content);

	return buf;
}

vector<string> diary::serialize_diary_csv() const
{
	return
	{
		std::to_string(m_id), m_date, m_weather, m_title, m_content
	};
}
