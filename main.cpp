#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<map>
#include"main.h"
using namespace std;

//-------------字符数组之间的常规操作-----------------

void Connect(char *x,char *y,char *z)   //把x+y链接赋值给z,假设z的大小足够容纳x+y
{
	int i=0;
	for(;x[i]!='\0';i++) z[i]=x[i];
	for(int j=0;y[j]!='\0';j++) z[i++]=y[j];
	z[i]='\0';
}

void Copy(const char *b, char *a)   //把b的值赋值给a
{
	int i=0;
    for(i=0;b[i]!='\0';i++) a[i]=b[i];
    a[i]='\0';
}

int Get_size(char *a)   //获取字符数组的实际字符数
{
	int i=0;
	for(;a[i]!='\0';i++){;}
	return i;
}

void Stitch(char* a,char *b)  //把a字符数组连接到b数组后,假设b数组长度足够的前提下
{
	int size=Get_size(b);
	int j=0;
	for(;a[j]!='\0';j++)
	{
		b[size++]=a[j];
	}
	b[size]='\0';
}

char* string_char(string a,char * b)  //把string b 转化为字符数组 a，在a数组长度足够前提下；char*转为string可以直接赋值
{
	int i=0;
	for(;i<a.length();i++) b[i]=a[i];
	b[i]='\0';
	return b;
}



string to_string(int x)
{
    vector<int> temp;
    string s;
    if(x==0) return "0";
    while(x)
    {
        temp.push_back(x%10);
        x=x/10;
    }
    for(int i=temp.size()-1;i>=0;i--)
    {
        s+=temp[i]+'0';
    }
    return s;
}

vector<string> split(const string& str, const string& pattern)		//pattern为分隔符
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}



vector<string> getStuCourse(const Student& s) {
	return split(s.course, "&");
}


//索引对象
//学生学号的索引、学生姓名的索引、老师工号的索引、教务员工号的索引
multimap<string, string>Stu_number;
multimap<string, string>Stu_name;
multimap<string, string>Tea;
multimap<string, string>Ad;




void Student::transCourse( Course& x, char* cou_name, char* class_name)
{
	Stitch(cou_name,this->course),Stitch("/",this->course),Stitch(class_name,this->course),Stitch("/",this->course);
	Stitch(x.overall_grade,this->course),Stitch("&",this->course);
}


/*----功能函数-----*/
//读取文件里索引信息
//传入文件名和存储索引的multimap的对象
//已经调试
void openFind(string file_name, multimap<string, string>& x)   
{
	fstream f(file_name, ios::binary | ios::in);
	f.seekg(0, ios::end);
	long pos = f.tellg();    //得到文件最后的指针位置
	Find temp;
	for (f.seekg(0, ios::beg);pos != f.tellg() ;)
	{
		f.read((char*)&temp, sizeof(temp));
		//需要把char[]转化为string存入容器
		string key=temp.key,value=temp.value;
		x.insert(make_pair(key, value));     //将索引信息读入容器
	}
	f.close();
}

//获取特定对象的信息
//需要传入作为索引的学号或者姓名
//当对应的对象不存在时，返回0，否则返回1
//已经调试
template<typename T>
int copyInfo(string info, multimap<string, string>& x, vector<T>& y)    //y为需要读取的信息;用vector保存原因是防止有多个对象  已经调试
{
	int num = x.count(info);
	if (num == 0) return 0;
	multimap<string, string>::iterator it = x.find(info);
	for (int i = 0;i < num;i++)
	{
		string posi = (*it).second;    //得到信息的偏移量,文件绝对地址&偏移量
		string a(posi, 0, posi.find('&')), b(posi, posi.find('&') + 1, posi.size() - posi.find('&') - 1);
		fstream f(a, ios::binary | ios::in);
		f.seekg(long(sizeof(T) * (atoi(b.c_str())-1)), ios::beg);      //偏移到对应位置
		T temp;
		f.read((char*)&temp, sizeof(T));      //读取信息
		y.push_back(temp);
		it++;
		f.close();
	}
	return 1;
}

