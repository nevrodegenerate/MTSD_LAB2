#pragma once

#include <iostream>
#include <string>

class char_list {
private:
	std::string name;
	int length;
	char* list;
public:
	char_list operator=(const char_list& new_list);
	char_list(std::string new_name);
	char_list() : char_list("") {};
	char_list(const char_list& new_list);
	char_list(const char_list&& new_list);
	~char_list();
	void SetName(std::string new_name);
	std::string GetName();
	int GetLength();
	void Append(char new_char);
	void AppendAll(std::string new_chars);
	void Insert(char new_char, int index);
	char Delete(int index);
	void DeleteAll(char target);
	char Get(int index);
	char_list Clone();
	void Reverse();
	int FindFirst(char target);
	int FindLast(char target);
	void Clear();
	void Extend(char_list extension);
	void Print();
};