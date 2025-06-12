#pragma once

#include "char_list.h"

class list_interface {
private:
	int count;
	char_list* lists;
public:
	list_interface();
	~list_interface();
	void display();
	int list_loop();
	int operation_loop(int index);
	void add_list(char_list new_list);
	void del_list(int index);
	void copy_list(int index);
};