#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<map>
using namespace std;
class User {
	string number;      //学号 只能用学号或者工号登录
	string password;
};
class Student : public User
{
public:
    string name;
    string grade;      //年级
    string college;  //学院
    string major;    //专业
    string Class;     //班级
    string course;   //学生全部课程信息。以 课程名字/授课地点/授课时间/授课老师姓名/成绩&课程姓名/授课地点/.....
    Student() {;}
    Student(string Number,string Password,string Name,string Grade,string College,string Major,string Classstring course="\0")
    {
        number=Number,password=Password,name=Name,grade=Grade,college=College,major=Major,this->Class=Class,this->course=course;
    }
    void transCourse(const Course & x) ;     //将课程类对象信息提取出来，并存在course数据中
    void set_number(string number) {this->number=number;}
    void set_pass(string password) {this->password=password;}
    void set_name(string password) {this->name=name;}
    void set_grade(string grade) {this->grade=grade;}
    void set_major(string major) {this->major=major;}
    void set_course(string course) {this->course=course;}
    void set_college(string college) {this->college=college;}
    void set_class(string Class) {this->Class=Class;}
};

void Student::transCourse(const Course & x)
{
    course+=x.cou_name+"/"+x.position+"/"+x.time+"/"+x.tea_name+"/"+x.mark+"&";
}

class Teacher : public User
{
public:
    string name;   //姓名
    string course;    //所教课程名字的集合 格式为 课程名字&课程名字&...
    Teacher() {;}
    Teacher(string Number,string Password,string Name,string course="\0")
    {
        number=Number,password=Password,name=Name,this->course=course;
    }
    void transCourse(const Course & x) {course+=x.cou_name+"&";}     //将课程类对象信息提取出来，并存在course数据中
    void set_number(string number) {this->number=number;}
    void set_pass(string password) {this->password=password;}
    void set_name(string password) {this->name=name;}
    void set_course(string course) {this->course=course;}
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
    Find(){}
    Find(string a,string b)
    {
        key=a,value=b;
    }
};

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

/*----功能函数-----*/
//读取索引信息
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

//根据学号或者姓名找到对应位置并读取信息
//当学号或者姓名不存在时，返回0，否则返回1
template<typename T>
int copyInfo(string info,multimap<string,string> & x,vector<T> & y)    //y为需要读取的信息;用vector保存原因是防止有多个对象
{
    int num=x.count(info);
    if(num==0) return 0;
    multimap<string,string>::iterator it=x.find(info);
    for(int i=0;i<num;i++)
    {
        string posi=(*it).second;    //得到信息的偏移量,文件绝对地址&偏移量
        string a(posi,0,posi.find('&')),b(posi,posi.find('&')+1,posi.size()-posi.find('&')-1);
        fstream f(a,ios::binary|ios::in);
        f.seekg(long(sizeof(T)*atoi(b.c_str())),ios::beg);      //偏移到对应位置
        T temp;
        f.read((char*)&temp,sizeof(T));      //读取信息
        y.push_back(temp);
        it++;
        f.close();
    }
    return 1;
}

//根据学号或者姓名，把修改后的y写入对应位置
//当姓名或者学号不存在时，返回0；否则返回1；
template<typename T>
int modifyInfo(string info,multimap<string,string> & x,const T & y)
{
    if(x.count(info)==0) return 0;
    multimap<string,string>::iterator it=x.find(info);
    string posi=(*it).second;    //得到信息的偏移量,文件绝对地址&偏移量
    string a(posi,0,posi.find('&')),b(posi,posi.find('&')+1,posi.size()-posi.find('&')-1);
    fstream f(a,ios::binary|ios::out);
    f.seekp(long(sizeof(T)*atoi(b.c_str())),ios::beg);
    f.write((char*)&y,sizeof(T));
    f.close();
    return 1;
}

//根据学号或者姓名删除某对象的索引信息
template<typename T>
void deleteInfo(string info,multimap<string,string> & x,string file_name)
{
    fstream f(file_name,ios::binary|ios::out|ios::trunc);
    x.erase(info);
    multimap<string,string>::iterator it=x.begin();    //将修改后的索引信息重新写入文件
    for(;it!=x.end();it++)
    {
        Find temp((*it).first,(*it).second);
        f.write((char*)&temp,sizeof(temp));
    }
    f.close();         //索引信息在文件中删除完毕
}

