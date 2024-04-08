#ifndef INCLUDE_STUDENT_H
#define INCLUDE_STUDENT_H

#include <iostream>
#include <vector>




class Group;
class Student
{
private:
    unsigned int id;
    char* f;
    char* im;
    char* o;
    Group* group;
    std::vector <int> marks;
public:
    void print();
        
    Student(unsigned int id_, const char* f_, const char* im_, const char* o_);
    ~Student();
    
    void add_mark(int mark_);
    float aver_mark();
    void add_to_group(Group *p);
    char* getF();
    char* getIm();
    char* getO();
    std::vector <int> getMarks();


   
    unsigned int getId() const;

};


#endif // INCLUDE_STUDENT_H