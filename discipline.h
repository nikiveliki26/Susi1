#ifndef DISCIPLINE_H_INCLUDED
#define DISCIPLINE_H_INCLUDED

#include<cstring>

class Discipline{
  private:
  char* name1;
  char type[20];
  int course1;
  double grade;

  void copy_discipline(const Discipline&);
  void delete_discipline();
  public:
    Discipline();
    Discipline(const char* ,const char* ,const int);
    Discipline(const Discipline&);
    Discipline& operator=(const Discipline&);
    ~Discipline();

    friend class Specialnost;
    friend class Student;
    friend class Susi;

};

void Discipline:: copy_discipline(const Discipline& other){
   name1=new char[strlen(other.name1)+1];
   strcpy(name1,other.name1);
   strcpy(type,other.type);
   course1=other.course1;
   grade=other.grade;

}
void Discipline:: delete_discipline(){
   delete[] name1;
}

Discipline::Discipline(){
    name1=nullptr;
    strcpy(type,"");
    course1=1;
    grade=2.00;

}

Discipline::Discipline(const char* name1_,const char* type_,const int course1_){
  name1=new char[strlen(name1_)+1];
  strcpy(name1,name1_);
  strcpy(type,type_);
  course1=course1_;
  grade=2.00;

}
Discipline:: Discipline(const Discipline& other){
    delete_discipline();
    copy_discipline(other);
}
Discipline& Discipline:: operator=(const Discipline& other){
      if(this != &other){
         delete_discipline();
        copy_discipline(other);
      }
     return *this;
}
Discipline:: ~Discipline(){
   delete_discipline();
}

#endif // DISCIPLINE_H_INCLUDED
