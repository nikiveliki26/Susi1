#ifndef SUSI_H_INCLUDED
#define SUSI_H_INCLUDED

#include"discipline.h"
#include"specialnost.h"
#include"student.h"

#include<iostream>
using namespace std;
#include<cstring>

class Susi{
 private:
  Student* students;
  Specialnost* specialnosti;
  int numberST;
  int numberSP;

  Susi& operator=(const Susi&)=delete;
  Susi (const Susi&)=delete;

  void adjustgrade(Student&);

 public:
    Susi();
    ~Susi();
    void getnumber();
    void add_specialnost( Specialnost&);

    void enroll(const int , const char* ,const int ,const char *);
    void interrupt(const int);
    void resume(const int);
    void advance(const int);
    void graduate(const int);
    void addgrade(const int,const char*,const double);
    void enrollin(const int ,const char*);
    void print(const int)const;
    void printall(const char* ,const int)const;
    void protocol(const char*)const;
    void report(const int)const;
};

Susi:: Susi(){
  students=nullptr;
  specialnosti=nullptr;
  numberST=0;
  numberSP=0;
}

Susi:: ~Susi(){
  delete[] students;
  delete[] specialnosti;
}

void Susi:: getnumber(){
  cout<<numberST<<endl;
  cout<<numberSP<<endl;
}

void Susi:: add_specialnost(Specialnost& a){
     Specialnost* newspecialnosti= new Specialnost[++numberSP];
     for(int i=0;i<numberSP-1;i++) newspecialnosti[i]=specialnosti[i];
     newspecialnosti[numberSP-1]=a;
     delete[] specialnosti;
     specialnosti=newspecialnosti;

}

void Susi:: adjustgrade(Student& Tosho){
     int br=Tosho.numberCD+Tosho.numberPD;
     double sbor=0.0;
     for(int i=0;i<Tosho.numberCD;i++) sbor+=Tosho.currentcourse[i].grade;
     for(int i=0;i<Tosho.numberPD;i++) sbor+=Tosho.previouscourses[i].grade;
     Tosho.AvgGrade=sbor/br;
}

void Susi:: enroll(const int fn_,const char* program,const int group_,const char* name_){
    Student* newstudents=new Student[++numberST];
    for(int i=0;i<numberST-1;i++) newstudents[i]=students[i];
    newstudents[numberST-1].name=new char[strlen(name_)+1];
    strcpy(newstudents[numberST-1].name,name_);
    newstudents[numberST-1].fn=fn_;
    newstudents[numberST-1].course=1;
    for(int i=0;i<numberSP;i++){
        if(strcmp(program,specialnosti[i].name2)==0) newstudents[numberST-1].spec=specialnosti[i];
    }
    newstudents[numberST-1].group=group_;
    strcpy(newstudents[numberST-1].status,"zapisan");
    newstudents[numberST-1].AvgGrade=2.0;
    for(int i=0;i<newstudents[numberST-1].spec.numberD;i++){
        if(newstudents[numberST-1].spec.disciplines[i].course1==1 && strcmp(newstudents[numberST-1].spec.disciplines[i].type,"zaduljitelna")==0){
            newstudents[numberST-1].numberCD++;
        }
    }

    newstudents[numberST-1].currentcourse=new Discipline[newstudents[numberST-1].numberCD];
    int r=0;
    for(int i=0;i<newstudents[numberST-1].spec.numberD;i++){
        if(newstudents[numberST-1].spec.disciplines[i].course1==1 && strcmp(newstudents[numberST-1].spec.disciplines[i].type,"zaduljitelna")==0){
            newstudents[numberST-1].currentcourse[r]=newstudents[numberST-1].spec.disciplines[i];
            r++;
        }
    }

    newstudents[numberST-1].previouscourses=nullptr;
    newstudents[numberST-1].numberPD=0;

    delete[] students;
    students=newstudents;
}

 void Susi:: interrupt(const int fn_){
     for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_) strcpy(students[i].status,"prekusnal");
     }

 }

void Susi:: resume(const int fn_){
    for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_) strcpy(students[i].status,"zapisan");
     }
}

void Susi:: advance(const int fn_){
     for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_){
            Discipline* newpreviouscourses=new Discipline[students[i].numberPD+students[i].numberCD];
            for(int j=0;j<students[i].numberPD;j++) newpreviouscourses[j]=students[i].previouscourses[j];
            for(int j=students[i].numberPD;j<students[i].numberPD+students[i].numberCD;j++) newpreviouscourses[j]=students[i].currentcourse[j];
            delete[] students[i].previouscourses;
            students[i].previouscourses=newpreviouscourses;
            students[i].numberPD+=students[i].numberCD;
            students[i].numberCD=0;
            delete[] students[i].currentcourse;
            students[i].course++;
            for(int j=0;j<students[i].spec.numberD;j++){
                    if(students[i].spec.disciplines[j].course1==students[i].course && strcmp(students[i].spec.disciplines[j].type,"zaduljitelna")==0){
                        students[i].numberCD++;
                    }

            }
            students[i].currentcourse=new Discipline[students[i].numberCD];
             int r=0;
             for(int j=0;j<students[i].spec.numberD;j++){
                    if(students[i].spec.disciplines[j].course1==students[i].course && strcmp(students[i].spec.disciplines[j].type,"zaduljitelna")==0){
                        students[i].currentcourse[r]=students[i].spec.disciplines[j];
                        r++;
                    }

            }

          adjustgrade(students[i]);
            }
     }
}

