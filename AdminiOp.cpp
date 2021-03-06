
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
    int Admin_Login(string number,vector<Admini> & x)  //number���û�����Ĺ���  x�ǵ�½�ɹ��󷵻��û��ĸ�����Ϣ
    {
        string real_password = openAccount<Admini>(number, Ad_number);   //�����password���û����������,�ý���Ա��������
        if (real_password == "\0")return -1;		//�û�������
        else if (real_password == password)	//��¼�ɹ� ��½�ɹ�����û�������Ϣ¼��
        {
            copyInfo(number,Ad_number,x);
        }
        else return 0;
    }
    int Admin_Modify()
    {
        //�޸���Ϣ������ǰ�˵İ������ƺ�����д��ֱ�Ӱ��û��޸ĺ�����д��������У���ͨ��modifyInfo()����д���ļ���
    }
    int Admin_Search()
    {
        int SearchStu();
        int SearchTea();
        int SearchCourse();
        return 0;
    };
    int SearchStu_number(string number,vector<Student> & x)    //��ѧ������ѧ����Ϣ ǰ���û������ѧ�Ŵ���number������
    {
        //x�洢ѧ����Ϣ
        int flag=copyInfo(number,Ad_number,x);  //ѧ����Ϣ����x�У���ǰ��ʹ��
        return flag;   //flagΪ1��ʾ�����ɹ�����֮ʧ��
    }
    int SearchStu_name(string name,vector<Student> & x)      //����������ѧ������    ǰ���û��������������name������
    {
        int flag=copyInfo(name,Ad_name,x);  //ѧ����Ϣ����x�У���ǰ��ʹ��
        return flag;   //flagΪ1��ʾ�����ɹ�����֮ʧ��
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
    int SearchCourse(string name,map<string,vector<Course>> &x,vector<string> & y)     //x�м�¼�˿γ��ļ����Ϳγ���Ϣ��һһ��Ӧ y��¼�����пγ��ļ���
    {
        fstream f("Course//"+name+"//record.dat",ios::binary|ios::in);
        f.seekg(0,ios::end);
        long End=f.tellg(); f.seekg(0,ios::begin);
        for(;f.tellg()!=End;)
        {
            string temp;
            f.read((char*)&temp,sizeof(string));     //�����пγ��ļ�������y��
            y.push_back(temp);
        }
        if(y.size()==0) return 0;     //û�пγ̰༶
        f.close();      //��ȡ��ϣ������������ζ�ȡȫ���γ��ļ�

        for(int i=0;i<y.size();i++)
        {
            string temp="Course//"+name+"//"+y[i]+".dat";
            vector<Course> temp_cou;
            copyAllInfo(temp,temp_cou);    //����Ӧ�γ��ļ�����Ϣȫ������temp_cou�����У��ٱ�����x��
            x[name+"_"+y[i]]=temp_cou;  //��ȡ���  key=�����˼����ʵ��_����5��"
        }
        return 0;
    }
    int multi_Search(string cou_name,string tea_name,map<string,vector<Course>> &x,vector<string> &y)  //�ڽ���Ա�����γ���Ϣʱ��֧�������ؼ��֡����������γ����� ��ʦ
    {
        fstream f("Course//"+cou_name+"//record.dat",ios::binary|ios::in);
        f.seekg(0,ios::end);
        long End=f.tellg(); f.seekg(0,ios::begin);
        for(;f.tellg()!=End;)
        {
            string temp;
            f.read((char*)&temp,sizeof(string));     //�����пγ��ļ�������y��
            y.push_back(temp);
        }
        if(y.size()==0) return 0;     //û�пγ̰༶
        f.close();

        //��ʼ�ӿγ�������Ѱ�Һ���ʦ������ͬ�Ŀγ��ļ�
        for(int i=0;i<y.size();i++)
        {
            if(y[i].substr(0,tea_name.size())==tea_name)    //ȷ���ǲ��ҵ���ʦ
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