//将修改后的信息写入文件
//需要传入对象的名字或者学号、索引对象、以及修改后的对象信息
//当对象不存在时，返回0；否则返回1；
//已经调试
template<typename T>
int modifyInfo(string info, multimap<string, string>& x, const T& y)     //已经调试
{
	if (x.count(info) == 0) return 0;
	multimap<string, string>::iterator it = x.find(info);
	string posi = (*it).second;    //得到信息的偏移量,文件绝对地址&偏移量
	string a(posi, 0, posi.find('&')), b(posi, posi.find('&') + 1, posi.size() - posi.find('&') - 1);
	fstream f(a, ios::binary | ios::out|ios::in);        //修改部分：增加ios::in
	f.seekp(long(sizeof(T) * (atoi(b.c_str())-1)), ios::beg);
	f.write((char*)&y, sizeof(T));
	f.close();
	return 1;
}

//删除对象的信息
//传入特定对象的名字或者学号、索引对象、以及索引文件的名字
//例子：删除一个学生的信息，并不修改学生数据存储的文件，而是只修改索引文件
//已经调试
void deleteInfo(string info, multimap<string, string>& x, string file_name)   
{
	fstream f(file_name, ios::binary | ios::trunc|ios::out);
	x.erase(info);
	multimap<string, string>::iterator it = x.begin();    //将修改后的索引信息重新写入文件
	for (;it != x.end();it++)
	{
		//将string转为char[]存入
		char a[20],b[40];
		string_char((*it).first,a), string_char((*it).second,b);
		Find temp(a,b);
		f.write((char*)&temp, sizeof(temp));
	}
	f.close();         //索引信息在文件中删除完毕
}


//增加学生信息
//该函数只修改对应的数据文件，并未修改索引文件
//传入对象信息、数据文件的名字，返回该信息偏移量（例如该信息前面已经有17个信息，则返回18）
//已经调试
template<typename T>
int addInfo(const T& info, string file_name)  
{
	fstream f(file_name,  ios::binary | ios::app);
	f.write((char*)&info, sizeof(T));
	int value = ((long)f.tellp() - ios::beg) / sizeof(T);
	f.close();


	return value;
}


//该函数是增加索引信息到索引文件，对应增加数据的addInfo()函数
//传入索引的key、value、索引对象以及索引文件位置
//已经调试
void addIndex(string key, string value, multimap<string, string>& x, string file_name)     //file_name为索引文件  已经调试
{
	x.insert(make_pair(key, value));
	char a[20],b[40];
	string_char(key,a),string_char(value,b);
	Find temp(a,b);
	fstream f(file_name, ios::binary | ios::app);
	f.write((char*)&temp, sizeof(temp));
	f.close();
}

//增加学生信息，封装了addInfo()以及addIndex()函数
//传入人员信息，对应的索引对象，数据信息文件名，索引信息文件名
//由于学生有以姓名为主导和以学号为主导的文件，所以需要两个索引文件
//file_name1是学生数据信息文件名，另外两个分别是学生索引信息的文件名
//已经调试
template<typename T>
void addPerson(const T& info, multimap<string, string> x2, multimap<string, string> x3, string file_name1, string file_name2, string file_name3) 
{
	int num = addInfo(info, file_name1);   //得到偏移量
	addIndex(info.name, file_name1 + "&" + to_string(num), x2, file_name2);
	addIndex(info.number, file_name1 + "&" + to_string(num), x3, file_name3);
}


// 增加教师、教务员信息，封装了addInfo()以及addIndex()函数
//传入人员信息，对应的索引对象，数据信息文件名，索引信息文件名
//由于教师与教务员只有工号索引文件，所以只有一个索引文件名
//file_name1是学生数据信息文件名，另外两个分别是学生索引信息的文件名
//已经调试
template<typename T>
void addPerson(const T& info, multimap<string, string> numberMap, string infoFile, string indexFile)    
{
    int num = addInfo(info, infoFile);   //得到偏移量
    addIndex(info.number, infoFile + "&" + to_string(num), numberMap, indexFile);
}


