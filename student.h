#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include"specialnost.h"
#include"discipline.h"
#include<cstring>

class Student{
  private:
      char* name;
      int fn;
      int course;
      Specialnost spec;
      int group;
      char status[20];
      double AvgGrade;
      Discipline* currentcourse;
      Discipline* previouscourses;
      int numberCD;
      int numberPD;

      void copy_student(const Student&);
      void delete_student();
  public:
    Student();
    Student(const char* ,const int  ,const int  ,const Specialnost  ,const int  ,const char*  ,const double  ,const Discipline*  ,const Discipline*  ,const int , const int);
    Student(const Student&);
    Student& operator=(const Student&);
    ~Student();



    friend class Susi;


};


void Student:: copy_student(const Student& other){
   name=new char[strlen(other.name)+1];
   strcpy(name,other.name);
   fn=other.fn;
   course=other.course;
   spec=other.spec;
   group=other.group;
   strcpy(status,other.status);
   AvgGrade=other.AvgGrade;
   numberCD=other.numberCD;
   numberPD=other.numberPD;
   currentcourse=new Discipline[numberCD+1];
   previouscourses=new Discipline[numberPD+1];
   for(int i=0;i<numberCD;i++) currentcourse[i]=other.currentcourse[i];
   for(int i=0;i<numberCD;i++) previouscourses[i]=other.previouscourses[i];

}

void Student:: delete_student(){
    delete[] name;
    delete[] currentcourse;
    delete[] previouscourses;
}

Student::Student(){
     name=nullptr;
     fn=0;
     course=1;
     group=1;
     strcpy(status,"zapisan");
     AvgGrade=2.00;
     currentcourse=nullptr;
     previouscourses=nullptr;
     numberCD=0;
     numberPD=0;
     spec.name2=nullptr;
     spec.disciplines=nullptr;
     spec.numberD=0;

}

Student::Student(const char* name_,const int fn_,const int course_ ,const Specialnost spec_  ,const int group_ ,const char* status_ ,const double AvgGrade_ ,const Discipline* currentcourse_ ,const Discipline* previouscourses_ ,const int numberCD_ , const int numberPD_){
name=new char[strlen(name_)+1];
   strcpy(name,name_);
   fn=fn_;
   course=course_;
   spec=spec_;
   group=group_;
   strcpy(status,status_);
   AvgGrade=AvgGrade_;
   numberCD=numberCD_;
   numberPD=numberPD_;
   currentcourse=new Discipline[numberCD+1];
   previouscourses=new Discipline[numberPD+1];
   for(int i=0;i<numberCD;i++) currentcourse[i]=currentcourse_[i];
   for(int i=0;i<numberCD;i++) previouscourses[i]=previouscourses_[i];



}

Student::Student(const Student& other){

    delete_student();
    copy_student(other);

}


Student& Student:: operator=(const Student& other){
             if(this!=&other){
                delete_student();
                copy_student(other);
             }
             return *this;

    }
Student::~Student(){
       delete_student();
    }


#endif // STUDENT_H_INCLUDED
