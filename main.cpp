#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>

using namespace std;
class SystemOp{
public:
    Login{}
    Logout{}
}
class StuOp
{
public:
    Stu_Login{}  //学生登陆

    Stu_ReadScore
    {
        
    } //学生查成绩
    
    
}

class TeaOp
{
public:
    Tea_Login{}                 //老师登陆
    Tea_ReadClassScore{}        //查询这门课程成绩
    Tea_SetPropotion{}          //设置平均分-期末分比例
    Tea_ModifyScore             //批改成绩
    {
        InputScore{}            //输入平时分期末分
        CalScore{}              //计算总评
    }
    InputScore{}
    CalScore{}
}

class AdminOp
{
public:
    Admin_Login{}
    Admin_Modify
    {
        
    }
    Admin_Search
    {
        SearchStu{}
        SearchTea{}
        SearchCourse{}
    }
    SearchStu{}
    SearchTea{}
    SearchCourse{}
    multi_Search{}
}
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
    string stu_name;      //学生姓名       学生学号？
    string position;       //授课地点
    string time;          //授课时间
    string grade;         //学生成绩
};

/*----功能函数-----*/
//读取索引信息 	读索引
void openFind(string file_name,multimap<string,string> & x)
{
    fstream f(file_name,ios::binary|ios::in);
    f.seekg(0,ios::end);
    long pos=f.tellg();    //得到文件最后的指针位置
    Find temp;
    for(f.seekg(0,ios::beg);f.tellg()!=pos;)
    {
        f.read((char*)&temp,sizeof(temp));
        x.insert(make_pair(temp.key,temp.value));     //将索引信息读入容器
    }
    f.close();
}

//根据学号或者姓名找到对应位置并读取信息  	读学生信息
template<typename T>
void copyInfo(string info,multimap<string,string> & x,vector<T> & y)    //y为需要读取的信息;用vector保存原因是防止有多个对象
{
    int num=x.count(info); 	//可能有同名
    multimap<string,string>::iterator it=x.find(info);	//定位索引
    for(int i=0;i<num;i++)
    {
        string posi=(*it).second;    //得到信息的偏移量,<文件绝对地址&偏移量>
        string a(posi,0,posi.find('&')),b(posi,posi.find('&')+1,posi.size()-posi.find('&')-1); 	//a 文件名 b 偏移量
        fstream f(a,ios::binary|ios::in);
        f.seekg(long(sizeof(T)*atoi(b.c_str())),ios::beg);      //偏移到对应位置
        T temp;
        f.read((char*)&temp,sizeof(T));      //读取信息
        y.push_back(temp);
        it++;
        f.close();
    }
}

//根据学号或者姓名，把修改后的y写入对应位置	写学生信息
template<typename T>
void modifyInfo(string info,multimap<string,string> & x,const T & y)
{
    multimap<string,string>::iterator it=x.find(info);
    string posi=(*it).second;    //得到信息的偏移量,文件绝对地址&偏移量
    string a(posi,0,posi.find('&')),b(posi,posi.find('&')+1,posi.size()-posi.find('&')-1);
    fstream f(a,ios::binary|ios::out);
    f.seekp(long(sizeof(T)*atoi(b.c_str())),ios::beg);
    f.write((char*)&y,sizeof(T));
    f.close();
}

//根据学号或者姓名删除某对象的索引信息		删除索引
template<typename T>
void deleteIndex(string info,multimap<string,string> & x,string file_name)
{
    fstream f(file_name,ios::binary|ios::out|ios::trunc);
    x.erase(info);
    multimap<string,string>::iterator it=x.begin();    //将修改后的索引信息重新写入文件
    for(;it!=x.end();it++)
    {
        Find temp((*it).first,(*it).second);		//Find 构造函数
        f.write((char*)&temp,sizeof(temp));
    }
    f.close();         //索引信息在文件中删除完毕
}

//增加信息，直接在文件后追加,并返回该信息偏移量（例如该信息前面已经有17个信息，则返回18）
template<typename T>
int addInfo(const T & info,string file_name)
{
    fstream f(file_name,ios::out|ios::binary|ios::app);
    f.write((char*)&info,sizeof(T));

    f.close();
}

//增加索引信息				增加索引
void addIndex(string key,string value,multimap<string,string> & x,string file_name)     //file_name为索引文件
{
    x.insert(make_pair(key,value));
    Find temp(key,value);
    fstream f(file_name,ios::binary|ios::app|ios::out);
    f.write((char*)&temp,sizeof(temp));
    f.close();
}
