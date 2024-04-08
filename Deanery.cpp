#include "Deanery.h"
#include "Student.h"
#include "Group.h"


Deanery::~Deanery()
{
	groups.clear();

}

void Deanery::CreateGroups(const std::string& file_)
{
	std::ifstream file(file_);
	if (!file.is_open()) {
		std::cout << "Файл не может быть открыт" << std::endl;
	}

	else {
		
		char title_[100]{};
		char spec_[100]{};
		while (file >> title_ >> spec_) {
			//смотрим по названию, не добавили ли мы уже эту группу 
			// если в какой-то момент считывание групп из файла будет запущено повторно, ошибки не будет 
			if (findGroup(title_) == nullptr) {
				Group* g = new Group(title_, spec_);
				groups.push_back(g);
			}
		}
		//группа для студентов, которые не могут быть загружены в существующие группы
		if (findGroup("-") == nullptr) { //find()
			Group* g = new Group("-", "-");
			groups.push_back(g);
		}
		std::cout << "\n.....Группы успешно добавлены\n";

	}
	file.close();

}

void Deanery::hireStudents(const std::string& file_)
{
	std::ifstream file(file_);
	if (!file.is_open()) {
		std::cout << "\nФайл не может быть открыт" << std::endl;
	}
	else {
		unsigned int id_;
		char f_[100]{};
		char im_[100]{};
		char o_[100]{};
		char title_[100]{};
		int mark;	

		std::string line;
		int flag = 0;
		if (groups.size() <= 1) {
			std::cout << "\nПожалуйта, выгрузите сначала группы" << std::endl;
			return;
		}
	
		while (!file.eof()) {

			getline(file, line);
			//std::cout<<"\n" << line << "\n";

			std::istringstream iss(line);
			iss >> id_;
			iss >> f_;
			if (strcmp(f_, "\0") != 0) { //считываем только людей с фамилией
				//предотвращая ошибку если несколько строк будут разделены пустой строкой
				iss >> im_;
				iss >> o_;
				iss >> title_;
				if (findGroup(title_) != nullptr) {//ищем, считана ли у нас группа, если нет - студент добавляется в искуственно созданную группу "-"
					//проверяем, нет ли в нашей группе уже этого студента (защита от вызова этой функции во 2 раз)
					Group* gr = findGroup(title_);
					if (gr->find(id_) == nullptr) {

						Student* student = new Student(id_, f_, im_, o_);
						while (iss >> mark) {
							student->add_mark(mark);
						}
						student->add_to_group(findGroup(title_));
						findGroup(title_)->add_stud(student);
						
					}
				}
				else {
					Group* gr = findGroup("-");
					if (gr->find(id_) == nullptr) {
						Student* student = new Student(id_, f_, im_, o_);
						while (iss >> mark) {
							student->add_mark(mark);
						}
						student->add_to_group(findGroup("-"));//Добавляем в группу "-"
						findGroup("-")->add_stud(student);
						
					}				
				}				
			}			
		}
		std::cout << "\n.....Суденты успешно добавлены\n";

	}
	file.close();
}

Group* Deanery::findGroup(const char* title_)
{
	int flag = 0;
	for (int i = 0; i < groups.size(); i++) {
		if (strcmp(groups[i]->getTitle(), title_) == 0) {
			return groups[i];
			
		}	
	}
	
	return nullptr;
	

}

void Deanery::grades()
{
	std::cout << "\n\n  ------- Успеваемость -------";
	std::cout << std::endl;
	
	for (int i = 0; i < groups.size() - 1; i++) {
		std::cout << "\n            " << groups[i]->getTitle();		
		
		std::cout <<"\n  Средняя оценка по группе: " << floor(groups[i]->aver() * 100) / 100 << std::endl;// 2 знака после запятой
		float max = -11;
		float min = 11;
		int otl = 0;
		int plo = 0;
		int hor=0;
		int flag = 0;

		std::vector <Student*> student = groups[i]->getStudents();
		for (int i = 0; i < student.size(); i++) {
			if (student[i]->aver_mark() > max) {
				max = student[i]->aver_mark();
			}
			if (student[i]->aver_mark() < min) {
				min = student[i]->aver_mark();
			}
			if (student[i]->aver_mark() < 4) {
				plo++;
				
			}
			else if (student[i]->aver_mark() < 8) {
				hor++;
			}
			else {
				otl++;
			}
		}
		std::cout << "  Лучший ученик:";
		for (int i = 0; i < student.size(); i++) {
			if (student[i]->aver_mark() == max and (max>min or (max==min and max>=4))) {//защита от того, если в группе 1 ученик
				std::cout << "  " << student[i]->getF() << " " << student[i]->getIm()<<" " << student[i]->aver_mark()<< " ";
				flag = 1;
			}
			
		}
		//делаем красивый вывод, если лучшего ученика нет 
		if (flag == 0) {
			std::cout << "  - ";
			
		}
		flag = 0;
		std::cout << "\n  Больше всех неуспевающий ученик:";
		for (int i = 0; i < student.size(); i++) {
			if (student[i]->aver_mark() == min and (min < max or (max == min and min < 4))) {
				std::cout << "  " << student[i]->getF() << " " << student[i]->getIm() <<" " << student[i]->aver_mark() << " ";
				flag = 1;
			}

		}
		//делаем красивый вывод, если худшего ученика нет 
		if (flag == 0) {
			std::cout << "   - " ;

		}
		std::cout << "\n  " <<  "Отличники: " << otl << "  Хорошисты: " << hor << "  Неуспевающие: " << plo << std::endl;
		student.clear();		
	}
	
}

