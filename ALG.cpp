#include "alg.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include "string.h"
#include <cstdlib>


//静态成员
vector<string> ALG::firstname = {
        "佰胜","亚弘","天域","吉兴","银华","月启","亚金","游缘","启明","金为","缘凌","华茂",
        "信威","优真","讯迈","锐丰","安辰","鑫达","畅旺","鑫福","升晖","通森","腾辉","恒瑞"
    };

vector<string> ALG::lastname = {
     "王","李","张","刘","陈","杨","黄","赵","吴","周","徐","孙","马","朱","胡","郭","何","林","高","罗","郑","梁","谢"
};

vector<string> ALG::coursename = {
     "C++语言程序设计","Python语言程序设计","Java语言程序设计","数据结构","数据库","操作系统","编译原理","算法设计与分析","计算机组成原理"
};

vector<int> ALG::IndDig = {0,1,2,3,4,5,6,7,8,9};

vector<char> ALG::IndDigChar = {'0','1','2','3','4','5','6','7','8','9'};

vector<string> ALG::classname = {"一班","二班","三班","四班"};

int ALG::stucurnum = 0;
int ALG::teacurnum = 0;
int ALG::coucurnum = 0;



//辅助函数
StuCourse ALG::helper1(string str)
{
    StuCourse sc;
    for(int i=0;i<str.length();i++)
    {
        if(str[i]=='/')
        str[i] = ' ';
    }
    istringstream input(str);
    char* a=new char[20];double b;bool ok1;bool ok2;double c;
    input>>a>>b>>c;
    sc.incourname(a);
    sc.inNorGrade(b,ok1);
    sc.inFinGrade(c,ok2);
    return sc;
}

//辅助函数2
CourClass ALG::helper2(string str)
{
    CourClass cc;
    int leng = str.length();
    for(int i=0;i<leng;i++)
    {
        if(str[i]=='/')
            str[i]=' ';
    }
    istringstream input(str);
    char* a=new char[30];char* b = new char[30];
    input>>a>>b;
    strcpy(cc.courname,a);
    strcpy(cc.classname,b);
    return cc;
}

//将 double 转为只有一位小数的 string
string ALG::doubleTostring(double a)
{
    string t=to_string(a);
    int leng = t.length();
    for(int i=0;i<leng;i++)
    {
        if(t[i]=='.')
            return t.substr(0,i+2);
    }
    return "";
}

ALG::ALG()
{

}

//创建随机名字
string ALG::CreateRanName(int seed)
{
    random_shuffle(lastname.begin(),lastname.end());
    random_shuffle(firstname.begin(),firstname.end());
    string res = lastname[seed % lastname.size()] + firstname[seed % firstname.size()];
    return res;
}

//整数转为对应的四位字符串
string ALG::CreateXXXX(int n)
{
    if(n==0)
        return "0000";
    string res = "";
    while(n!=0)
    {
        int num = n % 10;
        res = char(num+48) + res;
        n = (n - num)/10;
    }
    while(res.length()<4)
    {
        res = "0" + res;
    }
    return res;
}

//创建唯一的 Id：
//n := ID 的位数
//type IN {1,2,3},1 := 学生学号,2 := 教师工号,3 := 课程编号
//forwardcode := 前导码
string ALG::CreateOnlyId(int n,int type, string forwardcode)
{
    int leng = forwardcode.length();
    if(leng+4>n)
        return "无效的 ID";
    else
    {
        string res = forwardcode;
        random_shuffle(IndDigChar.begin(),IndDigChar.end());
        for(int i=0;i+leng+4<n;i++)
        {
            res += IndDigChar[i%10];
        }
        string back;
        switch(type)
        {
        case 1:{back = CreateXXXX(stucurnum++);break;}
        case 2:{back = CreateXXXX(teacurnum++);break;}
        case 3:{back = CreateXXXX(coucurnum++);break;}
        }
        res += back;
        return res;
    }
}

//创建 n 个教师的随机信息
void ALG::CreateRanTeacher(int n, string InfPath, string NameToIndexPath, string IdToIndexPath)
{
    Teacher tea;
    TeaIndex index1;
    TeaIndex1 index2;
    fstream fout;
    fout.open(InfPath,ios::out|ios::binary);

    fstream findex1;
    findex1.open(NameToIndexPath,ios::out|ios::binary);
    fstream findex2;
    findex2.open(IdToIndexPath,ios::out|ios::binary);
    for(int i=0;i<n;i++)
    {
        tea.inteaname(CreateRanName(19).c_str());
        tea.inid(CreateOnlyId(12,2,"2019").c_str());
        string oripassword = "a123456";bool ok;
        tea.changepassword(oripassword.c_str(),ok);
        tea.incoursename(CreateRandTeaCour(3).c_str());
        fout.write((char*)&tea,sizeof(Teacher));

        strcpy(index1.teaname,tea.reteaname());
        index1.exposition = i * sizeof(Teacher);
        findex1.write((char*)&index1,sizeof(TeaIndex));

        strcpy(index2.id,tea.reid());
        index2.exposition = index1.exposition;
        findex2.write((char*)&index2,sizeof(TeaIndex1));
    }
    fout.close();
    findex1.close();
    findex2.close();
}

