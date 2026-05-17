#pragma once
#include <vector>
#include "Diary.h"

using namespace std;

class repository 
{
private:
	vector<diary> m_diaries;
	repository();
	~repository();

	int generate_id() const;
	bool check_id_exist(int id) const;

	repository(const repository&) = delete;
	repository& operator=(const repository&) = delete;

public:
	static repository& get_instance();

	void insert_diary(const diary& new_diary);
	void insert_diary(const string& date, const string& weather, const string& title, const string& content);
	diary get_diary_by_id(int id) const;
	vector<diary> get_diaries() const;
	void update_diary(const diary& new_diary);
	void update_diary(int id, const string& date, const string& weather, const string& title, const string& content);
	void erase_diary_by_id(int id);

	void save_diaries() const;
	int get_size() const;

	vector<vector<uint8_t>> serialize_diaries() const;
	void deserialize_diaries(const vector<vector<uint8_t>>& chunks);
};