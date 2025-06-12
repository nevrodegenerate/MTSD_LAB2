#include "char_list.h"

list_element::list_element(char new_item) {
	item = new_item;
	next_elem = nullptr;
}

char_list char_list::operator=(const char_list& new_list) {
	name = new_list.name;
	length = new_list.length;
	start = new_list.start;
	end = new_list.end;
	return *this;
}

char_list::char_list(std::string new_name) {
	name = new_name;
	length = 0;
	start = nullptr;
	end = nullptr;
}

char_list::char_list(const char_list& new_list) {
	name = new_list.name;
	length = new_list.length;
	start = new_list.start;
	end = new_list.end;
}

char_list::char_list(const char_list&& new_list) {
	name = new_list.name;
	length = new_list.length;
	start = new_list.start;
	end = new_list.end;
}

char_list::~char_list() {}

void char_list::SetName(std::string new_name) {
	name = new_name;
}

std::string char_list::GetName() {
	return name;
}

int char_list::GetLength() {
	return length;
}

void char_list::Append(char new_char) { }

void char_list::AppendAll(std::string new_chars) {
	for (int i = 0; i < new_chars.length(); i++) {
		Append(new_chars[i]);
	}
}

void Insert(char new_char, int index){}

char char_list::Delete(int index) {
	if (!index || index > length) {
		throw std::invalid_argument("Index out of range");
	}
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
	if (!index || index > length) {
		throw std::invalid_argument("Index out of range");
	}
	return '0';
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
	start = nullptr;
	end = nullptr;
}

void char_list::Extend(char_list extension) {
	for (int i = 0; i < extension.length; i++) {
		Append(extension.Get(i));
	}
}

void char_list::Print() {
	list_element* temp = start;

	for (int i = 0; i < length; i++) {
		std::cout << temp->item;
		temp = temp->next_elem;
	}
}