//创建 n 个课程
string ALG::CreateRandTeaCour(int n)
{
    string res = "";
    for(int i=0;i<n;i++)
    {
        if(i%coursename.size()==0 || i%classname.size()==0)
        {
            random_shuffle(coursename.begin(),coursename.end());
            random_shuffle(classname.begin(),classname.end());
        }
        res += coursename[i%coursename.size()]+"/"+classname[i%classname.size()];
        if(i!=n-1)
            res += "&";
    }
    return res;
}

//解析学生的 课程-平时成绩-期末成绩 串
vector<StuCourse> ALG::DecodeGrade(const char *a)
{
    string temp = string(a);
    vector<StuCourse> res;
    int leng = temp.length();
    string assi;
    int last = 0;
    for(int cur=0;cur<leng;cur++)
    {
        if(temp[cur]=='&')
        {
            assi = temp.substr(last,cur-last);
            res.push_back(helper1(assi));
            last = cur+1;
        }
        else if(cur == leng-1)
        {
            assi = temp.substr(last,cur-last+1);
            res.push_back(helper1(assi));
        }
    }
    return res;
}

//解析教师的 课程-班级 串
vector<CourClass> ALG::DecodeCourClass(const char *a)
{
    string temp = string(a);
    vector<CourClass> res;
    int leng = temp.length();
    string assi;
    int last = 0;
    for(int cur=0;cur<leng;cur++)
    {
        if(temp[cur]=='&')
        {
            assi = temp.substr(last,cur-last);
            res.push_back(helper2(assi));
            last = cur+1;
        }
        else if(cur == leng-1)
        {
            assi = temp.substr(last,cur-last+1);
            res.push_back(helper2(assi));
        }
    }
    return res;
}

//创建 n 个同一个学院的学生的信息，同一个学院表现在 InfPath 上，后两个文件是全校性的
void ALG::CreateRanStudent(int n, string InfPath, string IdToIndexPath, string NameToIndexPath)
{
    Student stu;
    fstream fout;
    fout.open(InfPath,ios::out|ios::binary);
    fstream fidindex;
    fidindex.open(IdToIndexPath,ios::app|ios::binary);
    fstream fnameindex;
    fnameindex.open(NameToIndexPath,ios::app|ios::binary);
    StuIdIndexs indexid;
    StuNameIndexs indexname;

    for(int i=0;i<n;i++)
    {
        stu.instuname(CreateRanName(38).c_str());
        stu.instuid(CreateOnlyId(12,1,"2021").c_str());
        string str1 = "计算机";
        string str2 = "a123456";
        bool did;
        stu.inmajor(str1.c_str());
        stu.changepassword(str2.c_str(),did);
        stu.incourseandgrade(CreateRanCourGrade(5).c_str());
        fout.write((char*)&stu,sizeof(Student));

        strcpy(indexid.stuid,stu.restuid());
        string s = InfPath + '#' + to_string(i*sizeof(Student));
        strcpy(indexid.PathAndExpo,s.c_str());
        fidindex.write((char*)&indexid,sizeof(StuIdIndexs));

        strcpy(indexname.stuname,stu.restuname());
        string st = InfPath + '#' + to_string(i*sizeof(Student));
        strcpy(indexname.PathAndExpo,st.c_str());
        fnameindex.write((char*)&indexname,sizeof(StuNameIndexs));
    }
    fout.close();
    fidindex.close();
    fnameindex.close();
}

//返回位于 [a,b] 的随机浮点数，但效率不高
double ALG::CreateRandDoubleBetween(double a, double b)
{
    double res;
    do
    {
        double point = rand()%10/10.0;
        double base = rand()%10;
        double tens = rand()%10;
        res = tens*10.0 + base + point;
    }while(res<a || res > b);
    return res;

}

//产生 n 个随机课程成绩信息
string ALG::CreateRanCourGrade(int n)
{
    string res = "";

    for(int i=0;i<n;i++)
    {
        if(i%coursename.size()==0)
            random_shuffle(coursename.begin(),coursename.end());
        res+=coursename[i];
        res+='/';
        res+=doubleTostring(CreateRandDoubleBetween(60,100));
        res+='/';
        res+=doubleTostring(CreateRandDoubleBetween(50,100));
        if(i!=n-1)
            res+='&';
    }
    return res;
}

//解析 路径-偏移 对
pathAndexpo ALG::DecodePathAndExpo(const char *a)
{
    string temp = string(a);
    int leng = temp.length();
    for(int i=0;i<leng;i++)
    {
        if(temp[i]=='#')
        {
            temp[i] = ' ';
            break;
        }
    }
    istringstream input(temp);
    char* b = new char[50];
    long expo;
    input>>b>>expo;
    pathAndexpo res;
    strcpy(res.path,b);
    res.exposition = expo;
    return res;
}