void Susi:: graduate(const int fn_){
   for(int i=0;i<numberST;i++){
    if(students[i].fn==fn_){
        bool flag=1;
        for(int j=0;j<students[i].numberCD;j++){
            if(students[i].currentcourse[j].grade<3.00) flag=false;
        }

        for(int j=0;j<students[i].numberPD;j++){
            if(students[i].previouscourses[j].grade<3.00) flag=false;
        }
        if(flag && students[i].course==4 && strcmp(students[i].status,"zapisan")==0) strcpy(students[i].status,"zavurshil");
        else cout<<"Ne moje da zavurshi";
    }


   }


}

void Susi:: addgrade(const int fn_,const char* subject,const double grade_){
   for(int i=0;i<numberST;i++){
       if(students[i].fn==fn_){
        for(int j=0;j<students[i].numberCD;j++){
            if(strcmp(students[i].currentcourse[j].name1,subject)==0) students[i].currentcourse[j].grade=grade_;
        }

        for(int j=0;j<students[i].numberPD;j++){
            if(strcmp(students[i].previouscourses[j].name1,subject)==0) students[i].previouscourses[j].grade=grade_;
        }
        adjustgrade(students[i]);
       }
   }
}


void Susi:: enrollin(const int fn_,const char* subject){
    for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_){
            for(int j=0;j<students[i].spec.numberD;j++){
                if((students[i].spec.disciplines[j].name1,subject)==0 && students[i].course==students[i].spec.disciplines[j].course1){
                    Discipline* newcurrentcourse=new Discipline[++students[i].numberCD];
                    for(int k=0;k<students[i].numberCD-1;k++) newcurrentcourse[k]=students[i].currentcourse[k];
                    newcurrentcourse[students[i].numberCD-1]=students[i].spec.disciplines[j];
                    delete[] students[i].currentcourse;
                    students[i].currentcourse=newcurrentcourse;
                }
            }
        }

    }

}

void Susi:: print(const int fn_)const{
       for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_){
         cout<<"name: "<<students[i].name<<endl<<"specialnost: "<<students[i].spec.name2<<endl<<"course: "<<students[i].course<<endl;
         cout<<"group: "<<students[i].group<<endl<<"status: "<<students[i].status<<endl<<"Average Grade: "<<students[i].AvgGrade<<endl;
         for(int j=0;j<students[i].numberCD;j++) cout<<students[i].currentcourse[j].name1<<" "<<students[i].currentcourse[j].grade<<endl;
         for(int j=0;j<students[i].numberPD;j++) cout<<students[i].previouscourses[j].name1<<" "<<students[i].previouscourses[j].grade<<endl;
        }

    }

}

void Susi:: printall(const char* program,const int year)const{
      for(int i=0;i<numberST;i++){
        if(strcmp(students[i].spec.name2,program)==0 && year==students[i].course){
           print(students[i].fn);
        }

    }

}


void Susi:: protocol(const char* course_)const{
    Student* newstudents=new Student[numberST];
    Student temp;
    for(int i=0;i<numberST;i++) newstudents[i]=students[i];
    for(int i=0;i<numberST;i++){
        for(int j=i;j<numberST;j++){
            if(newstudents[i].fn>newstudents[j].fn){
              temp=newstudents[i];
              newstudents[i]=newstudents[j];
              newstudents[j]=temp;
            }
        }
    }

    for(int i=0;i<numberSP;i++){
        bool flag=false;
        for(int j=0;j<specialnosti[i].numberD;j++) if(strcmp(course_,specialnosti[i].disciplines[j].name1)==0) flag=true;
        if(flag) cout<<specialnosti[i].name2<<":"<<endl<<endl;
        int kurs=1;
        if(flag) while(kurs<=4){ cout<<"course: "<<kurs<<endl;
                for(int j=0;j<numberST;j++) if(strcmp(newstudents[j].spec.name2,specialnosti[i].name2)==0 && newstudents[j].course==kurs){
            for(int k=0;k<newstudents[j].numberCD;k++) if(strcmp(newstudents[j].currentcourse[k].name1,course_)==0){
                cout<<newstudents[j].fn<<" "<<newstudents[j].name<<" "<<newstudents[j].currentcourse[k].grade<<endl;
            }

            for(int k=0;k<newstudents[j].numberPD;k++) if(strcmp(newstudents[j].previouscourses[k].name1,course_)==0){
                cout<<newstudents[j].fn<<" "<<newstudents[j].name<<" "<<newstudents[j].currentcourse[k].grade<<endl;
            }

          }
          kurs++;
        }

    }

}

void Susi:: report(const int fn_)const{
       for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_){
         cout<<"name: "<<students[i].name<<endl<<"specialnost: "<<students[i].spec.name2<<endl<<"course: "<<students[i].course<<endl;
         cout<<"group: "<<students[i].group<<endl<<"status: "<<students[i].status<<endl<<"Average Grade: "<<students[i].AvgGrade<<endl;
         cout<<"Vzeti izpiti: "<<endl;
         for(int j=0;j<students[i].numberCD;j++) if(students[i].currentcourse[j].grade>=3.00) cout<<students[i].currentcourse[j].name1<<" "<<students[i].currentcourse[j].grade<<endl;
         for(int j=0;j<students[i].numberPD;j++) if(students[i].previouscourses[j].grade>=3.00) cout<<students[i].previouscourses[j].name1<<" "<<students[i].previouscourses[j].grade<<endl;
         cout<<"Nevzeti izpiti: "<<endl;
         for(int j=0;j<students[i].numberCD;j++) if(students[i].currentcourse[j].grade<3.00) cout<<students[i].currentcourse[j].name1<<" "<<students[i].currentcourse[j].grade<<endl;
         for(int j=0;j<students[i].numberPD;j++) if(students[i].previouscourses[j].grade<3.00) cout<<students[i].previouscourses[j].name1<<" "<<students[i].previouscourses[j].grade<<endl;

        }

    }

}


/*for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_){

        }

    }*/
#endif // SUSI_H_INCLUDED
