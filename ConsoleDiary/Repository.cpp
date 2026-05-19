#include "Repository.h"
#include "Reader.h"
#include "Writer.h"
#include <iostream>

repository::repository() 
{
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
	//save();
}

repository* repository::m_instance = nullptr;

repository* repository::get_instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new repository();
	}
	return m_instance;
}

void repository::delete_instance()
{
	delete m_instance;
	m_instance = nullptr;
}

void repository::insert_diary(const diary& new_diary) 
{
	m_diaries.insert(new_diary);
}

void repository::insert_diary(const string& date, const string& weather, const string& title, const string& content) 
{
	m_diaries.insert(diary(generate_id(), date, weather, title, content));
}

diary repository::get_diary_by_id(int id) const 
{
	//for (int i = 0; i < m_diaries.size(); ++i) 
	//{
	//	if (m_diaries[i].get_id() == id) 
	//	{
	//		return m_diaries[i];
	//	}
	//}
	//return diary(-1, "", "", "", "");

	set<diary>::iterator iter = m_diaries.find(diary(id, "", "", "", ""));
	if (iter == m_diaries.end())
	{
		return diary(-1, "", "", "", "");
	}
	return *iter;
}

vector<diary> repository::get_diaries() const 
{
	return vector<diary>(m_diaries.begin(), m_diaries.end());
}

void repository::update_diary(const diary& new_diary) 
{
	if (!check_id_exist(new_diary.get_id()))
	{
		cout << "잘못된 ID 입니다.\n";
		return;
	}
	m_diaries.erase(diary(new_diary.get_id(), "", "", "", ""));
	m_diaries.insert(new_diary);
	//m_diaries[new_diary.get_id()].set_date(new_diary.get_date());
	//m_diaries[new_diary.get_id()].set_weather(new_diary.get_weather());
	//m_diaries[new_diary.get_id()].set_title(new_diary.get_title());
	//m_diaries[new_diary.get_id()].set_content(new_diary.get_content());
}

void repository::update_diary(int id, const string& date, const string& weather, const string& title, const string& content)
{
	if (!check_id_exist(id)) 
	{
		cout << "잘못된 ID 입니다.\n";
		return;
	}
	diary change(id, date, weather, title, content, m_diaries.find(diary(id, "", "", "", ""))->get_timestamp());
	m_diaries.erase(diary(id, "", "", "", ""));
	m_diaries.insert(change);
	//m_diaries[id].set_date(date);
	//m_diaries[id].set_weather(weather);
	//m_diaries[id].set_title(title);
	//m_diaries[id].set_content(content);
}

void repository::erase_diary_by_id(int id) 
{
	if (!check_id_exist(id)) 
	{
		cout << "잘못된 ID 입니다.\n";
		return;
	}
	//m_diaries[id].set_is_delete();
	set<diary>::iterator iter = m_diaries.find(diary(id, "", "", "", ""));
	iter->get_is_delete();
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
	vector<diary> diaries_vec(m_diaries.begin(), m_diaries.end());
	for (int i = 0; i < diaries_vec.size(); ++i)
	{
		if (diaries_vec[i].get_is_delete()) continue;
		result.push_back(diaries_vec[i].serialize_diary_binary());
	}
	return result;
}

void repository::deserialize_diaries_binary(const vector<vector<uint8_t>>& chunks) 
{
	m_diaries.clear();
	for (int i = 0; i < chunks.size(); ++i) 
	{
		m_diaries.insert(chunks[i]);
	}
}

vector<vector<string>> repository::serialize_diaries_csv() const
{
	vector<vector<string>> result;
	vector<diary> diaries_vec(m_diaries.begin(), m_diaries.end());
	for (int i = 0; i < diaries_vec.size(); ++i)
	{
		if (diaries_vec[i].get_is_delete()) continue;
		result.push_back(diaries_vec[i].serialize_diary_csv());
	}
	return result;
}

void repository::deserialize_diaries_csv(const vector<vector<string>>& chunks)
{
	m_diaries.clear();
	for (int i = 0; i < chunks.size(); ++i)
	{
		m_diaries.insert(chunks[i]);
	}
}

int repository::generate_id() const 
{
	//return m_diaries.empty() ? 0 :(--m_diaries.end())->get_id() + 1;
	if(m_diaries.empty()) 
	{
		return 0;
	}
	else
	{
		return (--m_diaries.end())->get_id() + 1;
	}
}

bool repository::check_id_exist(int id) const 
{
	//for (int i = 0; i < m_diaries.size(); ++i) 
	//{
	//	if (m_diaries[i].get_id() == id) return true;
	//}
	//return false;
	return m_diaries.find(diary(id, "", "", "", "")) != m_diaries.end();
}
