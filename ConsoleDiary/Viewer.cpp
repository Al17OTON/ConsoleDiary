#include "Viewer.h"
#include <iostream>

void viewer::show_diaries(const repository& repo)
{
	vector<diary> diaries = repo.get_diaries();

	for (int i = 0; i < diaries.size(); ++i) 
	{
		if (diaries[i].get_is_delete()) continue;
		cout << diaries[i].to_string_short() << "\n";
	}
}

void viewer::show_diary_by_id(const repository& repo, int id) 
{
	cout << repo.get_diary_by_id(id).to_string() << "\n";
}

void viewer::show_inputs(const repository& repo)
{
	cout << "1. 일기 보기  2. 일기 작성하기  3. 수정하기  4. 삭제하기  5. 저장하기  6. 종료\n>> ";
}

void viewer::show_select()
{
	cout << "선택할 일기의 아이디를 입력해주세요.\n>> ";
}
