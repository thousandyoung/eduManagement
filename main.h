#ifndef MAINH_H
#define MAINH_H


//
//  edu.hpp
//  4
//
//  Created by Takashii on 2021/3/4.
//


#include <stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<map>

using namespace std;

//在cpp文件已经定义索引对象
extern multimap<string, string>Stu_number;
extern multimap<string, string>Stu_name;
extern multimap<string, string>Tea;
extern multimap<string, string>Ad;


void Connect(char *x,char *y,char *z);

void Copy(const char *b, char *a);

int Get_size(char *a);

void Stitch(char* a,char *b);

char* string_char(string a,char * b);

string to_string(int x);

//---------------------------------------各类定义-----------------------------------------
class Course       //存储在课程文件中的课程类
{
public:

    char stu_name[20];      //学生姓名
    char stu_number[20];    //学生学号
    char usual_grade[20];         //平时成绩
    char final_grade[20];        //期末成绩
    char overall_grade[20];       //总评成绩
    Course(){}
    Course(char* stu_name,char* stu_number,char* usual_grade,char* final_grade,char* overall_grade){
        Copy(stu_name,this->stu_name),Copy(stu_number,this->stu_number),Copy(usual_grade,this->usual_grade),Copy(final_grade,this->final_grade),Copy(overall_grade,this->overall_grade);
    }
};

class User {
public:
    char number[20];      //学号 只能用学号或者工号登录
    char password[20];
};

class Student : public User
{
public:
    char name[20];
    char grade[20];    //年级
    char college[20];  //学院
    char major[20];    //专业
    char Class[20];    //班级
    char course[100];   //学生全部课程信息。以 课程名字/总评成绩/课程名字/总评成绩...
    Student() { number[0]=name[0]=password[0]=grade[0]=college[0]=major[0]=Class[0]=course[0]='\0'; }
    Student(const Student& x)
    {
        Copy(x.name,name),Copy(x.number,number),Copy(x.course,course),Copy(x.password,password);
        Copy(x.college,college),Copy(x.Class,Class),Copy(x.major,major),Copy(x.grade,grade);
    }
    Student(char* Number, char* Password, char* Name, char* Grade, char* College,char *Class, char* Major, char* course = '\0')
    {
        Copy(Number,number),Copy(Password,password),Copy(Name,name),Copy(Grade,grade),Copy(College,college),Copy(Major,major),Copy(Class,this->Class),Copy(course,this->course);
    }
    void transCourse( Course& x,char* cou_name,char* class_name);     //将课程类对象信息提取出来，并存在course数据中
    void set_number(char* number) { Copy(number,this->number ); }
    void set_pass(char* password) { Copy(password,this->password); }
    void set_name(char* name) { Copy(name,this->name); }
    void set_grade(char* grade) { Copy(grade,this->grade); }
    void set_major(char* major) { Copy(major,this->major); }
    void set_course(char* course) { Copy(course,this->course); }
    void set_college(char* college) { Copy(college,this->college); }
    void set_class(char* Class) { Copy(Class,this->Class); }
};

class Teacher :public User
{
public:
    char name[20];
    char course[100];

    Teacher() { name[0]=course[0]=number[0]=password[0]='\0'; }
    Teacher(char *Number, char* Password, char* Name, char* course = '\0')
    {
        Copy(Number,number), Copy(Password,password), Copy(Name,name), Copy(course,this->course);
    }
    Teacher(const Teacher &x)
    {
        Copy(x.name,name),Copy(x.number,number),Copy(x.course,course),Copy(x.password,password);
    }
    //void transCourse(const string& x) { course += x + "&"; }     //将课程类对象信息提取出来，并存在course数据中
    void set_number(char* number) { Copy(number,this->number); }
    void set_pass(char* password) { Copy(password,this->password); }
    void set_name(char* name) { Copy(name,this->name); }
    void set_course(char* course) { Copy(course,this->course); }
};

class Admini :public User      //教务员
{
public:
    char name[20];        //姓名
    Admini(){name[0]='\0',password[0]=number[0]='\0';}
    Admini(char *name)
    {
        Copy(name,this->name);
    }
    Admini(const Admini & x)
    {
        Copy(x.name,name),Copy(x.number,number),Copy(x.password,password);
    }
    void set_name(char *name)
    {
        Copy(name,this->name);
    }
};

