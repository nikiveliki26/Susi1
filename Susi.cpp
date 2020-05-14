#include<iostream>
using namespace std;
#include"susi.h"
int main(){
Susi susi;
Discipline a1("DIS","zaduljitelna",1);
Discipline b1("DSTR","zaduljitelna",1);
Discipline c1("UP","zaduljitelna",1);
Specialnost a2("KN");
a2.add_discipline(a1);
a2.add_discipline(b1);
a2.add_discipline(c1);
a2.printdisciplines();
susi.add_specialnost(a2);
susi.getnumber();
susi.enroll(1,"KN",4,"pesho");
susi.addgrade(1,"DIS",3.49);
susi.report(1);
susi.getnumber();
//
//susi.enroll(2,"KN",3,"gosho");
//susi.print(1);
a2.printdisciplines();

return 0;
}
