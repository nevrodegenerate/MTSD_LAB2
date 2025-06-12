#include "char_list.h"

char_list char_list::operator=(const char_list& new_list) {
	name = new_list.name;
	length = new_list.length;
	list = new char[length];
	for (int i = 0; i < length; i++) {
		list[i] = new_list.list[i];
	}
	return *this;
}

char_list::char_list(std::string new_name) {
	name = new_name;
	length = 0;
	list = nullptr;
}

char_list::char_list(const char_list& new_list) {
	name = new_list.name;
	length = new_list.length;
	list = new char[length];
	for (int i = 0; i < length; i++) {
		list[i] = new_list.list[i];
	}
}

char_list::char_list(const char_list&& new_list) {
	name = new_list.name;
	length = new_list.length;
	list = new char[length];
	for (int i = 0; i < length; i++) {
		list[i] = new_list.list[i];
	}
}

char_list::~char_list() {
	list = nullptr;
	delete[] list;
}

void char_list::SetName(std::string new_name) {
	name = new_name;
}

std::string char_list::GetName() {
	return name;
}

int char_list::GetLength() {
	return length;
}

void char_list::Append(char new_char) {}

void char_list::AppendAll(std::string new_chars) {
	for (int i = 0; i < new_chars.length(); i++) {
		Append(new_chars[i]);
	}
}

void char_list::Insert(char new_char, int index) {}

char char_list::Delete(int index) {
	return '0';
}

void char_list::DeleteAll(char target) {
	int index = FindFirst(target);
	while (index != -1) {
		Delete(index);
		index = FindFirst(target);
	}
}

char char_list::Get(int index) {
	return list[index];
}

char_list char_list::Clone() {
	return std::move(*this);
}

void char_list::Reverse() {}

int char_list::FindFirst(char target) {
	return -1;
}

int char_list::FindLast(char target) {
	return -1;
}

void char_list::Clear() {
	length = 0;
	list = nullptr;
}

void char_list::Extend(char_list extension) {}

void char_list::Print() {
	for (int i = 0; i < length; i++) {
		std::cout << list[i];
	}
}