//
//  edu.hpp
//  4
//
//  Created by Takashii on 2021/3/4.
//

#ifndef edu_hpp
#define edu_hpp

#include <stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<map>

using namespace std;

multimap<string, string>Stu_number;
multimap<string, string>Stu_name;
multimap<string, string>Tea;
multimap<string, string>Ad;
//---------------------------------------各类定义-----------------------------------------
class Course       //存储在课程文件中的课程类
{
public:
    string cou_name;       //课程名字
    string tea_name;       //授课老师姓名
    string stu_name;      //学生姓名
    string stu_number;    //学生学号
    string position;       //授课地点
    string time;          //授课时间
    string mark;         //学生成绩
};

class User {
public:
	string number;      //学号 只能用学号或者工号登录
	string password;
};

class Student : public User
{
public:
	string name;
	string grade;    //年级
	string college;  //学院
	string major;    //专业
	string Class;    //班级
	string course;   //学生全部课程信息。以 课程名字/授课地点/授课时间/授课老师姓名/成绩&课程姓名/授课地点/.....
	Student() { ; }
	Student(string Number, string Password, string Name, string Grade, string College, string Major, string course = "\0")
	{
		number = Number, password = Password, name = Name, grade = Grade, college = College, major = Major, this->Class = Class, this->course = course;
	}
	void transCourse(const Course& x);     //将课程类对象信息提取出来，并存在course数据中
	void set_number(string number) { this->number = number; }
	void set_pass(string password) { this->password = password; }
	void set_name(string password) { this->name = name; }
	void set_grade(string grade) { this->grade = grade; }
	void set_major(string major) { this->major = major; }
	void set_course(string course) { this->course = course; }
	void set_college(string college) { this->college = college; }
	void set_class(string Class) { this->Class = Class; }
};

class Teacher : public User
{
public:
	string name;   //姓名
	string course;    //所教课程名字的集合 格式为 课程名字&课程名字&...
	Teacher() { ; }
	Teacher(string Number, string Password, string Name, string course = "\0")
	{
		number = Number, password = Password, name = Name, this->course = course;
	}
	void transCourse(const Course& x) { course += x.cou_name + "&"; }     //将课程类对象信息提取出来，并存在course数据中
	void set_number(string number) { this->number = number; }
	void set_pass(string password) { this->password = password; }
	void set_name(string password) { this->name = name; }
	void set_course(string course) { this->course = course; }
};

class Admini :public User      //教务员
{
public:
	string name;        //姓名
};

class Find       //索引类键值对
{
public:
	string key;
	string value;
	Find() {}
	Find(string a, string b):key(a),value(b){}
};
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

//前提：学生选课成功
//在对应课程下增加信息，并更新课程索引信息；更改学生个人信息，更新文件
//需要提供学生个人信息，学号索引对象，课程名字，课程索引对象，课程信息文件，索引信息文件名
//由于有以姓名为主导和以学号为主导的文件，所以需要两个索引文件
void addCourse(const Student& info, multimap<string, string> x1, Course temp, multimap<string, string>& x2, multimap<string, string>& x3, string file_name1, string file_name2, string file_name3);
//判断账号是否存在，存在则返回密码，否则返回空字符串
//通过学号或者姓名找到学生信息表，读出账号密码信息
//函数需要提供用户登录的账号以及对应的multimap对象，其中该函数只处理一个索引对象
template<typename T>
string openAccount(string ID, const multimap<string, string>& x);

//读取整个文件的信息
//传入文件夹的名称
template<typename T>
int copyAllInfo(string file_name, vector<T>& x);


//----------------------------------OP类-------------------------------------------

//主程序
class SystemOp {
public:
    void init() {
        openFind("Stu.dat", Stu);
        openFind("Teacher.dat", Tea);
        openFind("Admin.dat", Ad);
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
    int Tea_Login(string name, string password);                //老师登陆
    int Tea_ReadClassScore();       //查询这门课程成绩
    int Tea_SetPropotion();         //设置平均分-期末分比例
    int Tea_ModifyScore();          //批改成绩;
    int InputScore();
    int CalScore();
};

class AdminOp
{
public:
    int Admin_Login();
    int Admin_Modify();
    int Admin_Search()
    {
        int SearchStu();
        int SearchTea();
        int SearchCourse();
        return 0;
    };
    int SearchStu();
    int SearchTea();
    int SearchCourse();
    int multi_Search();
};
#endif /* edu_hpp */
