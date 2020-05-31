#include<iostream>
using namespace std;
#include"susi.h"
int main(){
Susi susi;
Discipline a1("DIS","zaduljitelna",1);
Discipline b1("DSTR","zaduljitelna",1);
Discipline c1("UP","zaduljitelna",1);
Discipline d1("Algebra","zaduljitelna",1);
Discipline e1("SDP","zaduljitelna",2);
Discipline f1("SM","izbiraema",1);
Discipline h1("TM","zaduljitelna",3);
Discipline i1("AI","zaduljitelna",4);
Specialnost a2("KN");
a2.add_discipline(a1);
a2.add_discipline(b1);
a2.add_discipline(c1);
a2.add_discipline(e1);
a2.add_discipline(f1);
a2.add_discipline(h1);
a2.add_discipline(i1);
susi.add_specialnost(a2);
Specialnost b2("SI");
b2.add_discipline(a1);
b2.add_discipline(b1);
b2.add_discipline(c1);
susi.add_specialnost(b2);
Specialnost c2("IS");
c2.add_discipline(d1);
susi.add_specialnost(c2);
susi.enroll(1,"KN",4,"pesho");
susi.addgrade(1,"DIS",3.49);
susi.report(1);
susi.interrupt(1);

//
susi.enroll(2,"SI",3,"gosho");

susi.print(2);
susi.addgrade(1,"DSTR",4.51);
susi.resume(1);
susi.addgrade(1,"DSTR",4.48);
susi.report(1);
susi.enroll(3,"KN",3,"Ivan");
susi.addgrade(3,"DSTR",6.00);
susi.addgrade(3,"DIS",6.00);
susi.addgrade(3,"UP",6.00);
susi.enrollin(3,"SM");
susi.printall("KN",1);
susi.advance(3);
susi.advance(3);
susi.addgrade(3,"SM",6.00);
susi.addgrade(3,"SDP",5.5);
susi.addgrade(3,"TM",6.00);
susi.graduate(3);
susi.print(3);
susi.protocol("DSTR");
//susi.writedata("C:\\Users\\krale\\Desktop\\susidata\\susifile.txt");

susi.change(1,"SI",0);
susi.print(1);

exit();
if(flag) return 0;


}
