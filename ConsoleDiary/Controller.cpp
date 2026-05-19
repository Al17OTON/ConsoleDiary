#include "Controller.h"
#include "Viewer.h"
#include <iostream>

// TODO : 구조체 기반 입력으로 변경
// 중복 코드를 없애기 위해 repositoty에서 구조체의 id값을 기반으로 스마트하게 처리
// 이미 있는 id -> update, 없는 id -> create
void controller::create_diary(repository& repo) 
{
    string date, weather, title, content;
    cout << "제목 : ";
    getline(cin, title);
    cout << "날짜 : ";
    getline(cin, date);
    cout << "날씨 : ";
    getline(cin, weather);
    cout << "내용 : ";
    getline(cin, content);

    repo.insert_diary(date, weather, title, content);
}

void controller::read_diary(const repository& repo) 
{
    int id;
    viewer::show_select();
    cin >> id;
    viewer::show_diary_by_id(repo, id);
}

void controller::update_diary(repository& repo) 
{
    int id;
    viewer::show_select();
    cin >> id;
    string date, weather, title, content;

    cout << "제목 : ";
    getline(cin, title);
    cout << "날짜 : ";
    getline(cin, date);
    cout << "날씨 : ";
    getline(cin, weather);
    cout << "내용 : ";
    getline(cin, content);

    repo.update_diary(id, date, weather, title, content);
}

void controller::remove_diary(repository& repo) 
{
    int id;
    viewer::show_select();
    cin >> id;
    repo.erase_diary_by_id(id);
}

void controller::save_diaries(const repository& repo)
{
    int select;
	cout << "저장 형식을 선택하세요.\n1. Binary\n2. CSV\n선택 : ";
    cin >> select;

	select == 1 ? repo.save_diaries_binary() : repo.save_diaries_csv();
}
