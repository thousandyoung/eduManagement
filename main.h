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

	string stu_name;      //学生姓名
	string stu_number;    //学生学号
	string usual_grade;         //平时成绩
	string final_grade;        //期末成绩
	string overall_grade;       //总评成绩
	Course(){}
	Course(string stu_name,string stu_number,string usual_grade,string final_grade,string overall_grade):stu_name(stu_name),stu_number(stu_number),usual_grade(usual_grade),final_grade(final_grade),overall_grade(overall_grade){}
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
	string course;   //学生全部课程信息。以 课程名字/总评成绩/课程名字/总评成绩...
	Student() { ; }
	Student(string Number, string Password, string Name, string Grade, string College, string Major, string course = "\0")
	{
		number = Number, password = Password, name = Name, grade = Grade, college = College, major = Major, this->Class = Class, this->course = course;
	}
	void transCourse(const Course& x,string cou_name,string class_name);     //将课程类对象信息提取出来，并存在course数据中
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
	//void transCourse(const string& x) { course += x + "&"; }     //将课程类对象信息提取出来，并存在course数据中
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
template<typename T>
void addPerson(const T& info, multimap<string, string> numberMap, string infoFile, string indexFile);

//前提：学生选课成功
//对学生类中course进行修改，在张萌五班中加入该学生
//需要提供学生个人信息，学号索引对象，课程名字，课程索引对象，课程信息文件，索引信息文件名
// filename1 张萌五班
void addCourse(Student& info, multimap<string, string> x1, string cou_name, string class_name, string file_name1);
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
