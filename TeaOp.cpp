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
int TeaOp::Tea_Login(string name, string password) {
	string real_password = openAccount<Teacher>(name, Tea_number);
	if (real_password == "\0")return -1;		//用户不存在
	if (real_password == password)return 1;		//登录成功
	return 0;									//密码错误
}
//将课程中所有信息读出来
vector<Course> TeaOp::Tea_ReadClassScore(string filename) {
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
	fstream f(filename, ios::in);
	f.getline(s, 80);
	stringstream ss(s);
	ss >> cou_name >> tea_name >> position >> time >> propotion;
}
//计算学生的总评成绩
int TeaOp::InputScore(string name,double score1,double score2) {
	vector<Student>s;
	if (copyInfo(name, Stu, s))return 0;
	Course temp(s[0].name, s[0].number, to_string(score1), to_string(score2), to_string(score1 * propotion + (1 - propotion) * score2));
	fstream f(filename, ios::binary | ios::out|ios::app);
	f.write((char*)&temp, sizeof(temp));
}

int changeScore(vector<Student>s) {

}
