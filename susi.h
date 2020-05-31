#ifndef SUSI_H_INCLUDED
#define SUSI_H_INCLUDED

#include"discipline.h"
#include"specialnost.h"
#include"student.h"

#include<iostream>
using namespace std;
#include<cstring>
#include<fstream>
#include<string>
char filename[1000];
bool flag=false;
bool flag1=false;

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
    void change(const int,const char*,const int);

    void writedata(const char*);

    void save();
    void saveas();
    void close();
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
    numberST++;
    Student* newstudents=new Student[numberST];
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
            if(strcmp(students[i].status,"zapisan")!=0){
                cout<<"Studentut ne e zapisan"<<endl;
                return;
            }
            Discipline* newpreviouscourses=new Discipline[students[i].numberPD+students[i].numberCD];
            for(int j=0;j<students[i].numberPD;j++) newpreviouscourses[j]=students[i].previouscourses[j];
            for(int j=students[i].numberPD;j<students[i].numberPD+students[i].numberCD;j++) newpreviouscourses[j]=students[i].currentcourse[j-students[i].numberPD];
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
        if(strcmp(students[i].status,"zapisan")!=0){
                cout<<"Studentut ne e zapisan"<<endl;
                return;
            }
        bool flag=1;
        for(int j=0;j<students[i].numberCD;j++){
            if(students[i].currentcourse[j].grade<3.00) flag=false;
        }

        for(int j=0;j<students[i].numberPD;j++){
            if(students[i].previouscourses[j].grade<3.00) flag=false;
        }
        if(flag && students[i].course==4 && strcmp(students[i].status,"zapisan")==0) strcpy(students[i].status,"zavurshil");
        else cout<<"Ne moje da zavurshi"<<endl<<endl;
    }


   }


}

void Susi:: addgrade(const int fn_,const char* subject,const double grade_){
   if(grade_<2.00 || grade_>6.00){
    cout<<"nevalidna ocenka"<<endl;
    return;
   }
   for(int i=0;i<numberST;i++){
       if(students[i].fn==fn_){
            if(strcmp(students[i].status,"zapisan")!=0){
                cout<<"Studentut ne e zapisan"<<endl;
                return;
            }
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
               if(strcmp(students[i].status,"zapisan")!=0){
                cout<<"Studentut ne e zapisan"<<endl;
                return;
            }
            for(int j=0;j<students[i].spec.numberD;j++){
                if(strcmp(students[i].spec.disciplines[j].name1,subject)==0 && students[i].course==students[i].spec.disciplines[j].course1){
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
         cout<<"Print za "<<students[i].name<<endl;
         cout<<"name: "<<students[i].name<<endl<<"specialnost: "<<students[i].spec.name2<<endl<<"course: "<<students[i].course<<endl;
         cout<<"group: "<<students[i].group<<endl<<"status: "<<students[i].status<<endl<<"Average Grade: "<<students[i].AvgGrade<<endl;
         for(int j=0;j<students[i].numberCD;j++) cout<<students[i].currentcourse[j].name1<<" "<<students[i].currentcourse[j].grade<<endl;
         for(int j=0;j<students[i].numberPD;j++) cout<<students[i].previouscourses[j].name1<<" "<<students[i].previouscourses[j].grade<<endl;
         cout<<endl<<endl;
        }

    }

}

void Susi:: printall(const char* program,const int year)const{
      cout<<"Printall za "<<program<<" "<<year<<"kurs"<<endl;
      for(int i=0;i<numberST;i++){
        if(strcmp(students[i].spec.name2,program)==0 && year==students[i].course){
           print(students[i].fn);
        }

    }

}


void Susi:: protocol(const char* course_)const{
    cout<<"Protocol za "<<course_<<endl;
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
        if(flag) while(kurs<=4){ cout<<"course"<<kurs<<":"<<endl;
                for(int j=0;j<numberST;j++) if(strcmp(newstudents[j].spec.name2,specialnosti[i].name2)==0 && newstudents[j].course==kurs){
            for(int k=0;k<newstudents[j].numberCD;k++) if(strcmp(newstudents[j].currentcourse[k].name1,course_)==0){
                cout<<newstudents[j].fn<<" "<<newstudents[j].name<<" "<<newstudents[j].currentcourse[k].grade<<endl;
            }

            for(int k=0;k<newstudents[j].numberPD;k++) if(strcmp(newstudents[j].previouscourses[k].name1,course_)==0){
                cout<<newstudents[j].fn<<" "<<newstudents[j].name<<" "<<newstudents[j].previouscourses[k].grade<<endl;
            }

          }
          kurs++;
          cout<<endl;
        }

    }

}

void Susi:: report(const int fn_)const{
       for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_){
         cout<<"Report za "<<students[i].name<<endl;
         cout<<"name: "<<students[i].name<<endl<<"specialnost: "<<students[i].spec.name2<<endl<<"course: "<<students[i].course<<endl;
         cout<<"group: "<<students[i].group<<endl<<"status: "<<students[i].status<<endl<<"Average Grade: "<<students[i].AvgGrade<<endl;
         cout<<"Vzeti izpiti: "<<endl;
         for(int j=0;j<students[i].numberCD;j++) if(students[i].currentcourse[j].grade>=3.00) cout<<students[i].currentcourse[j].name1<<" "<<students[i].currentcourse[j].grade<<endl;
         for(int j=0;j<students[i].numberPD;j++) if(students[i].previouscourses[j].grade>=3.00) cout<<students[i].previouscourses[j].name1<<" "<<students[i].previouscourses[j].grade<<endl;
         cout<<"Nevzeti izpiti: "<<endl;
         for(int j=0;j<students[i].numberCD;j++) if(students[i].currentcourse[j].grade<3.00) cout<<students[i].currentcourse[j].name1<<" "<<students[i].currentcourse[j].grade<<endl;
         for(int j=0;j<students[i].numberPD;j++) if(students[i].previouscourses[j].grade<3.00) cout<<students[i].previouscourses[j].name1<<" "<<students[i].previouscourses[j].grade<<endl;
         cout<<endl<<endl;
        }

    }

}

