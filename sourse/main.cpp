#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "to_do_list.h"

int main()
{
	std::string file_name = "todo_list.txt";
	td_list::get_all_tasks(file_name);
	std::string command, parametrs;
	while (true) {
		std::cout << "-> ";
		std::cin >> command;
		if (command == "exit")
			break;
		std::getline(std::cin, parametrs);
		td_list::organizer(command + parametrs);
	}
	td_list::input_all_in_file(file_name);
}
