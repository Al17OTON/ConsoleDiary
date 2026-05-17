#include "Repository.h"
#include "Reader.h"
#include "Writer.h"
#include <iostream>

repository::repository() 
{
	cout << "Repository 생성 \n";
	vector<vector<uint8_t>> load_binary = reader::load_binary();
	vector<vector<string>> load_csv = reader::load_scv();
	if (!load_csv.empty())
	{
		deserialize_diaries_csv(reader::load_scv());
	}
	else
	{
		deserialize_diaries_binary(reader::load_binary());
	}
	
}

repository::~repository() 
{
	cout << "Repository 소멸자\n";
	//save();  // 종료 시 자동 저장
}

repository& repository::get_instance() 
{
	static repository instance;		// meyer's singleton

	return instance;
}

void repository::insert_diary(const diary& new_diary) 
{
	m_diaries.push_back(new_diary);
}

void repository::insert_diary(const string& date, const string& weather, const string& title, const string& content) 
{
	m_diaries.push_back(diary(generate_id(), date, weather, title, content));
}

diary repository::get_diary_by_id(int id) const 
{
	for (int i = 0; i < m_diaries.size(); ++i) 
	{
		if (m_diaries[i].get_id() == id) 
		{
			return m_diaries[i];
		}
	}
	return diary(-1, "", "", "", "");
}

vector<diary> repository::get_diaries() const 
{
	return m_diaries;
}

void repository::update_diary(const diary& new_diary) 
{
	if (!check_id_exist(new_diary.get_id()))
	{
		cout << "잘못된 아이디입니다\n";
		return;
	}
	m_diaries[new_diary.get_id()].set_date(new_diary.get_date());
	m_diaries[new_diary.get_id()].set_weather(new_diary.get_weather());
	m_diaries[new_diary.get_id()].set_title(new_diary.get_title());
	m_diaries[new_diary.get_id()].set_content(new_diary.get_content());
}

void repository::update_diary(int id, const string& date, const string& weather, const string& title, const string& content) 
{
	if (!check_id_exist(id)) 
	{
		cout << "잘못된 아이디입니다\n";
		return;
	}
	diary change(id, date, weather, title, content);
	m_diaries[id].set_date(date);
	m_diaries[id].set_weather(weather);
	m_diaries[id].set_title(title);
	m_diaries[id].set_content(content);
}

void repository::erase_diary_by_id(int id) 
{
	if (!check_id_exist(id)) 
	{
		cout << "잘못된 아이디입니다\n";
		return;
	}
	m_diaries[id].set_is_delete();
}

void repository::save_diaries_binary() const 
{
	writer::save_binary(serialize_diaries_binary());
}

void repository::save_diaries_csv() const
{
	writer::save_csv(serialize_diaries_csv());
}

int repository::get_size() const 
{
	return m_diaries.size();
}

vector<vector<uint8_t>> repository::serialize_diaries_binary() const 
{
	vector<vector<uint8_t>> result;
	for (int i = 0; i < m_diaries.size(); ++i) 
	{
		if (m_diaries[i].get_is_delete()) continue;
		result.push_back(m_diaries[i].serialize_diary_binary());
	}
	return result;
}

void repository::deserialize_diaries_binary(const vector<vector<uint8_t>>& chunks) 
{
	m_diaries.clear();
	for (int i = 0; i < chunks.size(); ++i) 
	{
		m_diaries.push_back(chunks[i]);
	}
}

vector<vector<string>> repository::serialize_diaries_csv() const
{
	vector<vector<string>> result;
	for (int i = 0; i < m_diaries.size(); ++i)
	{
		if (m_diaries[i].get_is_delete()) continue;
		result.push_back(m_diaries[i].serialize_diary_csv());
	}
	return result;
}

void repository::deserialize_diaries_csv(const vector<vector<string>>& chunks)
{
	m_diaries.clear();
	for (int i = 0; i < chunks.size(); ++i)
	{
		m_diaries.push_back(chunks[i]);
	}
}

int repository::generate_id() const 
{
	return m_diaries.empty() ? 0 :(--m_diaries.end())->get_id() + 1; // 임시
}

bool repository::check_id_exist(int id) const 
{
	for (int i = 0; i < m_diaries.size(); ++i) 
	{
		if (m_diaries[i].get_id() == id) return true;
	}
	return false;
}
