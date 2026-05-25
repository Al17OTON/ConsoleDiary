#include "Controller.h"
#include "Viewer.h"
#include <iostream>
#include "Diary.h"

// TODO : 구조체 기반 입력으로 변경하여 Update와 통합하기 
// 중복 코드를 없애기 위해 repositoty에서 구조체의 id값을 기반으로 처리
// 이미 있는 id -> update, 없는 id -> create
void controller::create_diary(repository& repo) 
{
	diary::diary_data data;
    
    // TODO : 날짜 입력 기능 추가

    cout << "제목 : ";
    cin.getline(data.m_title, sizeof(data.m_title));

    cout << "날씨 : ";
    cin.getline(data.m_weather, sizeof(data.m_weather));

    cout << "내용 : ";
    cin.getline(data.m_content, sizeof(data.m_content));

    data.m_id = -1;
    data.m_date = time(nullptr);

    repo.insert_diary(data);
}

void controller::read_diary(const repository& repo) 
{
    int id;
    viewer::show_select();
    cin >> id;
    viewer::show_diary_by_idx(repo, id);
}

void controller::update_diary(repository& repo) 
{
    diary::diary_data data;
    vector<diary> diaries = repo.get_diaries();
    int idx;
    viewer::show_select();
    cin >> idx;
    
    if (diaries.size() <= idx)
    {
        cout << "존재하지 않는 일기입니다.\n";
        return;
    }

    data.m_id = diaries[idx].get_id();

    // TODO : 날짜 입력 기능 추가

    cout << "제목 : ";
    cin.getline(data.m_title, sizeof(data.m_title));

    cout << "날씨 : ";
    cin.getline(data.m_weather, sizeof(data.m_weather));

    cout << "내용 : ";
    cin.getline(data.m_content, sizeof(data.m_content));

    data.m_date = diaries[idx].get_date();

    repo.insert_diary(data);
}

void controller::remove_diary(repository& repo) 
{
    int idx;
    viewer::show_select();
    cin >> idx;
	vector<diary> diaries = repo.get_diaries();

    if (diaries.size() <= idx)
    {
		cout << "존재하지 않는 일기입니다.\n";
		return;
    }

    repo.erase_diary_by_id(diaries[idx].get_id());
}

void controller::save_diaries(const repository& repo)
{
    int select;
	cout << "저장 형식을 선택하세요.\n1. Binary\n2. CSV\n선택 : ";
    cin >> select;

    if (select == 1)
    {
        repo.save_diaries_binary();
    }
    else
    {
        //repo.save_diaries_csv();
    }
}
