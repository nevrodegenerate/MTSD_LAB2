#include "interface.h"

using namespace std;

list_interface::list_interface() {
    count = 0;
    lists = nullptr;
};

list_interface::~list_interface() {
    delete[] lists;
    lists = nullptr;
}

void list_interface::display() {
    cout << "Lists:\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ") " << lists[i].GetName() << ": ";
        lists[i].Print();
        cout << "\n";
    }
    cout << "\n";
}

int list_interface::list_loop() {
    int menu = 1;
    string name;
    do {
        display();
        cout << "1. Select and edit a list\n"
            << "2. Create a new list\n"
            << "3. Remove a list\n"
            << "4. Copy a list\n"
            << "0. Exit program\n";
        cin.clear();
        cin >> menu;
        switch (menu) {
        case 1:
            cout << "Enter list index:\n";
            cin >> menu;
            if (menu > 0 && menu <= count) {
                operation_loop(menu - 1);
            }
            else {
                cout << "Index out of range\n";
            }
            menu = 1;
            break;
        case 2:
            cout << "Enter new list name:\n";
            cin.ignore();
            getline(cin, name);
            add_list(char_list(name));
            break;
        case 3:
            cout << "Enter index of removed list:\n";
            cin >> menu;
            if (menu > 0 && menu <= count) {
                del_list(menu - 1);
            }
            else {
                cout << "Index out of range\n";
                cin.ignore();
                getline(cin, name);
            }
            menu = 3;
            break;
        case 4:
            cout << "Enter list index to copy:\n";
            cin >> menu;
            if (menu > 0 && menu <= count) {
                copy_list(menu - 1);
            }
            else {
                cout << "Index out of range\n";
            }
            menu = 4;
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "Wrong input\n";
            break;
        }
    } while (menu);
    return 0;
}

int list_interface::operation_loop(int index) {
    string name;
    int menu = 1;
    do {
        display();
        cout << "1. Add an element to the list\n"
            << "2. Add multiple elements to the list\n"
            << "3. Insert an element into the list\n"
            << "4. Remove an element by its index\n"
            << "5. Remove all instances of a single element from the list\n"
            << "6. Remove all elements from the list\n"
            << "7. Get an element by its index\n"
            << "8. Find first instance of an element in the list\n"
            << "9. Find last instance of an element in the list\n"
            << "10. Reverse all elements in the list\n"
            << "11. Add elements of another list\n"
            << "0. Back\n";
        cin.clear();
        cin >> menu;
        switch (menu) {
        case 1:
            cout << "Enter a new element (only first character counts):\n";
            cin.ignore();
            getline(cin, name);
            lists[index].Append(name[0]);
            break;
        case 2:
            cout << "Enter a string to add:\n";
            cin.ignore(); 
            getline(cin, name);
            lists[index].AppendAll(name);
            break;
        case 3:
            cout << "Enter a new element (only first character counts):\n";
            cin.ignore(); 
            getline(cin, name);
            cout << "Enter index of the new element:\n";
            cin >> menu;
            lists[index].Insert(name[0], menu);
            menu = 3;
            break;
        case 4:
            cout << "Enter index of the element to remove:\n";
            cin >> menu;
            lists[index].Delete(menu);
            menu = 3;
            break;
        case 5:
            cout << "Enter element to remove (only first character counts):\n";
            cin.ignore(); 
            getline(cin, name);
            lists[index].DeleteAll(name[0]);
            break;
        case 6:
            lists[index].Clear();
            cout << "All elements have been removed\n"; 
            break;
        case 7:
            cout << "Enter index of the element:\n";
            cin >> menu;
            cout << lists[index].Get(menu) << " is your element\n";
            menu = 3;
            break;
        case 8:
            cout << "Enter element to find (only first character counts):\n";
            cin.ignore(); 
            getline(cin, name);
            cout << "The first index of " << name[0] << " is " << lists[index].FindFirst(name[0]) << "\n";
            break;
        case 9:
            cout << "Enter element to find (only first character counts):\n";
            cin.ignore(); 
            getline(cin, name);
            cout << "The last index of " << name[0] << " is " << lists[index].FindLast(name[0]) << "\n";
            break;
        case 10:
            lists[index].Reverse();
            cout << "The list elements have been reversed\n";
            break;
        case 11:
            cout << "Enter index of the list to add to the current list:\n";
            cin >> menu;
            if (menu > 0 && menu <= count) {
                lists[index].Extend(lists[menu - 1]);
                cout << "List " << index << " has been expanded\n";
            }
            else {
                cout << "Index out of range\n";
            }
            menu = 11;
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "Wrong input\n";
            break;
        }
    } while (menu);
    return 0;
};

void list_interface::add_list(char_list new_elem) {
    char_list* new_list = new char_list[++count];

    for (int i = 0; i < count - 1; i++) {
        new_list[i] = lists[i];
    }

    new_list[count - 1] = new_elem;

    delete[] lists;
    lists = new_list;
}

void list_interface::del_list(int index) {
    char_list* new_list = new char_list[--count];

    for (int i = 0; i < index; i++) {
        new_list[i] = lists[i];
    }

    for (int i = index; i < count; i++) {
        new_list[i] = lists[i + 1];
    }

    delete[] lists;
    lists = new_list;
}

void list_interface::copy_list(int index) {
    char_list* new_list = new char_list[++count];

    for (int i = 0; i < count - 1; i++) {
        new_list[i] = lists[i];
    }

    new_list[count - 1] = lists[index].Clone();

    delete[] lists;
    lists = new_list;
};