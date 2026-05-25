#pragma once

#include "Repository.h"

using namespace std;

class viewer 
{
public:
	static void show_diaries(const repository& repo);
	static void show_diary_by_idx(const repository& repo, int idx);
	static void show_inputs(const repository& repo);
	static void show_select();

};