//前提：学生选课成功
//增加学生选课信息
//对学生类中course进行修改，在张萌五班中加入该学生
//传入学生个人信息，学号索引对象，课程名字，班级名字
// filename1 张萌五班
void addCourse(Student& info, multimap<string, string> x1, string cou_name, string class_name)
{
	 //打开文件
	Course temp;
        string fileName = cou_name + "/" + class_name ;
	Copy(info.name,temp.stu_name),Copy(info.number,temp.stu_number);
	Copy("None",temp.usual_grade),Copy("None",temp.final_grade),Copy("None",temp.overall_grade);
	char a[20],b[20];
	string_char(cou_name,a),string_char(class_name,b);
	info.transCourse(temp,a,b);  //修改学生课程信息
	modifyInfo(info.number, x1, info);  //修改到学生文件中
	int num = addInfo(temp, fileName); //修改课程文件信息

	
}

//判断账号是否存在，存在则返回密码，否则返回空字符串
//通过学号或者姓名找到学生信息表，读出账号密码信息
//传入提供用户登录的账号以及对应的索引multimap对象
template<typename T>
string openAccount(string ID,  multimap<string, string>& x) {
	int flag = x.count(ID);      //检查账户是否存在
	if (flag == 0) return "\0";     //账户不存在直接返回空字符串
	multimap<string, string>::iterator it = x.find(ID);
	string posi = (*it).second;    //得到信息的偏移量,文件绝对地址&偏移量
	string a(posi, 0, posi.find('&')), b(posi, posi.find('&') + 1, posi.size() - posi.find('&') - 1);
	fstream f(a, ios::binary | ios::in);
	f.seekg(long(sizeof(T) * atoi(b.c_str())), ios::beg);      //偏移到对应位置
	T temp;
	f.read((char*)&temp, sizeof(T));   //读取信息
	f.close();
	return temp.password;
}

//读取整个文件的数据信息
//传入对应文件的名字，以及存储信息的vector变量
//已经调试
template<typename T>
int copyAllInfo(string file_name, vector<T>& x)     
{
	fstream f(file_name, ios::binary | ios::in);
	f.seekg(0, ios::end);
	long End = f.tellg();    //获取末位置
	f.seekg(0, ios::beg);
	for (;End!=f.tellg();)
	{
		T temp;
		f.read((char*)&temp, sizeof(T));
		x.push_back(temp);
	}
	f.close();    //读取完全部信息
	return 1;
}


//--------------生成随机信息的函数------------



