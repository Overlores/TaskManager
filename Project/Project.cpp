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

	void setStatus(bool status)
	{
		 simple_status = status;
	}
	void setName(std::string newName)
	{
		
		name = std::move(newName);
	};

	
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

				 std::cout << "ID: " << task.getId() << " | " << "Name: " << task.getName();
				 if (task.getCompleted())
				 {
					 std::cout << " | " << "Status: " << "Completed" << '\n';
				 }
				 else
				 {
					 std::cout << " | " << "Status: " << "Not completed" << '\n';
				 }
				 

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


	
	 bool changeTaskStatus(int id,bool status) {

		 auto it = std::find_if(
			 tasks.begin(),
			 tasks.end(),
			 [id](const Task& rest) {
				 return rest.getId() == id;
			 }
		 );

		 if (it == tasks.end())
		 {
			
			 return false;
		 }
		 else {
			it->setStatus(status);
			return true;
		 }
	 }

	 bool changeTaskName(int id, std::string newName)
	 {
		 auto it = std::find_if(
			 tasks.begin(),
			 tasks.end(),
			 [id](const Task& rest) {
				 return rest.getId() == id;
			 }
		 );

		 if (it == tasks.end())
		 {
			 return false;
		 }
		 else {
			 it->setName(std::move(newName));
			 return true;
		 }
	 }

	 bool findTaskById(int id) const
	 {
		 auto it = std::find_if(
			 tasks.cbegin(),
			 tasks.cend(),
			 [id](const Task& vist) {
				 return vist.getId() == id;
			 }
		 );

		 if (it == tasks.end())
		 {
			 return false;
		 }
		 else {
			 std::cout << "ID: " << it->getId();
			 std::cout << " | " << "Name: " << it->getName();

			 if (it->getCompleted()) {
				 std::cout << " | " << "Status: Completed\n";
			 }
			 else
			 {
				 std::cout << " | " << "Status: Not completed\n";
			 }
			 return true;
		 }

	 }

	 bool findTasksByName(const std::string& searchName) const
	 {
		 bool found = false;

		 for (const Task& task : tasks)
		 {
			 if (task.getName().contains(searchName))
			 {
				 std::cout << "ID: " << task.getId();
				 std::cout << " | " << "Name: " << task.getName();
				 if (task.getCompleted())
				 {
					 std::cout << " | Status: Completed\n";
				 }
				 else {
					 std::cout << " | Status: Not Completed\n";
				 }
				 found = true;

			 }
			 
		 }
		 return found;
	 }

};

void Space() {
	std::cout << '\n' << '\n';
}


int main() {

	system("chcp 1251>nul");

	 int command;
	std::string name = "";
	 int taskId;
	std::cout << "Здравствуйте. Добро пожаловать в Менеджер задач. Пожалуйста выберите дальнейшие действия, для этого воспользуйтесь следующими возможностями:)\n";
	int status;

	TaskManager tm;

	do {
		std::cout << "0 - Выход\n" << "1 - Добавить задачу\n" << "2 - Вывести на экран ваши задачи в данный момент\n" << "3 - Удалить задачу\n" << "4 - Изменить статус задачи\n";
		std::cout << "5 - Изменить название задачи\n" << "6 - Найти задачу по ID\n" << "7 - найти задачу по названию\n";
		std::cout << "Ваше действие: ";
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
				std::cin >> taskId;

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

				if (!tm.removeTask(taskId))
				{
					std::cout << "Задача с указанным ID не найдена:(\n";
				}
				else {

					std::cout << " Задача №:" << taskId << " удалена!\n";
				}
				break;
			case 4:
				std::cout << "Введите id задачи: " << '\n';
				std::cin >> taskId;

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
				std::cout << "Выберите статус задачи: 0 - задача не выполнена!, 1 - задача выполнена! :)" << '\n';
				std::cin >> status;
				
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

				if (status != 0 && status != 1)
				{
					std::cout << "Недопустимый статус:(\n";
					break;
				}

				if (tm.changeTaskStatus(taskId, status))
				{
					std::cout << "Статус задачи успешно изменен!:)\n";
				}
				else {
					std::cout << "Задача не найдена!:(\n";
				}
				break;
			case 5:
				std::cout << "Введите Id задачи пожалуйста:)\n";
				std::cin >> taskId;
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

				std::cin.ignore(
					std::numeric_limits<std::streamsize>::max(),
					'\n'
				);

				if (std::cin.eof())
				{
					std::cout << "Ввод завершён!\n";
					return 0;
				}

				std::cout << "Введите новое название задачи пожалуйста:)\n";
				std::getline(std::cin, name);
				if (std::cin.eof()) {
					std::cout << "Ввод завершён!\n";
					return 0;
				}
				else if (std::cin.fail()) {
					std::cout << "Ошибка чтения названия задачи:(\n";
					return 1;
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
					if (tm.changeTaskName(taskId, name)) {
						std::cout << "Название успешно изменено:)\n";
					}
					else {
						std::cout << "Не удалось изменить задачу:(\n";
					}
				}
				break;
			case 6:
				std::cout << "Введите ID задачи пожалуйста:)" << '\n';
				std::cin >> taskId;
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

				std::cin.ignore(
					std::numeric_limits<std::streamsize>::max(),
					'\n'
				);

				if (std::cin.eof())
				{
					std::cout << "Ввод завершён!\n";
					return 0;
				}

				if (!tm.findTaskById(taskId))
				{
					std::cout << "Задача не найдена:(\n";
				}
				break;
			case 7:
				std::cout << "Введите название задачи:)\n";
				std::cin.ignore(
					std::numeric_limits<std::streamsize>::max(),
					'\n'
				);
				std::getline(std::cin, name);
				if (std::cin.eof()) {
					std::cout << "Ввод завершён!\n";
					return 0;
				}
				else if (std::cin.fail()) {
					std::cout << "Ошибка чтения названия задачи:(\n";
					return 1;
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
					if (!tm.findTasksByName(name))
					{
						std::cout << "Задача не найдена:(\n";
					}
				}
				break;
			default:
				std::cout << "Введено некорректное значение!:(\n";
			}
		}
	} while (command != 0);


	return 0;
}