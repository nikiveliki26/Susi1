#ifndef SPECIALNOST_H_INCLUDED
#define SPECIALNOST_H_INCLUDED

#include"discipline.h"
#include<cstring>
class Specialnost{
  private:
     char* name2;
     Discipline* disciplines;
     int numberD;
  public:
     Specialnost();
     Specialnost(const char* );
     Specialnost(const Specialnost&);
     Specialnost& operator=(const Specialnost&);
     ~Specialnost();

     void printdisciplines();
     void add_discipline(const Discipline&);
     friend class Student;
     friend class Susi;
};

Specialnost:: Specialnost():numberD(0),disciplines(nullptr),name2(nullptr){

}

Specialnost:: Specialnost(const char* name2_){
    name2=new char[strlen(name2_)+1];
    strcpy(name2,name2_);
    numberD=0;
    disciplines= nullptr;
    //for(int i=0;i<numberD;i++) disciplines[i]=disciplines_[i];
}

Specialnost:: Specialnost(const Specialnost& other){

        delete[]name2;
        delete[]disciplines;

     name2=new char[strlen(other.name2)+1];
     strcpy(name2,other.name2);
     numberD=other.numberD;
     disciplines=new Discipline[numberD];
     for(int i=0;i<numberD;i++) disciplines[i]=other.disciplines[i];

}

Specialnost& Specialnost:: operator=(const Specialnost& other){
      if(this!=&other){
        delete[] name2;
        delete[] disciplines;
        name2=new char[strlen(other.name2)+1];
        strcpy(name2,other.name2);
        numberD=other.numberD;
        disciplines= new Discipline[numberD];
        for(int i=0;i<numberD;i++) disciplines[i]=other.disciplines[i];

      }
      return *this;

}

Specialnost:: ~Specialnost(){
    delete[] name2;
    delete[] disciplines;
}

void Specialnost::add_discipline(const Discipline& newdis){
     Discipline* newdisciplines=new Discipline[++numberD];
     for(int i=0;i<numberD-1;i++) newdisciplines[i]=disciplines[i];
     newdisciplines[numberD-1]=newdis;
     delete[] disciplines;
     disciplines=newdisciplines;
}

void Specialnost:: printdisciplines(){
     for(int i=0;i<numberD;i++) cout<<disciplines[i].name1<<endl;

}
#endif // SPECIALNOST_H_INCLUDED