string class_name[10] = { "计科1班","计科2班","信安1班","信安2班","网工1班","网工2班","环院1班","环院2班","软件1班","软件1班" };
string grade_name[4] = { "2017级","2018级","2019级","2020级" };
string major_name[10] = { "计算机科学","计算机科学","信息安全","信息安全","网络工程","网络工程","环境安全","环境安全","软件专业","软件专业" };
string college_name[10] = { "计算机学院","计算机学院","计算机学院","计算机学院","计算机学院","计算机学院","环境学院","环境学院","软件学院","软件学院" };
string before_name[20] = { "赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "杨","余","卢","彭","万俟", "司马", "上官", "欧阳" };
string after_name[140] = { "伟", "刚", "勇", "毅", "俊", "峰", "强", "军", "平", "保", "东", "文", "辉", "力", "明", "永", "健", "世", "广", "志", "义", "兴", "良", "海", "山", "仁", "波", "宁", "贵", "福", "生", "龙", "元", "全", "国", "胜", "学", "祥", "才", "发", "武", "新", "利", "清", "飞", "彬","富", "顺", "信", "子", "杰", "涛", "昌", "成", "康", "星", "光", "天", "达", "安", "岩", "中", "茂", "进", "林", "有", "坚", "和", "彪", "博", "诚", "先", "敬", "震", "振", "壮", "会", "思", "群", "豪", "心", "邦", "承", "乐", "绍", "功", "松", "善", "厚", "庆", "磊", "民", "友", "裕", "河", "哲", "江", "超", "浩", "亮", "政", "谦", "亨", "奇", "固", "之", "轮", "翰", "朗", "伯", "宏", "言", "若", "鸣", "朋", "斌", "梁", "栋", "维", "启", "克", "伦", "翔", "旭", "鹏", "泽", "晨", "辰", "士", "以", "建", "家", "致", "树", "炎", "德", "行", "时", "泰", "盛" };
int index_class = -1;  //用到的班级数，最多只能生成10个班级文件
string before_num = "20003034";   //学号前面固定位，学号共12位，固定位8位
int index_num = -1;   //学号后4位，按顺序递增
string sex[] = { "男", "女"};
string tea_number = "20001233"; //老师、教务员工号固定是12为
int index_num_tea = -1;

string file_student = "D:\\dataWork\\Class\\";  //存储学生信息文件路径
string file_course = "D:\\dataWork\\Course\\";  //存储课程信息文件路径
string file_teacher = "D:\\dataWork\\teacher";  //存储教师信息文件路径
string file_admini = "D:\\dataWork\\admini";    //存储教务员信息文件路径
string file_index = "D:\\dataWork\\index\\";       //存储索引文件路径




string course_name[] = { "数据结构","数据结构","马克思实践","马克思实践","大学英语","大学英语" };
string course_class[] = { "张威1班","张威2班","王萌1班","王萌2班","李雷1班","李雷2班" };




string getRandomNum(int& index_num)  //获取学号
{
	index_num++;
	string temp;
	if (index_num < 10)
	{
		temp = before_num + "000" + to_string(index_num);
	}
	else if (index_num < 100)
	{
		temp = before_num + "00" + to_string(index_num);
	}
	else if (index_num < 1000)
	{
		temp = before_num + "0" + to_string(index_num);
	}
	else
	{
		temp = before_num + to_string(index_num);
	}
	return temp;
}

string getRandomSex()  //获得随机性别
{
	int x = rand() % 2;
	return sex[x];
}

string getRandomName()  //获得随机姓名
{
	int x = rand() % 20;
	int y = rand() % 140;
	string temp = before_name[x] + after_name[y];
	return temp;
}


//随机生成一个班的学生信息，可以调用多次
//已经调试
void addRandomClass()  
{
	int student_num = rand() % 70;
	if (student_num < 20) student_num += 20;  //班级最少20人
	int xx = rand() % 4;  //随机获得年级信息
	string temp_grade = grade_name[xx];
	index_class++;  //按顺序创建班级
	for (int i = 0;i < student_num;i++)
	{
		Student x;
		char a[40];
		x.set_number(string_char(getRandomNum(index_num),a));
		x.set_name(string_char(getRandomName(),a));
		x.set_grade(string_char(temp_grade,a));
		x.set_college(string_char(college_name[index_class],a));
		x.set_major(string_char(major_name[index_class],a));
		x.set_class(string_char(class_name[index_class],a));
		x.set_pass("123456");  //设置初始密码
		x.set_course("\0");

		//随机生成课程信息
		//这里先设定每个学生只选一门课
		int flag = rand() % 6;

		Course temp;
		string fileName = file_course + course_name[flag] + "//" + course_class[flag] ;
		Copy(x.name,temp.stu_name),Copy(x.number,temp.stu_number),Copy("None",temp.usual_grade);
		Copy("None",temp.final_grade),Copy("None",temp.overall_grade);

		char b[50];
		x.transCourse(temp, string_char(course_name[flag],a), string_char(course_class[flag],b));   //修改学生课程信息
		addInfo(temp, fileName); //修改课程文件信息
		//将学生信息添加进文件
		addPerson(x, Stu_name, Stu_number, file_student + class_name[index_class], file_index + "Stu_name", file_index + "Stu_number");  //修改部分：使用file_index1而非file_index
	}
}

//生成几个教师和一个教务员的信息
//只能调用一次
//已经调试
void addRandomTeacher()
{
	char a[100],b[100],c[100];
	Teacher x1,x2,x3;
	x1.set_course("数据结构/张威1班&数据结构/张威2班&"),x1.set_name("张威"),x1.set_number(string_char(getRandomNum(index_num_tea),a)),x1.set_pass("123456");
	x2.set_course("马克思实践/王萌1班&马克思实践课/王萌2班&"),x2.set_name("王萌"),x2.set_number(string_char(getRandomNum(index_num_tea),b)),x2.set_pass("123456");
	x3.set_course("大学英语/李雷1班&大学英语/李雷2班&"),x3.set_name("李雷"),x3.set_number(string_char(getRandomNum(index_num_tea),c)),x3.set_pass("123456");

	Admini y1;
	string_char(getRandomNum(index_num_tea),y1.number), Copy("123456",y1.password), Copy( "韩梅梅",y1.name);

	addPerson(y1, Ad, file_admini, file_index + "Admini_index");  //增加教务员信息
	addPerson(x1, Tea, file_teacher , file_index + "Teacher_index");  //增加教师信息
	addPerson(x2, Tea, file_teacher , file_index + "Teacher_index");  //增加教师信息
	addPerson(x3, Tea, file_teacher , file_index + "Teacher_index");  //增加教师信息

	//增加几个课程的文件
	cou_info a1, a2, a3, a4, a5, a6;
	Copy("数据结构",a1.cou_name), Copy("张威1班",a1.class_name), Copy("张威",a1.tea_name ), Copy("A3 306",a1.position ),Copy( "周一第一第二节",a1.time ), a1.propotion = 0.4;
	Copy("数据结构",a2.cou_name ), Copy("张威2班",a2.class_name), Copy("张威",a2.tea_name  ), Copy("A3 306",a2.position ), Copy("周二第一第二节",a2.time ), a2.propotion = 0.4;
	Copy("马克思实践",a3.cou_name ), Copy("王萌1班",a3.class_name ), Copy("王萌",a3.tea_name), Copy("A2 206",a3.position ),Copy("周一第六第七节",a3.time ), a3.propotion = 0.5;
	Copy("马克思实践",a4.cou_name ), Copy("王萌2班",a4.class_name), Copy("王萌",a4.tea_name), Copy("A2 306",a4.position ),Copy("周二第一第二节",a4.time ), a4.propotion = 0.5;
	Copy("大学英语",a5.cou_name), Copy("李雷1班",a5.class_name ), Copy("李雷",a5.tea_name), Copy("A4 306",a5.position ), Copy("周三第一第二节",a5.time), a5.propotion = 0.3;
	Copy("大学英语",a6.cou_name), Copy("李雷2班",a6.class_name), Copy("李雷",a6.tea_name), Copy("A4 306",a6.position ), Copy("周四第一第二节",a6.time ), a6.propotion = 0.3;
	fstream f1(file_course + "数据结构//张威1班", ios::out | ios::binary); f1.write((char*)&a1, sizeof(a1)); f1.close();
	fstream f2(file_course + "数据结构//张威2班", ios::out | ios::binary); f2.write((char*)&a2, sizeof(a2)); f2.close();
	fstream f3(file_course + "马克思实践//王萌1班", ios::out | ios::binary); f3.write((char*)&a3, sizeof(a3)); f3.close();
	fstream f4(file_course + "马克思实践//王萌2班",ios::out | ios::binary); f4.write((char*)&a4, sizeof(a4)); f4.close();
	fstream f5(file_course + "大学英语//李雷1班", ios::out | ios::binary); f5.write((char*)&a5, sizeof(a5)); f5.close();
	fstream f6(file_course + "大学英语//李雷2班",ios::out | ios::binary); f6.write((char*)&a6, sizeof(a6)); f6.close();
}

//注：记得给每个写文件操作函数加上 ios::in 否则重写文件

int main() {
	addRandomTeacher();
	addRandomClass();
	addRandomClass();
}


