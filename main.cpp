#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>

struct task_struct {
	std::string title;
	std::tm start;
	std::tm end;
	bool bStart = false;
	bool bEnd = false;
};

void convert_sec(double sec) {
	std::cout << "time spent ";
	if (((int)sec / 3600) != 0)
		std::cout << (int)sec / 3600 << "h ";
	if ((((int)sec % 3600) / 60) != 0)
		std::cout << ((int)sec % 3600) / 60 << "m ";
	std::cout << ((int)sec % 3600) % 60 << "s" << std::endl;
}

int main() {
	std::vector<task_struct> task_vec;
	std::string command;

	std::cout << "You have few commands:" << std::endl;
	std::cout << '"' << "begin" << '"' << "\t\tfor begin new task," << std::endl;
	std::cout << '"' << "end" << '"' << "\t\tfor finish current task," << std::endl;
	std::cout << '"' << "status" << '"' << "\tfor display info about all finished tasks," << std::endl;
	std::cout << '"' << "exit" << '"' << "\t\tfor exit from program." << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "Input command:";
	std::cin >> command;
	while (command != "exit") {
		if (command == "begin") {
			if (!task_vec.empty()) {
				int count_started = 0;
				for (int i = 0; i < task_vec.size(); i++) {
					if (task_vec[i].bStart) {
						task_vec[i].bStart = false;
						std::time_t timeNow = std::time(nullptr);
						task_vec[i].end = *std::localtime(&timeNow);
						task_vec[i].bEnd = true;
						std::cout << "Task " << '"' << task_vec[i].title << '"' << " is ended" << std::endl;
					}
				}
			}
			task_struct task;
			std::string in_str;
			std::cout << "Input title of new task:";
			std::getline(std::cin, in_str) >> task.title;
			std::time_t timeNow = std::time(nullptr);
			task.start = *std::localtime(&timeNow);
			task.bStart = true;
			task_vec.push_back(task);
		} else if (command == "end") {
			if (!task_vec.empty()) {
				for (int i = 0; i < task_vec.size(); i++) {
					if (task_vec[i].bStart) {
						task_vec[i].bStart = false;
						std::time_t timeNow = std::time(nullptr);
						task_vec[i].end = *std::localtime(&timeNow);
						task_vec[i].bEnd = true;
						std::cout << "Task " << '"' << task_vec[i].title << '"' << " is ended" << std::endl;
					}
				}
			} else
				std::cout << "No tasks started yet!" << std::endl;
		} else if (command == "status") {
			if (!task_vec.empty()) {
				double diff_sec;
				double diff_sec_total = 0;
				for (int i = 0; i < task_vec.size(); i++) {
					if (task_vec[i].bEnd) {
						diff_sec = difftime(std::mktime(&task_vec[i].end),
											 std::mktime(&task_vec[i].start));
						std::cout << i << ". Task " << '"' << task_vec[i].title << '"' << std::endl;
						convert_sec(diff_sec);
					}
				}
			} else
				std::cout << "No tasks started yet!" << std::endl;
		}
		std::cout << "-----------------------------------" << std::endl;
		std::cout << "Input command:";
		std::cin >> command;
	}
	return 0;
}
