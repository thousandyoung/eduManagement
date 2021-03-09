#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<map>
#include<vector>
using namespace std;

//�γ̵���Ŀ����ʦ������Ա���������༶����������ʱ��ȷ����
//�ȵ���addRandomTeacher()���ɼ�����ʦ������Ա���γ��ļ�����Ϣ
//Ȼ��������10��addRandomClass()����10���༶��Ϣ
//�ļ�����·��д��file_class,file_index��
//��δ����



string class_name[10]={"�ƿ�1��","�ƿ�2��","�Ű�1��","�Ű�2��","����1��","����2��","��Ժ1��","��Ժ2��","���1��","���1��"};
string grade_name[4]={"2017��","2018��","2019��","2020��"};
string major_name[10]={"�������ѧ�뼼��","�������ѧ�뼼��","��Ϣ��ȫ","��Ϣ��ȫ","���繤��","���繤��","������ȫ","������ȫ","���רҵ","���רҵ"}
string college_name[10]={"�������ѧ�빤��ѧԺ","�������ѧ�빤��ѧԺ","�������ѧ�빤��ѧԺ","�������ѧ�빤��ѧԺ","�������ѧ�빤��ѧԺ","�������ѧ�빤��ѧԺ","������ѧ�빤��ѧԺ","������ѧ�빤��ѧԺ","���ѧԺ","���ѧԺ"};
string before_name[20]={"��", "Ǯ", "��", "��", "��", "��", "֣", "��", "��", "��", "��", "��", "��","��","¬","��","��ٹ", "˾��", "�Ϲ�", "ŷ��"};
string after_name[140]={"ΰ", "��", "��", "��", "��", "��", "ǿ", "��", "ƽ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "־", "��", "��", "��", "��", "ɽ", "��", "��", "��", "��", "��", "��", "��", "Ԫ", "ȫ", "��", "ʤ", "ѧ", "��", "��", "��", "��", "��", "��", "��", "��", "��","��", "˳", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ï", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "׳", "��", "˼", "Ⱥ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ԣ", "��", "��", "��", "��", "��", "��", "��", "ǫ", "��", "��", "��", "֮", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ά", "��", "��", "��", "��", "��", "��", "��", "��", "��", "ʿ", "��", "��", "��", "��", "��", "��", "��", "��", "ʱ", "̩", "ʢ"};
int index_class=-1;  //�õ��İ༶�������ֻ������10���༶�ļ�
string before_num="20003034";   //ѧ��ǰ��̶�λ��ѧ�Ź�12λ���̶�λ8λ
ine index_num=-1;   //ѧ�ź�4λ����˳�����
string sex[2]=["��","Ů"];
string tea_number="20001233"; //��ʦ������Ա���Ź̶���12Ϊ
int index_num_tea=-1;

string file_student="D:\\dataWork\\Class\\";  //�洢ѧ����Ϣ�ļ�·��
string file_course="D:\\dataWork\\Course\\";  //�洢�γ���Ϣ�ļ�·��
string file_teacher="D:\\dataWork\\teacher.dat";  //�洢��ʦ��Ϣ�ļ�·��
string file_admini="D:\\dataWork\\admini.dat";    //�洢����Ա��Ϣ�ļ�·��
string file_index="D:\\dataWork\\index\\";       //�洢�����ļ�·��

string course_name={"���ݽṹ","���ݽṹ","���˼ʵ��","���˼ʵ��","��ѧӢ��","��ѧӢ��"};
string course_class={"����1��","����2��","����1��","����2��","����1��","����2��"};

string getRandomNum(int & index_num)  //��ȡѧ��
{
    index_num++;
    if(index_num<10)
    {
        string temp=before_num+"000"+to_string(index_num);
    }
    else if(index_num<100)
    {
        string temp=before_num+"00"+to_string(index_num);
    }
    else if(index_num<1000)
    {
        string temp=before_num+"0"+to_string(index_num);
    }
    else
    {
        string temp=before_num+to_string(index_num);
    }
    return temp;
}

string getRandomSex()  //�������Ա�
{
    int x=rand()%2;
    return sex[x];
}

string getRandomName()  //����������
{
    int x=rand()%20;
    int y=rand()%140;
    string temp=before_name[x]+after_name[y];
    return temp;
}

string addRandomClass()  //������ɰ༶��Ϣ
{
    int student_num=rand()%70;
    if(student_num<20) student+=20;  //�༶����20��
    int xx=rand()%4;  //�������꼶��Ϣ
    string temp_grade=grade_name[xx];
    index_class++;  //��˳�򴴽��༶
    for(int i=0;i<student_num;i++)
    {
        Student x;
        x.set_number(getRandomNum(index_num));
        x.set_name(getRandomName());
        x.set_grade(temp_grade);
        x.set_college(college_name[index_class]);
        x.set_major(major_name[index_class]);
        x.set_class(class_name[index_class]);
        x.set_pass("123456");  //���ó�ʼ����
        x.set_course("\0");

        //������ɿγ���Ϣ
        //�������趨ÿ��ѧ��ֻѡһ�ſ�
        int flag=rand()%6;

        Course temp;
        string fileName = file_course+cou_name + "/" + class_name + ".dat";
        temp.stu_name = info.name; temp.stu_number = info.number;
        temp.usual_grade = "None"; temp.final_grade = "None"; temp.overall_grade = "None";
        x.transCourse(temp,course_name[flag],course_class[flag]);   //�޸�ѧ���γ���Ϣ
        addInfo(temp, fileName); //�޸Ŀγ��ļ���Ϣ

        //��ѧ����Ϣ��ӽ��ļ�
        addPerson(x,Stu_name,Stu_number,file_student+class_name[index_class],file_index+"Stu_name.dat",file_index+"Stu_number.dat");
    }
}

//��ʱֻ���ɼ�����ʦ��Ϣ
string addRandomTeacher()
{
    Teacher x1(getRandomNum(index_num_tea),"123456","����","���ݽṹ/����1��&���ݽṹ/����2��&");
    Teacher x2(getRandomNum(index_num_tea),"123456","����","���˼ʵ��/����1��&���˼ʵ����/����2��&");
    Teacher x3(getRandomNum(index_num_tea),"123456","����","��ѧӢ��/����1��&��ѧӢ��/����2��&");

    Admini y1;
    y1.number=getRandomNum(index_num_tea),y1.password="123456",y1.name="��÷÷";

    addPerson(y1,Ad,file_admini,file_index+"Admini_index.dat");  //���ӽ���Ա��Ϣ
    addPerson(x1,Tea,file_teacher+file_index+"Teacher_index.dat");  //���ӽ�ʦ��Ϣ
    addPerson(x2,Tea,file_teacher+file_index+"Teacher_index.dat");  //���ӽ�ʦ��Ϣ
    addPerson(x3,Tea,file_teacher+file_index+"Teacher_index.dat");  //���ӽ�ʦ��Ϣ

    //���Ӽ����γ̵��ļ�
    cou_info a1,a2,a3,a4,a5,a6;
    a1.cou_name="���ݽṹ",a1.class_name="����1��",a1.tea_name="����",a1.position="A3 306",a1.time="��һ��һ�ڶ���",a1.propotion=0.4;
    a2.cou_name="���ݽṹ",a2.class_name="����2��",a2.tea_name="����",a2.position="A3 306",a2.time="�ܶ���һ�ڶ���",a2.propotion=0.4;
    a3.cou_name="���˼ʵ��",a3.class_name="����1��",a3.tea_name="����",a3.position="A2 206",a3.time="��һ�������߽�",a3.propotion=0.5;
    a4.cou_name="���˼ʵ��",a4.class_name="����2��",a4.tea_name="����",a4.position="A2 306",a4.time="�ܶ���һ�ڶ���",a4.propotion=0.5;
    a5.cou_name="��ѧӢ��",a5.class_name="����1��",a5.tea_name="����",a5.position="A4 306",a5.time="������һ�ڶ���",a5.propotion=0.3;
    a6.cou_name="��ѧӢ��",a6.class_name="����2��",a6.tea_name="����",a6.position="A4 306",a6.time="���ĵ�һ�ڶ���",a6.propotion=0.3;
    fstream f(file_Course+"���ݽṹ//����1��.dat",ios::in|ios::out|ios::binary); f.write((char*)&a1,sizeof(a1)); f.close();
    fstream f(file_Course+"���ݽṹ//����2��.dat",ios::in|ios::out|ios::binary); f.write((char*)&a2,sizeof(a2)); f.close();
    fstream f(file_Course+"���˼ʵ��//����1��.dat",ios::in|ios::out|ios::binary); f.write((char*)&a3,sizeof(a3)); f.close();
    fstream f(file_Course+"���˼ʵ��//����2��.dat",ios::in|ios::out|ios::binary); f.write((char*)&a4,sizeof(a4)); f.close();
    fstream f(file_Course+"��ѧӢ��/����1��.dat",ios::in|ios::out|ios::binary); f.write((char*)&a5,sizeof(a5)); f.close();
    fstream f(file_Course+"��ѧӢ��//����2��.dat",ios::in|ios::out|ios::binary); f.write((char*)&a6,sizeof(a6)); f.close();
}

//ע���ǵø�ÿ��д�ļ������������� ios::in ������д�ļ�
