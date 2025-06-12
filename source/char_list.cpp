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

void char_list::Append(char new_char) {
	list_element* new_element = new list_element(new_char);

	if (!length) {
		start = end = new_element;
		new_element->next_elem = new_element;
	}
	else {
		end->next_elem = new_element;
		end = new_element;
		new_element->next_elem = start;
	}
	length++;
}

void char_list::AppendAll(std::string new_chars) {
	for (int i = 0; i < new_chars.length(); i++) {
		Append(new_chars[i]);
	}
}

void char_list::Insert(char new_char, int index) {
	if (index < 0 || index > length - 1) {
		throw std::invalid_argument("Index out of range");
	}
	list_element* new_elem = new list_element(new_char);
	list_element* temp1 = start;
	list_element* temp2 = temp1->next_elem;

	for (int i = 0; i < index; i++) {
		temp1 = temp1->next_elem;
	}
	for (int i = 0; i < length; i++) {
		if (temp2->next_elem == temp1) {
			temp2->next_elem = new_elem;
			break;
		}
		temp2 = temp2->next_elem;
	}

	if (!index) {
		start = new_elem;
	}
	else if (index = length - 1) {
		end = new_elem;
	}

	new_elem->next_elem = temp1;
	length++;
}

char char_list::Delete(int index) {
	if (index < 0 || index > length - 1) {
		throw std::invalid_argument("Index out of range");
	}

	list_element* temp = start;
	char target = temp->next_elem->item;

	for (int i = 0; i < index - 1; i++) {
		temp = temp->next_elem;
		target = temp->next_elem->item;
	}

	if (!index) {
		target = start->item;
		start = temp->next_elem;
	}
	else if (index == length - 1) {
		list_element* new_end = start;
		for (int i = 0; i < length - 2; i++) {
			new_end = new_end->next_elem;
		}
		end = new_end;
	}

	temp->next_elem = temp->next_elem->next_elem;
	length--;

	return target;
}

void char_list::DeleteAll(char target) {
	int index = FindFirst(target);

	while (index != -1) {
		Delete(index);
		index = FindFirst(target);
	}
}

char char_list::Get(int index) {
	if (index < 0 || index > length - 1) {
		throw std::invalid_argument("Index out of range");
	}

	list_element* temp = start;

	for (int i = 0; i < index; i++) {
		temp = temp->next_elem;
	}

	return temp->item;
}

char_list char_list::Clone() {
	return std::move(*this);
}

void char_list::Reverse() {
	list_element* temp1 = start;
	list_element* temp2 = end;
	list_element* temp3 = temp1->next_elem;
	start = temp2;
	end = temp1;

	for (int i = 0; i < length; i++) {
		temp3 = temp1->next_elem;
		for (int j = 0; j < length - 3; j++) {
			temp1->next_elem = temp1->next_elem->next_elem;
		}
		temp1->next_elem = temp2;
		temp2 = temp1;
		temp1 = temp3;
	}
}

int char_list::FindFirst(char target) {
	list_element* temp = start;

	for (int i = 0; i < length; i++) {
		if (temp->item == target) {
			return i;
		}
		temp = temp->next_elem;
	}

	return -1;
}

int char_list::FindLast(char target) {
	list_element* temp = start;
	int index = -1;

	for (int i = 0; i < length; i++) {
		if (temp->item == target) {
			index = i;
		}
		temp = temp->next_elem;
	}

	return index;
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