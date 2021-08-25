#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

std::map<int, std::pair<char, std::string>> tasks;
int i = 1;

void input_all_in_file(std::string& file_name) {
	std::ofstream os;
	os.open(file_name, std::ios::trunc);
	for (int j = 1; j < i; j++)
	{
		os << tasks[j].first << j << ' ' << tasks[j].second;
		if (j+1!=i)
		{
			os << '\n';
		}
	}
}

int checking(const std::string& s) {
	int num = -1;
	std::string tmp;
	std::stringstream stream;
	stream << s;
	stream >> tmp;
	stream >> tmp;
	if (tmp!=":")
	{
		std::cout << "there's no \":\" in command";
	}
	stream >> tmp;
	if (tmp == "all")
	{
		return 0;
	}
	else {
		stream.clear();
		stream << tmp;
		stream >> num;
		if (!(num > 0 && num < i)) {
			std::cout << "wrong number\n";
			num = -1;
		}
	}
	return num;
}

void get_all_tasks(const std::string& file_name) {
	std::ifstream is;
	is.open(file_name);
	if (is.is_open()) {
		std::string tmp;
		while (!is.eof() && std::getline(is, tmp)) {
			tasks[i].first = tmp[0];
			tmp.erase(0, 3);
			tasks[i].second += tmp;
			++i;
		}
	}
	is.close();
}

void create(const std::string& s) {
	tasks[i] = std::make_pair('-', s);
	++i;
}

void remove(const int num) {
	if (i - 1 != num) {
		tasks[num] = tasks[i - 1];
	}
	tasks.erase(i-1);
	--i;
}

void remove_all() {
	tasks.clear();
	i = 1;
}

void done(const int num) {
	if (tasks[num].first == '+')
	{
		std::cout << "Task has already done\n";
		return;
	}
	tasks[num].first = '+';
}

void done_all() {
	for (int j = 0; j < i; j++)
	{
		tasks[j].first = '+';
	}
}

void print_all() {
	if (tasks.begin() == tasks.end()) {
		std::cout << "you don't have tasks for today\n";
		return;
	}
	for (int j = 1; j < i; j++)
	{
		std::cout << tasks[j].first << ' ' << j << ". " << tasks[j].second << '\n';
	}
}

void print(const int num) {
	std::cout << tasks[num].first << ' ' << num << ". " << tasks[num].second << '\n';
}

void organizer(const std::string& all_text) {
	std::stringstream stream;
	stream << all_text;
	std::string command;
	stream >> command;
	if (command == "create") {
		stream >> command;
		if (command != ":")
		{
			std::cout << "there's no \":\" in command\n";
			return;
		}
		std::string tmp;
		while (stream>>command)
			tmp += command + ' ';
		create(tmp);
	}
	else if (command == "done") {
		int num = checking(all_text);
		if (num == -1) 
			std::cout << "wrong parametrs after \":\"\n";
		else if (num == 0)
			done_all();
		else
			done(num);
	}
	else if (command == "remove") {
		int num = checking(all_text);
		if (num == -1) 
			std::cout << "wrong parametrs after \":\"\n";
		else if (num == 0)
			remove_all();
		else
			remove(num);
	}
	else if (command == "print") {
		int num = checking(all_text);
		if (num == -1) 
			return;
		else if (num == 0)
			print_all();
		else
			print(num);
	}
	else {
		std::cout << "wrong command\n";
	}
}
