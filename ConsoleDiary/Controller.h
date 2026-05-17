#pragma once

#include "Repository.h"

class controller 
{
public:
	static void create_diary(repository& repo);
	static void read_diary(const repository& repo);
	static void update_diary(repository& repo);
	static void remove_diary(repository& repo);
	static void save_diaries(const repository& repo);
};