void Susi::change(const int fn_,const char* option,const int value){
    for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_){
          if(strcmp(option,"group")==0) students[i].group=value;
          else if(strcmp(option,"year")==0){
            int br=0;
            for(int j=0;j<students[i].numberPD;j++) if(students[i].previouscourses[j].grade<3.00) br++;
            if(br<=2 && value-1==students[i].course) advance(fn_);
            else cout<<"Studentut ne moje da otide v po-goren kurs"<<endl<<endl;
            }
          else{
           for(int j=0;j<numberSP;j++) if(strcmp(option,specialnosti[j].name2)==0){
            bool flag=true;
            for(int k=0;k<specialnosti[j].numberD;k++) if(strcmp(specialnosti[j].disciplines[k].type,"zaduljitelna")==0){
                for(int r=0;r<students[i].numberPD;r++) if(strcmp(students[i].previouscourses[r].name1,specialnosti[j].disciplines[k].name1)==0 && students[i].previouscourses[r].grade<3.0) flag=false;
            }
            if(!flag) cout<<"Ne moje da otide po-goren kurs"<<endl<<endl;
            if(flag){
                students[i].spec=specialnosti[j];
                Discipline* newcurrentcourse=new Discipline[students[i].numberCD];
                for(int r=0;r<students[i].numberCD;r++) newcurrentcourse[r]=students[i].currentcourse[r];
                int brIZ=0;
                for(int p=0;p<students[i].numberCD;p++) if(strcmp(students[i].currentcourse[p].type,"izbiraema")==0) brIZ++;
                delete[] students[i].currentcourse;
                int brCD=students[i].numberCD;
                students[i].numberCD=0;
                for(int p=0;p<students[i].spec.numberD;p++){
        if(students[i].spec.disciplines[p].course1==students[i].course && strcmp(students[i].spec.disciplines[p].type,"zaduljitelna")==0){
            students[i].numberCD++;
        }
    }
    students[i].numberCD+=brIZ;
    students[i].currentcourse=new Discipline[students[i].numberCD];
    int r=0;
    for(int p=0;p<students[i].spec.numberD;p++){
        if(students[i].spec.disciplines[p].course1==students[i].course && strcmp(students[i].spec.disciplines[p].type,"zaduljitelna")==0){
            students[i].currentcourse[r]=students[i].spec.disciplines[p];
            r++;
        }
    }
    for(int p=0;p<brIZ;p++) if(strcmp(newcurrentcourse[p].type,"izbiraema")==0){
        students[i].currentcourse[r]=newcurrentcourse[p];
        r++;
        }
    for(int p=0;p<r;p++)
            for(int k=0;k<brCD;k++) if(strcmp(students[i].currentcourse[p].name1,newcurrentcourse[k].name1)) students[i].currentcourse[p].grade=newcurrentcourse[k].grade;

            }
           }
          }

        }

    }


}

