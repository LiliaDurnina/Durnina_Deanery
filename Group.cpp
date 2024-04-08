#include "Group.h"
#include "Student.h"

Group::Group(const char* title_, const char* spec_)
{
	title = new char[strlen(title_) + 1];
	for (int i = 0; i < strlen(title_); i++) {
		title[i] = title_[i];
	}
	title[strlen(title_)] = '\0';
	spec = new char[strlen(spec_) + 1];
	for (int i = 0; i < strlen(spec_); i++) {
		spec[i] = spec_[i];
	}
	spec[strlen(spec_)] = '\0';
	head = nullptr;

}

Group::~Group()
{
	delete[]  title;
	delete[]  spec;
	students.clear();

}

void Group::print_student() const
{
	std::cout << "\n          " << title;
	std::cout << "\n   " << spec;
	for (int i = 0; i < students.size(); i++) {
		std::cout << "\n   " <<i+1 <<". " << students[i]->getF() << " " << students[i]->getIm();
	}
	std::cout << "\n   Староста:  ";
	if (head != nullptr) {
		std::cout << head->getF() ;
	}
	else {
		std::cout << "-";
	}



}
void Group::print_student_with_marks() const
{
	std::cout << "\n          " << title;
	std::cout << "\n  " << spec;
	for (int i = 0; i < students.size(); i++) {
		std::cout << "\n   ";
		students[i]->print();
	}
	std::cout << "\n\n  Староста: ";
	if (head != nullptr) {
		std::cout << head->getF() << " "<< head->getIm();
	}
	else {
		std::cout << "-";
	}



}

void Group::print() const
{
	std::cout << "\n          " << title;
	std::cout << "\n   " << spec;
	
	std::cout << "\n   Староста:  ";
	if (head != nullptr) {
		std::cout << head->getF();
	}
	else {
		std::cout << "-";
	}
	std::cout << "\n   Студенты:  " << students.size();
	
}


void Group::add_stud(Student* stud)
{
	students.push_back(stud);
}

Student * Group::find(const char* f_)
{
	Student* st = nullptr;
	
	for (int i = 0; i < students.size(); i++) {
		if (strcmp(students[i]->getF(), f_) == 0) {
			
			st = students[i];
			

		}
	
	}
	return st;
}


Student * Group::find(unsigned int id_)
{

	Student* st=nullptr;
	
	for (int i = 0; i < students.size(); i++) {
		
		if (students[i]->getId() == id_) {
			
		
			st = students[i];
			


		}

	}
	return st;

}

void Group::election()
{
	float max= - 10;
	for (int i = 0; i < students.size(); i++) {

		if (students[i]->aver_mark()>max) {
			max = students[i]->aver_mark();
			head = students[i];


		}

	}
	if (students.size() == 0) {
		head = nullptr;
	}


}

void Group::print_head()
{
	if (head != nullptr) {
		std::cout << head->getF() << " " << head->getIm();
	}
	else {
		std::cout << "-";

	}
}

float Group::aver()
{
	if (students.size() == 0) {
		return 0;
	}
	else {
		float sum = 0;
		for (int i = 0; i < students.size(); i++) {
			sum += students[i]->aver_mark();
		}
		return (float)sum / students.size();


	
	}
}

char* Group::getTitle()
{
	return title;
}

char* Group::getSpec()
{
	return spec;
}

void Group::deleteStudent(Student* st)
{
	for (int i = 0; i < students.size(); i++) {
		if (students[i] == st) {
			auto iter = students.cbegin();
			students.erase(iter+i);
		}
	}
}

std::vector<Student*> Group::getStudents()
{
	return students;
}









