#include "Repository.h"
#include "Reader.h"
#include "Writer.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>

repository::repository() 
{
	//vector<vector<string>> load_csv = reader::load_scv();

	//if (!load_csv.empty())
	//{
	//	deserialize_diaries_csv(reader::load_scv());
	//}
	//else
	//{
	//	deserialize_diaries_binary(reader::load_binary());
	//}

	vector<vector<uint8_t>> load_binary = reader::load_binary();
	if (!load_binary.empty())
	{
		deserialize_diaries_binary(reader::load_binary());
	}
}

repository::~repository() 
{
	//save();
}

int repository::generate_id() const
{
	// TODO : 더 좋은 id 발급 방식 찾아보기
	int id = rand() % 100000000;
	while (check_id_exist(id))
	{
		id = rand() % 100000000;
	}
	return id;
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

void repository::insert_diary(diary::diary_data& data)
{
	// ID가 지정 안되어있으면 자동으로 생성
	if (data.m_id == -1)
	{
		data.m_id = generate_id();
	}

	// ID가 이미 존재하면 업데이트, 존재하지 않으면 새로 추가
	m_diaries[data.m_id] = diary(data);
}

diary repository::get_diary_by_id(const int id) const 
{
	unordered_map<int, diary>::const_iterator iter = m_diaries.find(id);
	if (iter == m_diaries.end())
	{
		return diary(diary::diary_data{ 0, 0, "", "", ""});
	}
	return iter->second;
}

// TODO : 다이어리 포인터로 반환하여 복사 비용 줄이기
vector<diary> repository::get_diaries() const 
{
	vector<diary> vec;

	for (unordered_map<int, diary>::const_iterator iter = m_diaries.begin(); iter != m_diaries.end(); ++iter)
	{	
		vec.push_back(iter->second);
	}

	sort(vec.begin(), vec.end());

	return vec;
}

void repository::erase_diary_by_id(const int id) 
{
	m_diaries.erase(id);
}

void repository::save_diaries_binary() const
{
	writer::save_binary(serialize_diaries_binary());
}

int repository::get_size() const 
{
	return m_diaries.size();
}

vector<vector<uint8_t>> repository::serialize_diaries_binary() const
{
	vector<vector<uint8_t>> chunks;
	chunks.reserve(m_diaries.size());

	for (unordered_map<int, diary>::const_iterator iter = m_diaries.begin(); iter != m_diaries.end(); ++iter) 
	{
		chunks.push_back(iter->second.serialize_diary_binary());
	}

	return chunks;
}

void repository::deserialize_diaries_binary(const vector<vector<uint8_t>>& chunks)
{
	m_diaries.clear();
	for(int i = 0; i < chunks.size(); ++i) 
	{
		diary::diary_data data;
		memcpy(&data, chunks[i].data(), sizeof(diary::diary_data));
		m_diaries[data.m_id] = diary(data);
	}
}

//char* repository::generate_uuid() const 
//{
//	static random_device rd;
//	static mt19937 gen(rd());
//	static uniform_int_distribution<uint32_t> dist(0, 15);
//	static uniform_int_distribution<uint32_t> dist2(8, 11);
//
//	char buf[37];
//	auto r = [&]() { return dist(gen); };
//
//	snprintf(buf, sizeof(buf),
//		"%x%x%x%x%x%x%x%x-%x%x%x%x-4%x%x%x-%x%x%x%x-%x%x%x%x%x%x%x%x%x%x%x%x",
//		r(), r(), r(), r(), r(), r(), r(), r(),
//		r(), r(), r(), r(),
//		r(), r(), r(),
//		dist2(gen), r(), r(), r(),
//		r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r()
//	);
//
//	return buf;
//}

bool repository::check_id_exist(const int id) const 
{
	return m_diaries.find(id) != m_diaries.end();
}
