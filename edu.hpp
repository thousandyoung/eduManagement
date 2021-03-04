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

using namespace std;
class SystemOp{
public:
    int Login();
    int Logout();
};
class StuOp
{
public:
    int Stu_Login() ; //学生登陆

    void Stu_ReadScore()
    {
        
    };  //学生查成绩
    
    
};

class TeaOp
{
public:
    int Tea_Login();               //老师登陆
    int Tea_ReadClassScore();        //查询这门课程成绩
    int Tea_SetPropotion();          //设置平均分-期末分比例
    int Tea_ModifyScore()             //批改成绩
    {
        int InputScore();         //输入平时分期末分
        int CalScor();              //计算总评
        return 0;
    };
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
class Student
{
public:
    string name;
    string number;   //学号
    string college;  //学院
    string major;    //专业
    string course;   //学生全部课程信息
};

class Teacher
{
public:
    string name;
    string number;   //工号
    string course;    //所教课程名字的集合
};

class Admini        //教务员
{
public:
    string name;
};

class Find       //索引类键值对
{
public:
    string key;
    string value;
    Find()
    {
        ;
    }
    Find(string a,string b)
    {
        key=a,value=b;
    }
};

class course       //存储在课程课文中的课程类
{
public:
    string cou_name;       //课程名字
    string stu_id       //  学生学号
    string stu_name;      //学生姓名       学生学号？
    string position;       //授课地点
    string time;          //授课时间
    string grade;         //学生成绩
};
#endif /* edu_hpp */
