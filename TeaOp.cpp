#include"main.h"
#include<cstring>
#include<sstream>
struct cou_info {
	char cou_name[20];		//课程名字
	char class_name[20];	//教学班名
	char tea_name[20];		//授课老师姓名
	char position[20];		//授课地点
	char time[20];			//授课时间
	double propotion;		//平时成绩比例
}cur_course;
//登录老师账号
int TeaOp::Tea_Login(string number, string password) {
	string real_password = openAccount<Teacher>(number, Stu_number);
	if (real_password == "\0")return -1;		//用户不存在
	if (real_password == password)return 1;		//登录成功
	return 0;									//密码错误
}

//将老师所教课程读出来
vector<string>TeaOp::getTeaCourse(const Teacher& tea) {
	return split(tea.course, "&");
}

vector<pair<vector<Course>, string>>TeaOp::getAllStudent(const Teacher& tea) {
	vector<string>courses = getTeaCourse(tea);
	vector<pair<vector<Course>, string>> allCourse;
	for (auto course : courses) {
		getInfo(course);
		vector<Course>temp = Tea_ReadClassScore();
		pair<vector<Course>, string>it = make_pair(temp, cur_course.class_name);
		allCourse.push_back(it);
	}
	return allCourse;
}

//将课程中所有信息读出来
vector<Course> TeaOp::Tea_ReadClassScore() {
	string cur_filename = "course/" + string(cur_course.cou_name) + "/" + string(cur_course.class_name) + ".dat";
	fstream f(cur_filename, ios::in|ios::binary);
	f.read((char*)&cur_course, sizeof(cur_course));
	vector<Course>classStu;
	while ((long)f.tellg()!=ios::end)
	{
		Course temp;
		f.read((char*)&temp, sizeof(temp));
		classStu.push_back(temp);
	}
	f.close();
	return classStu;
}
//计算平均分
double TeaOp::getAverageScore(const vector<Course>&t) {
	double all_score = 0;
	for (auto i : t){
		string temp = i.final_grade;
		all_score += atof(temp.c_str());
	}
	return all_score / t.size();
}
//读出course文件第一行的课程信息
void TeaOp::getInfo(string c_name) {
	string filename = "course/" + c_name + ".dat";
	fstream f(filename, ios::in|ios::binary);
	f.read((char*)&cur_course, sizeof(cur_course));
	f.close();
}
//设置当前课程成绩计算比例
void TeaOp::Tea_SetPropotion(double proportion) {
	cur_course.propotion = proportion;
	string cur_filename = "course/" + string(cur_course.cou_name) + "/" + string(cur_course.class_name) + ".dat";
	fstream f(cur_filename, ios::out | ios::binary);
	f.write((char*)&cur_course, sizeof(cur_course));
	f.close();
}
//通过学号计算并修改学生的成绩
int TeaOp::InputScore(string number,double score1,double score2) {
	vector<Student>s;
	if (copyInfo(number, Stu_number, s)==0)return 0;
	string cur_filename = "course/" + string(cur_course.cou_name) + "/" + string(cur_course.class_name) + ".dat";
	Course temp(s[0].name, s[0].number, to_string(score1).c_str(), to_string(score2).c_str(), to_string(score1 * cur_course.propotion + (1 - cur_course.propotion) * score2).c_str());
	fstream f(cur_filename, ios::binary | ios::out | ios::in);
	Course stu_temp;
	while (f.read((char*)&stu_temp,sizeof(stu_temp)))
	{
		if (stu_temp.stu_number == number.data()) {
			f.seekp(long(f.tellg()) - sizeof(stu_temp));
			f.write((char*)&temp, sizeof(temp));
		}
	}
	if(long(f.tellg())==ios::end)
		f.write((char*)&temp, sizeof(temp));//修改课程文件
	changeScore(s, score1 * cur_course.propotion + (1 - cur_course.propotion) * score2);
	f.close();
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
		if (c_name.data() == cur_course.cou_name) {
			s_course[i] = string(cur_course.cou_name) + "/" + to_string(score);
			break;//如果课已经存于学生中，直接修改
		}
	}
	if (i == s_course.size())s_course.push_back( string(cur_course.cou_name) + "/" + to_string(score));
	strcpy(s[0].course, "");
	for (auto c : s_course)Connect(s[0].course, (char*)c.data(), s[0].course);//修改学生对象里的course
	modifyInfo(s[0].number, Stu_number, s[0]);//修改学生文件
	return 1;
}
