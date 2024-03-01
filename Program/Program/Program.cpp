#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Node {
	//string key = "";
	char* key = new char[1];
	Node* ptr_to_prev_node = nullptr;
	Node* ptr_to_next_node = nullptr;
};

struct List {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
	int size = 0;
};

void delete_key(List& list, char key) {
	if (list.head_node == nullptr) {
		cout << "List is empty" << endl;
		return;
	}

	Node* remove_node = list.head_node;
	while ((*(remove_node->key) != key) && (remove_node != nullptr)) {
		remove_node = remove_node->ptr_to_next_node;
	}

	if (remove_node == nullptr) {
		cout << "No key found" << endl;
		return;
	}

	//???
	if ((list.head_node == remove_node) && (list.tail_node == remove_node)) {
		list.head_node = nullptr;
		list.tail_node = nullptr;
	}
	else if (list.head_node == remove_node) {
		list.head_node = remove_node->ptr_to_next_node;
		remove_node->ptr_to_next_node->ptr_to_prev_node = nullptr;
	}
	else if (list.tail_node == remove_node) {
		list.tail_node = remove_node->ptr_to_prev_node;
		remove_node->ptr_to_prev_node->ptr_to_next_node = nullptr;
	}
	else {
		remove_node->ptr_to_next_node->ptr_to_prev_node = remove_node->ptr_to_prev_node;
		remove_node->ptr_to_prev_node->ptr_to_next_node = remove_node->ptr_to_next_node;
	}

	delete remove_node;

}

void add_node(List& list, int index, char str) {
	Node* new_node = new Node;
	*(new_node->key) = str;

	list.size++;

	if (list.head_node == nullptr) {
		list.head_node = new_node;
		list.tail_node = new_node;
		return;
	}

	if ((index == -1) || (index == 0)) {
		new_node->ptr_to_next_node = list.head_node;
		list.head_node->ptr_to_prev_node = new_node;
		list.head_node = new_node;
		return;
	}

	int counter = 0;
	int from_tail = list.size - 2 - index;
	Node* current_node;
	
	if (index < from_tail) {
		current_node = list.head_node;
		while (counter != index) {
			current_node = current_node->ptr_to_next_node;
			++counter;
		}
	}
	else{
		current_node = list.tail_node;
		while (counter != from_tail) {
			current_node = current_node->ptr_to_prev_node;
			++counter;
		}
	}

	new_node->ptr_to_next_node = current_node;
	new_node->ptr_to_prev_node = current_node->ptr_to_prev_node;
	current_node->ptr_to_prev_node->ptr_to_next_node = new_node;
	current_node->ptr_to_prev_node = new_node;


}

void print_list(List& list) {
	Node* current_node = list.head_node;

	if (current_node == nullptr) {
		cout << "List is empty" << endl;
		return;
	}

	while (current_node != nullptr) {
		cout << *(current_node->key) << "; ";
		current_node = current_node->ptr_to_next_node;
	}
	
	cout << endl;

	delete current_node;
}

void list_filesave(List& list) {
	Node* current_node = list.tail_node;

	ofstream f("list_savestate.dat");

	while (current_node != nullptr){
		f << current_node->key << "\n";
		current_node = current_node->ptr_to_prev_node;
	}

	f.close();
}

void list_fileread(List& list) {
	char buffer_char[1];
	string buffer_str;

	ifstream f("list_savestate.dat");

	while (!f.eof()) {
		getline(f, buffer_str);
		buffer_char[0] = buffer_str[0];
		if (buffer_str != "") {
			add_node(list, -1, buffer_str[0]);
		}
	}

	f.close();
}

void list_delete(List& list) {
	Node* remove_node;

	while ((list).head_node != nullptr) {
		remove_node = (list).head_node;
		(list).head_node = (list).head_node->ptr_to_next_node;
		delete remove_node;
	}

	list.size = 0;
}

int main() {
	int n, k;
	string str;
	char ch[1];
	List list;
	
	cout << "Enter number of elements that will be entered on list creation: ";
	cin >> n;
	cin.ignore();

	for (int i = 1; i <= n; ++i) {
		cout << "Enter key for element: ";
		getline(cin, str);
		ch[0] = str[0];
		add_node(list, -1, ch[0]);
	}

	print_list(list);

	cout << "Enter key for deletion: ";
	getline(cin, str);
	ch[0] = str[0];
	delete_key(list, ch[0]);
	print_list(list);

	cout << "Enter index of element for adding and number (K) of entering element: ";
	cin >> n >> k;
	cin.ignore();

	for (int i = 1; i <= k; ++i) {
		cout << "Enter key for element: ";
		getline(cin, str);
		ch[0] = str[0];
		add_node(list, n, ch[0]);
	}
	print_list(list);

	cout << "List saved in file" << endl;
	list_filesave(list);
	list_delete(list);
	print_list(list);

	cout << "List restored from file" << endl;
	list_fileread(list);
	print_list(list);

	list_delete(list);


	return 0;
}