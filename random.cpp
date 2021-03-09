#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<map>
#include<vector>
using namespace std;

//课程的数目和老师、教务员的数量、班级数量上限暂时是确定的
//先调用addRandomTeacher()生成几个老师、教务员、课程文件等信息
//然后最多调用10次addRandomClass()生成10个班级信息
//文件储存路径写在file_class,file_index中
//还未调试



string class_name[10]={"计科1班","计科2班","信安1班","信安2班","网工1班","网工2班","环院1班","环院2班","软件1班","软件1班"};
string grade_name[4]={"2017级","2018级","2019级","2020级"};
string major_name[10]={"计算机科学与技术","计算机科学与技术","信息安全","信息安全","网络工程","网络工程","环境安全","环境安全","软件专业","软件专业"}
string college_name[10]={"计算机科学与工程学院","计算机科学与工程学院","计算机科学与工程学院","计算机科学与工程学院","计算机科学与工程学院","计算机科学与工程学院","环境科学与工程学院","环境科学与工程学院","软件学院","软件学院"};
string before_name[20]={"赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "杨","余","卢","彭","万俟", "司马", "上官", "欧阳"};
string after_name[140]={"伟", "刚", "勇", "毅", "俊", "峰", "强", "军", "平", "保", "东", "文", "辉", "力", "明", "永", "健", "世", "广", "志", "义", "兴", "良", "海", "山", "仁", "波", "宁", "贵", "福", "生", "龙", "元", "全", "国", "胜", "学", "祥", "才", "发", "武", "新", "利", "清", "飞", "彬","富", "顺", "信", "子", "杰", "涛", "昌", "成", "康", "星", "光", "天", "达", "安", "岩", "中", "茂", "进", "林", "有", "坚", "和", "彪", "博", "诚", "先", "敬", "震", "振", "壮", "会", "思", "群", "豪", "心", "邦", "承", "乐", "绍", "功", "松", "善", "厚", "庆", "磊", "民", "友", "裕", "河", "哲", "江", "超", "浩", "亮", "政", "谦", "亨", "奇", "固", "之", "轮", "翰", "朗", "伯", "宏", "言", "若", "鸣", "朋", "斌", "梁", "栋", "维", "启", "克", "伦", "翔", "旭", "鹏", "泽", "晨", "辰", "士", "以", "建", "家", "致", "树", "炎", "德", "行", "时", "泰", "盛"};
int index_class=-1;  //用到的班级数，最多只能生成10个班级文件
string before_num="20003034";   //学号前面固定位，学号共12位，固定位8位
ine index_num=-1;   //学号后4位，按顺序递增
string sex[2]=["男","女"];
string tea_number="20001233"; //老师、教务员工号固定是12为
int index_num_tea=-1;

string file_student="D:\\dataWork\\Class\\";  //存储学生信息文件路径
string file_course="D:\\dataWork\\Course\\";  //存储课程信息文件路径
string file_teacher="D:\\dataWork\\teacher.dat";  //存储教师信息文件路径
string file_admini="D:\\dataWork\\admini.dat";    //存储教务员信息文件路径
string file_index="D:\\dataWork\\index\\";       //存储索引文件路径

string course_name={"数据结构","数据结构","马克思实践","马克思实践","大学英语","大学英语"};
string course_class={"张威1班","张威2班","王萌1班","王萌2班","李雷1班","李雷2班"};

string getRandomNum(int & index_num)  //获取学号
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

string getRandomSex()  //获得随机性别
{
    int x=rand()%2;
    return sex[x];
}

string getRandomName()  //获得随机姓名
{
    int x=rand()%20;
    int y=rand()%140;
    string temp=before_name[x]+after_name[y];
    return temp;
}

string addRandomClass()  //随机生成班级信息
{
    int student_num=rand()%70;
    if(student_num<20) student+=20;  //班级最少20人
    int xx=rand()%4;  //随机获得年级信息
    string temp_grade=grade_name[xx];
    index_class++;  //按顺序创建班级
    for(int i=0;i<student_num;i++)
    {
        Student x;
        x.set_number(getRandomNum(index_num));
        x.set_name(getRandomName());
        x.set_grade(temp_grade);
        x.set_college(college_name[index_class]);
        x.set_major(major_name[index_class]);
        x.set_class(class_name[index_class]);
        x.set_pass("123456");  //设置初始密码
        x.set_course("\0");

        //随机生成课程信息
        //这里先设定每个学生只选一门课
        int flag=rand()%6;

        Course temp;
        string fileName = file_course+cou_name + "/" + class_name + ".dat";
        temp.stu_name = info.name; temp.stu_number = info.number;
        temp.usual_grade = "None"; temp.final_grade = "None"; temp.overall_grade = "None";
        x.transCourse(temp,course_name[flag],course_class[flag]);   //修改学生课程信息
        addInfo(temp, fileName); //修改课程文件信息

        //将学生信息添加进文件
        addPerson(x,Stu_name,Stu_number,file_student+class_name[index_class],file_index+"Stu_name.dat",file_index+"Stu_number.dat");
    }
}

//暂时只生成几个老师信息
string addRandomTeacher()
{
    Teacher x1(getRandomNum(index_num_tea),"123456","张威","数据结构/张威1班&数据结构/张威2班&");
    Teacher x2(getRandomNum(index_num_tea),"123456","王萌","马克思实践/王萌1班&马克思实践课/王萌2班&");
    Teacher x3(getRandomNum(index_num_tea),"123456","李雷","大学英语/李雷1班&大学英语/李雷2班&");

    Admini y1;
    y1.number=getRandomNum(index_num_tea),y1.password="123456",y1.name="韩梅梅";

    addPerson(y1,Ad,file_admini,file_index+"Admini_index.dat");  //增加教务员信息
    addPerson(x1,Tea,file_teacher+file_index+"Teacher_index.dat");  //增加教师信息
    addPerson(x2,Tea,file_teacher+file_index+"Teacher_index.dat");  //增加教师信息
    addPerson(x3,Tea,file_teacher+file_index+"Teacher_index.dat");  //增加教师信息

    //增加几个课程的文件
    cou_info a1,a2,a3,a4,a5,a6;
    a1.cou_name="数据结构",a1.class_name="张威1班",a1.tea_name="张威",a1.position="A3 306",a1.time="周一第一第二节",a1.propotion=0.4;
    a2.cou_name="数据结构",a2.class_name="张威2班",a2.tea_name="张威",a2.position="A3 306",a2.time="周二第一第二节",a2.propotion=0.4;
    a3.cou_name="马克思实践",a3.class_name="王萌1班",a3.tea_name="王萌",a3.position="A2 206",a3.time="周一第六第七节",a3.propotion=0.5;
    a4.cou_name="马克思实践",a4.class_name="王萌2班",a4.tea_name="王萌",a4.position="A2 306",a4.time="周二第一第二节",a4.propotion=0.5;
    a5.cou_name="大学英语",a5.class_name="李雷1班",a5.tea_name="李雷",a5.position="A4 306",a5.time="周三第一第二节",a5.propotion=0.3;
    a6.cou_name="大学英语",a6.class_name="李雷2班",a6.tea_name="李雷",a6.position="A4 306",a6.time="周四第一第二节",a6.propotion=0.3;
    fstream f(file_Course+"数据结构//张威1班.dat",ios::in|ios::out|ios::binary); f.write((char*)&a1,sizeof(a1)); f.close();
    fstream f(file_Course+"数据结构//张威2班.dat",ios::in|ios::out|ios::binary); f.write((char*)&a2,sizeof(a2)); f.close();
    fstream f(file_Course+"马克思实践//王萌1班.dat",ios::in|ios::out|ios::binary); f.write((char*)&a3,sizeof(a3)); f.close();
    fstream f(file_Course+"马克思实践//王萌2班.dat",ios::in|ios::out|ios::binary); f.write((char*)&a4,sizeof(a4)); f.close();
    fstream f(file_Course+"大学英语/李雷1班.dat",ios::in|ios::out|ios::binary); f.write((char*)&a5,sizeof(a5)); f.close();
    fstream f(file_Course+"大学英语//李雷2班.dat",ios::in|ios::out|ios::binary); f.write((char*)&a6,sizeof(a6)); f.close();
}

//注：记得给每个写文件操作函数加上 ios::in 否则重写文件
