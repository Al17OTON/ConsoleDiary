#pragma once
#include <vector>
#include <set>
#include "Diary.h"

using namespace std;

class repository 
{
private:
	set<diary> m_diaries;
	repository();
	~repository();

	int generate_id() const;
	bool check_id_exist(int id) const;

	static repository* m_instance;

	repository(const repository&) = delete;
	repository& operator=(const repository&) = delete;

public:
	static repository* get_instance();
	static void delete_instance();

	void insert_diary(const diary& new_diary);
	void insert_diary(const string& date, const string& weather, const string& title, const string& content);
	diary get_diary_by_id(int id) const;
	vector<diary> get_diaries() const;
	void update_diary(const diary& new_diary);
	void update_diary(int id, const string& date, const string& weather, const string& title, const string& content);
	void erase_diary_by_id(int id);

	void save_diaries_binary() const;
	void save_diaries_csv() const;
	int get_size() const;

	vector<vector<uint8_t>> serialize_diaries_binary() const;
	void deserialize_diaries_binary(const vector<vector<uint8_t>>& chunks);
	vector<vector<string>> serialize_diaries_csv() const;
	void deserialize_diaries_csv(const vector<vector<string>>& chunks);
};