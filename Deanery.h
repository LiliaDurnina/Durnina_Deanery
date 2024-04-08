#ifndef INCLUDE_DEANERY_H
#define INCLUDE_DEANERY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>




class Group;
class Student;
class Deanery
{
private:    
    std::vector <Group*> groups;
public:
    Deanery() {};
    ~Deanery();
    void CreateGroups(const std::string& file_);//������� ������
    void hireStudents(const std::string& file_);//�������� ���������
    Group* findGroup(const char* title_);
    void grades();
    void printUnaccounted(); // ��� ����� �������� ��� �����
    void expel();//����������
   
    void printGroupWithoutStudents();
    void printGroupWithStat();
    void printGroup();
    void addMark();
    void transfer(const char* f_, const char* title_);//������� �������� � ������������ ������

    void save_stud(const std::string& file_);//��������� ������ � ���� 
    void save_group(const std::string& file_);//��������� ������ � ���� 

};


#endif // INCLUDE_DEANERY_H
