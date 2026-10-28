#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <limits>
#include <cctype>


class Task {
private:
	int id;
	std::string name;
	bool simple_status = false ;
public:
	explicit Task(int id, std::string name)
		:id(id),name(std::move(name))
	{
		
		
	}

	int getId() const
	{
		return id;
	}

	const std::string& getName() const {
		return name;
	}

	bool getCompleted() const {
		return simple_status;
	}
	
};

class TaskManager  {
private:
	std::vector<Task> tasks = {};
	int counter = 1;
public:
	void addTask(std::string name) {
		tasks.emplace_back(counter, std::move(name));
		counter++;
		
	}

	

	 void showTasks()const 
	 {
		 if (tasks.empty()) {
		 
			 std::cout << "Task list is empty." << '\n';
		}
		 else {
			 for (const Task& task : tasks) {

				 std::cout << "ID: " << task.getId() << " | " << "Name: " << task.getName() << '\n';

			 }
		 }
			 
		 
	}

	 bool removeTask(int id) {
		
		 auto result = std::erase_if(tasks, [id](const Task& task)
			 {
				return task.getId() == id;
			 });

		 return result > 0;
	 }

	


};

void Space() {
	std::cout << '\n' << '\n';
}


int main() {

	system("chcp 1251>nul");

	 int command;
	std::string name = "";
	 int remove;
	std::cout << "Здравствуйте. Добро пожаловать в Менеджер задач. Пожалуйста выберите дальнейшие действия, для этого воспользуйтесь следующими возможностями\n";
	

	TaskManager tm;

	do {
		std::cout << "0 - Выход\n" << "1 - Добавить задачу\n" << "2 - Вывести на экран ваши задачи в данный момент\n" << "3 - удалить задачу\n";
		
		std::cin >> command;
		

		if (std::cin.eof())
		{
			std::cout << "Ввод завершён!\n";
			return 0;
		}

		else if (std::cin.fail()) {
			std::cout << "Некорректный ввод!\n";
			std::cin.clear();
			std::cin.ignore(
				std::numeric_limits<std::streamsize>::max(),
				'\n'
			);
			command = -1;
			continue;
		}
		else {
			switch (command) {
			case 0:
				std::cout << "Выход\n";
				break;
			case 1:

				std::cout << "Введите пожалуйста задачу:)\n";
				std::cin.ignore(
					std::numeric_limits<std::streamsize>::max(),
					'\n'
				);
				std::getline(std::cin, name);
				if (std::cin.eof()) {
					std::cout << "Вывод завершён!\n";
					return 0;
				}
				else if (
					std::all_of(
						
						name.begin(),
						name.end(),
						[](unsigned char enter)
						{
							return std::isspace(enter);
						}
					)
					) {
					std::cout << "Название не может быть пустым.Попробуйте ещё раз:)\n";
				}
				else {
					tm.addTask(name);
					std::cout << "Задача успешно добавлена:)\n";
				}
				break;
			case 2:
				tm.showTasks();
				break;
			case 3:
			
				std::cout << "Введите пожалуйста задачу которую хотите удалить:)\n";
				std::cin >> remove;

				if (std::cin.eof())
				{
					std::cout << "Ввод завершён!\n";
					return 0;
				}
				else if (std::cin.fail()) {
					std::cout << "Некорректный ввод!\n";
					std::cin.clear();
					std::cin.ignore(
						std::numeric_limits<std::streamsize>::max(),
						'\n'
					);
					continue;
				}

				if (!tm.removeTask(remove))
				{
					std::cout << "Задача с указанным ID не найдена:(\n";
				}
				else {

					std::cout << " Задача №:" << remove << " удалена!\n";
				}
				break;
			default:
				std::cout << "Введено некорректное значение!" << '\n';
			}
		}
	} while (command != 0);


	return 0;
}