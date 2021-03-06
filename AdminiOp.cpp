
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
multimap<string, string>Tea_number;
multimap<string, string>Tea_name;
multimap<string, string>Ad_number;
multimap<string, string>Ad_name;


class AdminOp
{
public:
    int Admin_Login(string number,vector<Admini> & x)  //number是用户输入的工号  x是登陆成功后返回用户的个人信息
    {
        string real_password = openAccount<Admini>(number, Ad_number);   //这里的password是用户输入的密码,用教务员工号来查
        if (real_password == "\0")return -1;		//用户不存在
        else if (real_password == password)	//登录成功 登陆成功后把用户个人信息录入
        {
            copyInfo(number,Ad_number,x);
        }
        else return 0;
    }
    int Admin_Modify()
    {
        //修改信息可以在前端的按键控制函数里写，直接把用户修改后厄对象写道类对象中，再通过modifyInfo()函数写到文件里
    }
    int Admin_Search()
    {
        int SearchStu();
        int SearchTea();
        int SearchCourse();
        return 0;
    };
    int SearchStu_number(string number,vector<Student> & x)    //按学号搜索学生信息 前端用户输入的学号传入number对象中
    {
        //x存储学生信息
        int flag=copyInfo(number,Ad_number,x);  //学生信息存在x中，供前端使用
        return flag;   //flag为1表示搜索成功，反之失败
    }
    int SearchStu_name(string name,vector<Student> & x)      //按名字搜索学生名字    前端用户输入的姓名传入name对象中
    {
        int flag=copyInfo(name,Ad_name,x);  //学生信息存在x中，供前端使用
        return flag;   //flag为1表示搜索成功，反之失败
    }
    int SearchTea_number(string number,vector<Teacher> &x)
    {
        int flag=copyInfo(number,Tea_number,x);
        return flag;
    }
    int SearchTea_name(string name,vector<Teacher> &x)
    {
        int flag=copyInfo(name,Tea_name,x);
        return flag;
    }
    int SearchCourse(string name,map<string,vector<Course>> &x,vector<string> & y)     //x中记录了课程文件名和课程信息的一一对应 y记录了所有课程文件名
    {
        fstream f("Course//"+name+"//record.dat",ios::binary|ios::in);
        f.seekg(0,ios::end);
        long End=f.tellg(); f.seekg(0,ios::begin);
        for(;f.tellg()!=End;)
        {
            string temp;
            f.read((char*)&temp,sizeof(string));     //将所有课程文件名读入y中
            y.push_back(temp);
        }
        if(y.size()==0) return 0;     //没有课程班级
        f.close();      //读取完毕，接下来再依次读取全部课程文件

        for(int i=0;i<y.size();i++)
        {
            string temp="Course//"+name+"//"+y[i]+".dat";
            vector<Course> temp_cou;
            copyAllInfo(temp,temp_cou);    //将对应课程文件中信息全部读入temp_cou容器中，再保存入x中
            x[name+"_"+y[i]]=temp_cou;  //读取完毕  key=“马克思主义实践_张萌5班"
        }
        return 0;
    }
    int multi_Search(string cou_name,string tea_name,map<string,vector<Course>> &x,vector<string> &y)  //在教务员搜索课程信息时，支持两个关键字————》课程名字 老师
    {
        fstream f("Course//"+cou_name+"//record.dat",ios::binary|ios::in);
        f.seekg(0,ios::end);
        long End=f.tellg(); f.seekg(0,ios::begin);
        for(;f.tellg()!=End;)
        {
            string temp;
            f.read((char*)&temp,sizeof(string));     //将所有课程文件名读入y中
            y.push_back(temp);
        }
        if(y.size()==0) return 0;     //没有课程班级
        f.close();

        //开始从课程名字中寻找和老师名字相同的课程文件
        for(int i=0;i<y.size();i++)
        {
            if(y[i].substr(0,tea_name.size())==tea_name)    //确认是查找的老师
            {
                vector<Course> temp_cou;
                copyAllInfo("Course//"+cou_name+"//"+y[i]+".dat",temp_cou);
                x[cou_name+"_"+y[i]]=temp_cou;
            }
        }
        return 1;
    }
};
#endif /* edu_hpp */