class Find       //索引类键值对
{
public:
    char key[20];
    char value[40];
    Find() {key[0]=value[0]='\0';}
    Find(char *key,char* value)
    {
        Copy(key,this->key),Copy(value,this->value);
    }
};
struct cou_info {
    char cou_name[20];		//课程名字
    char class_name[20];		//教学班名
    char tea_name[20];		//授课老师姓名
    char position[20];		//授课地点
    char time[20];			//授课时间
    double propotion;		//平时成绩比例
}cur_course;
//-----------------------------------------功能函数-----------------------------------


//读取索引信息
void openFind(string file_name, multimap<string, string>& x);

//根据学号或者姓名找到对应位置并读取信息
//当学号或者姓名不存在时，返回0，否则返回1
template<typename T>
int copyInfo(string info, multimap<string, string>& x, vector<T>& y);

//根据学号或者姓名，把修改后的y写入对应位置
//当姓名或者学号不存在时，返回0；否则返回1；
template<typename T>
int modifyInfo(string info, multimap<string, string>& x, const T& y);

//根据学号或者姓名删除某对象的索引信息
template<typename T>
void deleteInfo(string info, multimap<string, string>& x, string file_name);

//增加信息，直接在文件后追加,并返回该信息偏移量（例如该信息前面已经有17个信息，则返回18）
template<typename T>
int addInfo(const T& info, string file_name);

//增加索引信息
void addIndex(string key, string value, multimap<string, string>& x, string file_name);

//增加学生、教师、教务员人员信息
//需要在数据文件和索引文件里追加信息
//需要提供人员信息，对应的索引对象，人员信息文件名，索引信息文件名
//由于有以姓名为主导和以学号为主导的文件，所以需要两个索引文件
template<typename T>
void addPerson(const T& info, multimap<string, string> x2, multimap<string, string> x3, string file_name1, string file_name2, string file_name3);
template<typename T>
void addPerson(const T& info, multimap<string, string> numberMap, string infoFile, string indexFile);

//前提：学生选课成功
//对学生类中course进行修改，在张萌五班中加入该学生
//需要提供学生个人信息，学号索引对象，课程名字，班级名字
// filename1 张萌五班
void addCourse(Student& info, multimap<string, string> x1, string cou_name, string class_name);
//判断账号是否存在，存在则返回密码，否则返回空字符串
//通过学号或者姓名找到学生信息表，读出账号密码信息
//函数需要提供用户登录的账号以及对应的multimap对象，其中该函数只处理一个索引对象
template<typename T>
string openAccount(string ID, const multimap<string, string>& x);

//读取整个文件的信息
//传入文件夹的名称
template<typename T>
int copyAllInfo(string file_name, vector<T>& x);

//分割字符串
vector<string> split(const string& str, const string& pattern);

//分割学生的course
vector<string> getStuCourse(const Student& s);

//分割教师的course
vector<string>getTeaCourse(const Teacher& tea);


//----------------------------------OP类-------------------------------------------

//主程序
class SystemOp {
public:
    int init() {
        openFind("Stu.dat", Stu_name);
        openFind("Teacher.dat", Tea);
        openFind("Admin.dat", Ad);
        return 0;
    }
    int Logout();
};
class StuOp
{
public:
    int Stu_Login(string name, string password); //学生登陆
    vector<Student> Stu_ReadScore(string stu_number);//用学号查成绩
};

class TeaOp
{
public:
    int Tea_Login(string name, string password);				//老师登陆
    vector<string>getTeaCourse(const Teacher& tea);				//读取教师所教课程（返回分割后的course）
    void getInfo(string filename);								//设置当前要访问的课程，并获取文件第一行课程信息
    vector<Course> Tea_ReadClassScore();						//查询当前访问课程成绩
    double getAverageScore(const vector<Course>&);				//返回学生平均成绩
    void Tea_SetPropotion(double proportion);					//设置当前课程平均分-期末分比例
    int changeScore(vector<Student>s, double score);			//修改学生文件中course（成绩）
    int InputScore(string name, double score1, double score2);   //修改学生成绩
	vector<pair<vector<Course>, string>>getAllStudent(const Teacher& tea);
};

class AdminOp
{
public:
    int Admin_Login(string number,vector<Admini> & x,string password);
    int Admin_Modify();
    int Admin_Search()
    {
        int SearchStu();
        int SearchTea();
        int SearchCourse();
        return 0;
    };
    int SearchStu_number(string number,vector<Student> & x);
    int SearchStu_name(string name,vector<Student> & x);
    int SearchTea_name(string name,vector<Teacher> &x);
    int SearchTea_number(string number,vector<Teacher> &x);
    int SearchCourse(string name,map<string,vector<Course>> &x,vector<string> & y);
    int multi_Search(string cou_name,string tea_name,map<string,vector<Course>> &x,vector<string> &y);
};

#endif // MAINH_H
