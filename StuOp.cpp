#include"main.h"
int StuOp::Stu_Login(string name,string password) {
	string real_password = openAccount<Student>(name,x);
	if (real_password == "\0")return -1;		  //用户不存在
	if (real_password == password)return 1;		//登录成功
	return 0;									                //密码错误
}