string extractword(string line, int n){
   line+=" ";
   string result;
   int wordnumber=0;

  for(int i=0;i<line.size();i++){

    if(line[i]==' '){
        wordnumber++;
        if(wordnumber==n) return result;
        result="";
    }
    else result+=line[i];
}
return "";
}


void Susi:: writedata(const char* filename){
 ofstream outfile;
 outfile.open(filename);
 outfile<<numberST<<endl;
 for(int i=0;i<numberST;i++){
    outfile<<students[i].name<<" "<<students[i].fn<<" "<<students[i].course<<" "<<students[i].spec.name2<<" "<<students[i].group<<" "<<students[i].status<<" "<<students[i].AvgGrade<<endl;
    outfile<<students[i].numberCD<<endl;
    for(int j=0;j<students[i].numberCD;j++) outfile<<students[i].currentcourse[j].name1<<" "<<students[i].currentcourse[j].type<<" "<<students[i].currentcourse[j].course1<<" "<<students[i].currentcourse[j].grade<<endl;

    outfile<<students[i].numberPD<<endl;
    for(int j=0;j<students[i].numberPD;j++) outfile<<students[i].previouscourses[j].name1<<" "<<students[i].previouscourses[j].type<<" "<<students[i].previouscourses[j].course1<<" "<<students[i].previouscourses[j].grade<<endl;



 }
outfile.close();

}

void exit(){
 flag=true;
}

void help(){
cout<<"The following commands are supported:"<<endl<<endl;
            cout<<"open <file>:	opens <file>"<<endl<<endl;;
            cout<<"close: closes currently opened file"<<endl<<endl;;
            cout<<"save: saves the currently opened file"<<endl<<endl;;
            cout<<"saveas <file>: saves the currently open file in <file>"<<endl<<endl;;
            cout<<"help: prints this information"<<endl<<endl;;
            cout<<"exit : exits the program"<<endl<<endl;;
            cout<<"enroll <fn> <program> <group> <name>: ";
            cout<<"registers a student named <name> in <group> group, <program> program"<<endl<<endl;;
            cout<<"advance <fn>: the student with <fn> faculty number goest to the next course"<<endl<<endl;;
            cout<<"change <fn> <option> <value>: "<<endl<<endl;;
            cout<<"Moves the student with <fn> faculty number to a different year, course or group. ";
            cout<<"graduate <fn>: graduates the student with <fn> faculty number if they have passed all their exams. "<<endl<<endl;;
            cout<<"interrupt <fn>: Changes the student's status to 'interrupted'. "<<endl<<endl;;
            cout<<"resume <fn>: restores the student's rights. "<<endl<<endl;
            cout<<"print <fn>: prints a reference about the student with <fn> faculty number."<<endl;
            cout<<"printall <program> <year>: prints references about all students in year <year> and program <program>."<<endl<<endl;
            cout<<"enrollin <fn> <course>: Adds a selective discipline named <course> to the student with <fn> faculty number."<<endl<<endl;;
            cout<<"addgrade <fn> <course> <grade>: Adds a <grade> grade to the student  in <course> discipline."<<endl<<endl;;
            cout<<"protocol <course>: prints protocols about all students who study <course> discipline."<<endl<<endl;;
            cout<<"report <fn>: prints  lists of taken and failed exams of a student."<<endl<<endl;;
}

void Susi::save(){
  writedata(filename);

}

void Susi::saveas(){
 char newfilename[1000];
 cin>>newfilename;
 writedata(newfilename);

}

void Susi:: close(){
   delete[] students;
   delete[] specialnosti;
   flag1=false;

}


/*void Susi:: loaddata(char* filename){
 fstream file;
 string line;
 string word;
 file.open(filename);
 while(getline(file,line)){
    word=extractword(line,1);
    numberST=stoi(word);
    students=new Student[numberST];
    for(int i=0;i<numberST;i++){

    }


 }
}

*/

/*for(int i=0;i<numberST;i++){
        if(students[i].fn==fn_){

        }

    }*/
#endif // SUSI_H_INCLUDED
