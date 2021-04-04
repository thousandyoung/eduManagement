#ifndef TEACHER_H
#define TEACHER_H
#include <string>
using namespace std;

class Teacher
{
    char teaname[20];    //姓名
    char id[20];   //工号
    char password[20];    //密码
    char coursename[100];    //任课课程的集合，格式课程名字/班名&课程名字/班名&···
public:
    Teacher();
    Teacher(const char* a,const char* b,const char* c,const char* d);
    Teacher(const Teacher& tea);
    void inteaname(const char* a);
    void inid(const char* a);
    void incoursename(const char* a);
    void changepassword(const char* newpass,bool& done);
    char* reteaname();
    char* reid();
    char* recoursename();
    char* repassword();


    string createRandomName();
    string createOnlyId();
    string createRandomCourse(int n);
    string createxxxx(int n);

};

struct TeaIndex{
    char teaname[20];
    unsigned int exposition;
};

struct TeaIndex1{
    char id[20];
    long exposition;
};

struct CourClass{
    char courname[30];
    char classname[30];
};

#endif // TEACHER_H