//增加信息，直接在文件后追加,并返回该信息偏移量（例如该信息前面已经有17个信息，则返回18）
template<typename T>
int addInfo(const T & info,string file_name)
{
    fstream f(file_name,ios::out|ios::binary|ios::app);
	f.write((char*)&info, sizeof(T));
	int value = ((long)f.tellp() - ios::beg) / sizeof(T);
	f.close();
	return value;
}

//增加索引信息
void addIndex(string key,string value,multimap<string,string> & x,string file_name)     //file_name为索引文件
{
    x.insert(make_pair(key,value));
    Find temp(key,value);
    fstream f(file_name,ios::binary|ios::app|ios::out);
    f.write((char*)&temp,sizeof(temp));
    f.close();
}

//增加学生、教师、教务员人员信息
//需要在数据文件和索引文件里追加信息
//需要提供人员信息，对应的索引对象，人员信息文件名，索引信息文件名
//由于有以姓名为主导和以学号为主导的文件，所以需要两个索引文件
template<typename T>
void addPerson(const T & info,multimap<string,string> x2,multimap<string,string> x3,string file_name1,string file_name2,string file_name3)
{
    int num=addInfo(info,file_name1);   //得到偏移量
    addIndex(info.name,file_name1+"&"+to_string(num),x2,file_name2);
    addIndex(info.number,file_name1+"&"+to_string(num),x3,file_name3);
}

//前提：学生选课成功
//在对应课程下增加信息，并更新课程索引信息；更改学生个人信息，更新文件
//需要提供学生个人信息，学号索引对象，课程名字，课程索引对象，课程信息文件，索引信息文件名
//由于有以姓名为主导和以学号为主导的文件，所以需要两个索引文件
void addCourse(const Student & info,multimap<string,string> x1,string cou_name,multimap<string,string>& x2,multimap<string,string> &x3,string file_name1,string file_name2.string file_name3)
{
    fstream f(file_name1,ios::in|ios::binary);    //打开文件，读取课程信息
    Course temp;
    f.read((char*)&temp,sizeof(Course)); f.close();
    temp.stu_name=info.name,temp.stu_number=info.number;
    info.transCourse(temp);   //修改学生课程信息
    modifyInfo(info.number,x1,info);  //修改到学生文件中
    int num=addInfo(temp,file_name1); //修改课程文件信息
    addIndex(info.name,file_name1+"&"+to_string(num),x2,file_name2);
    addIndex(info.number,file_name1+"&"+to_string(num),x3,file_name3);
}


//判断账号是否存在，存在则返回密码，否则返回空字符串
//通过学号或者姓名找到学生信息表，读出账号密码信息
//函数需要提供用户登录的账号以及对应的multimap对象，其中该函数只处理一个索引对象
template<typename T>
string openAccount(string ID,const multimap<string,string> & x) {
    int flag=x.count(ID);      //检查账户是否存在
    if(flag==0) return "\0";     //账户不存在直接返回空字符串
    multimap<string,string>::iterator it=x.find(ID);
    string posi=(*it).second;    //得到信息的偏移量,文件绝对地址&偏移量
    string a(posi,0,posi.find('&')),b(posi,posi.find('&')+1,posi.size()-posi.find('&')-1);
    fstream f(a,ios::binary|ios::in);
    f.seekg(long(sizeof(T)*atoi(b.c_str())),ios::beg);      //偏移到对应位置
	T temp;
	f.read((char*)&temp,sizeof(T));   //读取信息
	f.close();
	return temp.password;
}

//读取整个文件的信息
//传入文件夹的名称
template<typename T>
int copyAllInfo(string file_name,vector<T> & x)
{
    fstream f(file_name,ios::binary|ios::in);
    f.seekg(0,ios::end);
    long End=f.tellg();    //获取末位置
    f.seekg(0,ios::beg);
    for(;f.tellg()!=End;)
    {
        T temp;
        f.read((char*)&temp,sizeof(T));
        x.push_back(temp);
    }
    f.close();    //读取完全部信息
}

/*
//验证账号密码
template<typename T>
int checkAccount(string password, vector<T>& y) {
	if (y.empty())return -1;
	if (y[0].password == password)return 1;
	return 0;
}
*/

//教师增加选课信息——>教务员同意————》发布选课信息————》增加教师选课的信息、学生信息
//教师增加一门课程的同时，应该在文件里添加上课程信息
