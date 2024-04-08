#ifndef INCLUDE_GROUP_H
#define INCLUDE_GROUP_H


#include <iostream>
#include <vector>



class Student;

class Group
{
   

private:   
    char* title;
    
    char* spec;
    std::vector <Student*> students;
    Student* head;

public:
    
    Group(const char* title_, const char* spec_);
    ~Group();
    void print_student() const;
    void print_student_with_marks() const;
    void print() const;
    void add_stud(Student* stud);
    Student * find(const char* f_);//»щем студента по фамилии
   
    Student * find(unsigned int id_);
    void election();//выбор старосты
    void print_head();//напечатать старосту
    float aver();//средн€€ оценка
    char* getTitle();//получение названи€
    char* getSpec();//полученe специальности
    void deleteStudent(Student* st);
    std::vector <Student*> getStudents();
       
};


#endif // INCLUDE_GROUP_H
