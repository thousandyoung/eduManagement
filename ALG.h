#ifndef ALG_H
#define ALG_H

#include <iostream>
#include <vector>
#include "teacher.h"
#include "stucourse.h"
#include "student.h"

using namespace std;

class ALG
{
private:
    static StuCourse helper1(string str);
    static CourClass helper2(string str);
    static string doubleTostring(double a);
public:
    static vector<string> firstname;
    static vector<string> lastname;
    static vector<string> coursename;
    static vector<int> IndDig;
    static vector<char> IndDigChar;
    static vector<string> classname;
    static int stucurnum;
    static int teacurnum;
    static int coucurnum;

    ALG();

    static string CreateRanName(int seed);
    static string CreateXXXX(int n);
    static string CreateOnlyId(int n,int type,string forwardcode);
    static void CreateRanTeacher(int n,string InfPath,string NameToIndexPath,string IdToIndexPath);
    static string CreateRandTeaCour(int n);
    static vector<StuCourse> DecodeGrade(const char* a);
    static vector<CourClass> DecodeCourClass(const char* a);
    static void CreateRanStudent(int n,string InfPath,string IdToIndexPath,string NameToIndexPath);
    static double CreateRandDoubleBetween(double a,double b);
    static string CreateRanCourGrade(int n);
    static pathAndexpo DecodePathAndExpo(const char* a);


};




#endif // ALG_H
