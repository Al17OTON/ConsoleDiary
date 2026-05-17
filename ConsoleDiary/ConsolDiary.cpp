#include <iostream>
#include <string>
#include <cstdlib>
#include "Repository.h"
#include "Viewer.h"
#include "Controller.h"

using namespace std;

int main()
{
    repository& repo = repository::get_instance();
    bool flag = true;
    while (flag) {
        system("cls");
        int input;
        viewer::show_diaries(repo);
        viewer::show_inputs(repo);

        if (!(cin >> input)) 
        {
            // cin 실패 상태 초기화
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // pause 없이 처음부터 다시
        }

        // 버퍼에 남은 개행 제거
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(input) 
        {
            case 1: 
            {
                controller::read_diary(repo);
                break;
            }
            case 2: 
            {
                controller::create_diary(repo);
                break;
            }
            case 3: 
            {
                controller::update_diary(repo);
                break;
            }
            case 4: 
            {
                controller::remove_diary(repo);
                break;
            }
            case 5: 
            {
                controller::save_diaries(repo);
                break;
            }
            case 6: 
            {
                flag = false;
                break;
            }
        }

        system("pause");
    }
}
