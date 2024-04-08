#include "Student.h"
#include "Group.h"

void Student::print()
{
	std::cout << "\n  Id:" << id << " " << f << " "<<im << " " << o<<" ";
	if (group != nullptr) {

		std::cout << group->getTitle(); 
	}


	std::cout << "\n  Оценки: ";

	for (int i = 0; i < marks.size(); i++) {
		std::cout << marks[i] << " ";

	}

	if (marks.size() == 0) {
		std::cout << "Нет оценок";
	}
	std::cout << "\n  Средняя оцнека: " << this->aver_mark();

}

Student::Student(unsigned int id_, const char* f_, const char* im_, const char* o_)
{
	id = id_;
	f = new char[strlen(f_) + 1];
	for (int i = 0; i < strlen(f_); i++) {
		f[i] = f_[i];
	}
	f[strlen(f_)] = '\0';
	im = new char[strlen(im_) + 1];
	for (int i = 0; i < strlen(im_); i++) {
		im[i] = im_[i];
	}
	im[strlen(im_)] = '\0';
	o = new char[strlen(o_) + 1];
	for (int i = 0; i < strlen(o_); i++) {
		o[i] = o_[i];
	}
	o[strlen(o_)] = '\0';
	group = nullptr;

}

Student::~Student()
{
	delete[] f;
	delete[] im;
	delete[] o;
	marks.clear();

	
}

void Student::add_mark(int mark_)
{
	//Возможность добавить только существующую оценку вплоть до -10 (Спасибо И.С.Бычкову)
	if (mark_>= -10 and mark_<=10) {
		marks.push_back(mark_);
		
	}

	
	
}

float Student::aver_mark()
{   //Если оценок нет, считаем балл равным 0
	if (marks.size() == 0) {
		return 0;
	}
	else {
		int sum = 0;
		for (int i = 0; i < marks.size(); i++) {
			sum += marks[i];
			
		}
		
		
		return (float)sum / marks.size();

	}
}

void Student::add_to_group(Group *p)
{
	group = p;
}

char* Student::getF()
{
	return f;
}

char* Student::getIm()
{
	return im;
}

char* Student::getO()
{
	return o;
}

std::vector<int> Student::getMarks()
{
	return marks;
}

unsigned int Student::getId() const
{
	return id;
}





