#ifndef STUDENT_H
#define STUDENT_H


class Student
{
    char stuname[20];  //姓名
    char stuid[20];   //学号
    char major[20];   //专业
    char courseandgrade[1000];   //选课及课程信息
    char password[20];   //登录密码
public:
    Student();
    Student(char* a,char* b,char* c,char* d,char* e);

    void instuname(const char* a);
    void instuid(const char* a);
    void inmajor(const char* a);
    void incourseandgrade(const char* a);
    void changepassword(const char* a,bool& done);

    char* restuname();
    char* restuid();
    char* remajor();
    char* recourseandgrade();
    char* repassword();
};

struct StuIdIndexs{
    char stuid[20];
    char PathAndExpo[50];
};

struct StuNameIndexs{
    char stuname[20];
    char PathAndExpo[50];
};

struct pathAndexpo{
    char path[50];
    long exposition;
};


#endif // STUDENT_H
