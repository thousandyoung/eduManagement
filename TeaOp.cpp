#include"main.h"
#include<cstring>
#include<sstream>
string cou_name;       //课程名字
string tea_name;       //授课老师姓名
string position;       //授课地点
string time;          //授课时间
double propotion;		//平时成绩比例
string filename;
//登录老师账号
int TeaOp::Tea_Login(string number, string password) {
	string real_password = openAccount<Teacher>(number, Stu_number);
	if (real_password == "\0")return -1;		//用户不存在
	if (real_password == password)return 1;		//登录成功
	return 0;									//密码错误
}

//将老师所教课程读出来
vector<string>getTeaCourse(const Teacher& tea) {
	return split(tea.course, "&");
}

//将课程中所有信息读出来
vector<Course> TeaOp::Tea_ReadClassScore(string c_name) {
	filename = "Teacher/" + c_name + ".dat";
	char s[80];
	fstream f(filename, ios::in);
	f.getline(s,80);
	vector<Course>classStu;
	while ((long)f.tellg()!=ios::end)
	{
		Course temp;
		f.read((char*)&temp, sizeof(temp));
		classStu.push_back(temp);
	}
	return classStu;
}
//读出course文件第一行的课程信息
void TeaOp::getInfo(string filename) {
	char s[80];
	fstream f(filename, ios::in|ios::binary);
	f.getline(s, 80);
	stringstream ss(s);
	ss >> cou_name >> tea_name >> position >> time >> propotion;
}

//通过学号计算并修改学生的总评成绩
int TeaOp::InputScore(string number,double score1,double score2) {
	vector<Student>s;
	if (copyInfo(number, Stu_number, s)==0)return 0;
	Course temp(s[0].name, s[0].number, to_string(score1), to_string(score2), to_string(score1 * propotion + (1 - propotion) * score2));
	fstream f(filename, ios::binary | ios::out|ios::app);
	f.write((char*)&temp, sizeof(temp));//修改课程文件
	changeScore(s, score1 * propotion + (1 - propotion) * score2);
	return 1;
}

//修改学生的总评成绩
//修改成功（找到student）返回1否则返回0
int TeaOp::changeScore(vector<Student>s,double score) {
	if (s.empty())return 0;
	vector<string>s_course = getStuCourse(s[0]);
	int i;
	for (i = 0;i < s_course.size();i++) {
		int index = s_course[i].find_first_of("/", 0);
		string c_name = s_course[i].substr(0, index);
		if (c_name == cou_name) {
			s_course[i] = cou_name + "/" + to_string(score);
			break;//如果课已经存于学生中，直接修改
		}
	}
	if (i == s_course.size())s_course.push_back(cou_name + "/" + to_string(score));
	s[0].course = "";
	for (auto c : s_course)s[0].course += c;//修改学生对象里的course
	modifyInfo(s[0].number, Stu_number, s[0]);//修改学生文件
	return 1;
}
