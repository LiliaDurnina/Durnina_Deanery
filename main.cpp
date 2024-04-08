#include <iostream>
#include "Student.h"

#include "Group.h"
#include "Deanery.h"



int main(){
	setlocale(LC_ALL, "rus");
	
	Deanery deanery2023;

	//считываем группы из файла
	deanery2023.CreateGroups("groups.txt");

	//Показываем, что второе считывание ничего не ломает 
	deanery2023.CreateGroups("groups.txt");

	//напечатали имеющиеся группы без студентов
	deanery2023.printGroupWithoutStudents();

	//Считали студентов  
	deanery2023.hireStudents("students.txt");

	//второе считывание также ничего не ломает
	deanery2023.hireStudents("students.txt");

	//вновь выведем информации про группы, в котоыре были добавлены студенты
	deanery2023.printGroupWithoutStudents();

	//Выведем группы со студентами и информацией про них	
	//обратите внимание, что некорректные оценки (<-10 || >10) не записались
	deanery2023.printGroupWithStat();
		 
	deanery2023.printUnaccounted(); //печать неучтённых студентов

	deanery2023.grades(); //краткая статистика по группам
	
	deanery2023.expel(); //отчислим

	deanery2023.printGroup(); //смотрим, кто остался после отчисления, отслеживая изменение старост 

	deanery2023.addMark(); //добавим оценки 

	deanery2023.printGroupWithStat(); //посмотрим на добавленные оценки

	deanery2023.grades(); //статистика после удаления

	deanery2023.transfer("Неправильногрупная", "2023ПИ"); //переведём студента 

	deanery2023.transfer("Неправильногрупная", "2023ПИ"); //переведём студента из своей группы в свою же - ошибки не будет 

	deanery2023.transfer("Дурнина", "2023ПМИ");//обратимся к несуществующему студенту

	deanery2023.transfer("Восемнадцатая", "2023МББЭ");//обратимся к несуществующей группе
	
	deanery2023.printGroup();//посмотрим на изменения

	//deanery2023.save_group("groups.txt");//выгрузка изменений
	
	//deanery2023.save_stud("students.txt");//выгрузка изменений

	std::cout << std::endl << std::endl;
	return 0;
}