void Deanery::printUnaccounted()
{
	
	std::vector <Student*> student = groups[groups.size() - 1]->getStudents();
	if (student.size() != 0) {
		std::cout << "\n\n....Студенты, для которых не нашлось загруженных групп,\n   удалите их или укажите, в какой группе они должны быть";

		for (int i = 0; i < student.size(); i++) {
			std::cout << std::endl;
			student[i]->print();
		}
	}
	student.clear();
	

	
}

void Deanery::expel()
{
	std::cout << "\n\n  ------- Отчисление -------";
	std::cout << std::endl;
	
	for (int i = 0; i < groups.size() - 1; i++) {
		int flag = 0;
		std::vector <Student*> student = groups[i]->getStudents();
		std::cout << "\n  Из грууппы " << groups[i]->getTitle() << " отчислены: ";
		for (int j = 0; j < student.size(); j++) {
			if (student[j]->aver_mark() < 4) {
				groups[i]->deleteStudent(student[j]);
				std::cout << std::endl;
		
				student[j]->print();
				
				flag = 1;
			}
		}
		if (flag == 0) {
			std::cout << "-";
		}
		//Выбираем старосту, если вдруг она была удалена
		groups[i]->election();
		std::cout << std::endl;
		student.clear();

	}

}

void Deanery::printGroupWithoutStudents()
{
	std::cout<<"\n  ------- Группы -------";
	std::cout << std::endl;
	for (int i = 0; i < groups.size()-1; i++) {// -1, так как не выводим группу "-"
		groups[i]->election();
		groups[i]->print();
		std::cout << std::endl;		
	}
}
void Deanery::printGroupWithStat()
{
	std::cout << "\n  ------- Группы -------";
	std::cout << std::endl;
	for (int i = 0; i < groups.size() - 1; i++) {// -1, так как не выводим группу "-"
		groups[i]->election();
		groups[i]->print_student_with_marks();
		std::cout << std::endl;

	}
}

void Deanery::printGroup()
{
	std::cout << "\n  ------- Группы -------";
	
	for (int i = 0; i < groups.size()-1; i++) {
		std::cout << std::endl;
		groups[i]->election();
		groups[i]->print_student();
	}
}

void Deanery::addMark()
{
	int start = -10;
	int end = 10;
	
	for (int i = 0; i < groups.size() - 1; i++) {
		std::vector <Student*> student = groups[i]->getStudents();
		for (int j = 0; j < student.size(); j++) {

			student[j]->add_mark(rand() % (end - start + 1) + start);

		}
		groups[i]->election();//обновляем старосту каждый раз при изменеии статистики
		student.clear();


	}
	std::cout << "\n\n....Оценки были успешно добавлены\n";
	

}

void Deanery::transfer(const char* f_, const char* title_)
{
	if (this->findGroup(title_) == nullptr) {
		std::cout << "\n....Перевод не осуществлён, ввёденной группы " << title_ << " не существует"<<std::endl;
		return;
	}
	int flag = 0;
	for (int i = 0; i<groups.size(); i++) {
		if (groups[i]->find(f_)!=nullptr ) {
			flag = -1;
			if (groups[i] != findGroup(title_)) { 
				this->findGroup(title_)->add_stud(groups[i]->find(f_));
				this->groups[i]->deleteStudent(groups[i]->find(f_));
				flag = 1;
			}
		}
	}
	if (flag == 0) {
		std::cout << "\n....Перевод не осуществлён, ввёденного студента "<<f_ <<" не существует" << std::endl;
	}
	else if (flag == -1) {
		std::cout << "\n....Студент " << f_ << " уже в "<<title_ <<std::endl;
	}
	else {
		std::cout << "\n....Студент " << f_ << " переведён в группу " << title_ << std::endl;
	}
}

void Deanery::save_stud(const std::string& file_)
{
	std::ofstream file(file_, std::ios::out | std::ios::trunc);//открываем для записи, удаляя содержимое
	if (!file.is_open()) {
		std::cout << "Файл не может быть открыт" << std::endl;
	}

	else {
		for (int i = 0; i < groups.size(); i++) {
			std::vector <Student*> students = groups[i]->getStudents();
			for (int m = 0; m < students.size(); m++) {

				file << students[m]->getId() << " " << students[m]->getF() << " " << students[m]->getIm() << " " << students[m]->getO() << " " << groups[i]->getTitle()<<" ";
				std::vector <int> marks = students[m]->getMarks();
				for (int x = 0; x < marks.size(); x++) {
					file << marks[x]<< " ";
				}
				file << "\n";
			}
			students.clear();
		}
		std::cout << "\n\n....Изменения в "<<file_ <<" успешно сохранены ";


	}
	file.close();



}

void Deanery::save_group(const std::string& file_)
{
	std::ofstream file(file_, std::ios::out | std::ios::trunc);//открываем для записи, удаляя содержимое
	if (!file.is_open()) {
		std::cout << "Файл не может быть открыт" << std::endl;
	}

	else {
		for (int i = 0; i < groups.size()-1; i++) {
			file << groups[i]->getTitle() << " " << groups[i]->getSpec() << std::endl;

		}
		std::cout << "\n\n....Изменения в " << file_ << " успешно сохранены ";
	}
	file.close();
	

}


