#include"main.h"
int StuOp::Stu_Login(string name,string password) {
	string real_password = openAccount<Student>(name,Stu_name);
	if (real_password == "\0")return -1;		  //用户不存在
	if (real_password == password)return 1;		//登录成功
	return 0;									                //密码错误
}

vector<Student> StuOp:: Stu_ReadScore(string stu_number) {   //学生根据学号读成绩
    vector<Student> result;
    copyInfo(stu_number, Stu_name, result);
    return result;
}
