#include <iostream>
#include "Student.h"

#include "Group.h"
#include "Deanery.h"



int main(){
	setlocale(LC_ALL, "rus");
	
	Deanery deanery2023;

	//��������� ������ �� �����
	deanery2023.CreateGroups("groups.txt");

	//����������, ��� ������ ���������� ������ �� ������ 
	deanery2023.CreateGroups("groups.txt");

	//���������� ��������� ������ ��� ���������
	deanery2023.printGroupWithoutStudents();

	//������� ���������  
	deanery2023.hireStudents("students.txt");

	//������ ���������� ����� ������ �� ������
	deanery2023.hireStudents("students.txt");

	//����� ������� ���������� ��� ������, � ������� ���� ��������� ��������
	deanery2023.printGroupWithoutStudents();

	//������� ������ �� ���������� � ����������� ��� ���	
	//�������� ��������, ��� ������������ ������ (<-10 || >10) �� ����������
	deanery2023.printGroupWithStat();
		 
	deanery2023.printUnaccounted(); //������ ��������� ���������

	deanery2023.grades(); //������� ���������� �� �������
	
	deanery2023.expel(); //��������

	deanery2023.printGroup(); //�������, ��� ������� ����� ����������, ���������� ��������� ������� 

	deanery2023.addMark(); //������� ������ 

	deanery2023.printGroupWithStat(); //��������� �� ����������� ������

	deanery2023.grades(); //���������� ����� ��������

	deanery2023.transfer("������������������", "2023��"); //�������� �������� 

	deanery2023.transfer("������������������", "2023��"); //�������� �������� �� ����� ������ � ���� �� - ������ �� ����� 

	deanery2023.transfer("�������", "2023���");//��������� � ��������������� ��������

	deanery2023.transfer("�������������", "2023����");//��������� � �������������� ������
	
	deanery2023.printGroup();//��������� �� ���������

	//deanery2023.save_group("groups.txt");//�������� ���������
	
	//deanery2023.save_stud("students.txt");//�������� ���������

	std::cout << std::endl << std::endl;
	return 0;
}