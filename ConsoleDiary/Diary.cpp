#include "Diary.h"
#include "Util.h"

diary::diary(const diary_data& data)
{
	m_data = data;
}

diary::diary()
{
	m_data = diary_data{ 0, 0, "", "", "" };
}

//string diary::get_uuid() const 
//{
//	return string(m_data.m_uuid);
//}

int diary::get_id() const
{
	return m_data.m_id;
}

time_t diary::get_date() const
{
	return m_data.m_date;
}

const char* diary::get_weather() const
{
	return m_data.m_weather;
}

const char* diary::get_title() const
{
	return m_data.m_title;
}

const char* diary::get_content() const
{
	return m_data.m_content;
}

string diary::to_string_short() const 
{
	return std::to_string(m_data.m_id) + " " + std::to_string(m_data.m_date) + " " + m_data.m_title;
}

string diary::to_string() const 
{
	char buf[20];
	std::tm tm_info;
	std::time_t t = m_data.m_date;
	localtime_s(&tm_info, &t);
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &tm_info);
	return "ID : " + std::to_string(m_data.m_id) + "\nTimestamp : " + std::to_string(m_data.m_date) + "\n날씨 : " + m_data.m_weather + "\n제목 : " + m_data.m_title + "\n\n" + m_data.m_content + "\n\n작성 시각 : " + string(buf);
}

bool diary::operator<(const diary& o) const 
{
	return this->m_data.m_date > o.m_data.m_date;
}

// TODO : 구조체 기반 직렬화로 변경하기
vector<uint8_t> diary::serialize_diary_binary() const 
{
	vector<uint8_t> buf(sizeof(diary_data));
	memcpy(buf.data(), &m_data, sizeof(diary_data));
	return buf;
}

vector<string> diary::serialize_diary_csv() const
{
	return
	{
		std::to_string(m_data.m_id), std::to_string(m_data.m_date), m_data.m_weather, m_data.m_title, m_data.m_content
	};
}
