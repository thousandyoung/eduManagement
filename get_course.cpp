
    void get_course(vector<string>& cou_name,vector<string>& position,vector<string>& time,vector<string>& tea_name,vector<string>& grade)
    {
        int i=0,flag=0,number=course.size();
        while(course[i]!='&'&&i<number-1)
        {
            flag=course.find('/',i);
            string temp=course.substr(i,flag-i);
            cou_name.push_back(temp),i=flag+1;

            flag=course.find('/',i);
            temp=course.substr(i,flag-i);
            position.push_back(temp),i=flag+1;

            flag=course.find('/',i);
            temp=course.substr(i,flag-i);
            time.push_back(temp),i=flag+1;

            flag=course.find('/',i);
            temp=course.substr(i,flag-i);
            tea_name.push_back(temp),i=flag+1;

            flag=course.find('&',i);
            temp=course.substr(i,flag-i);
            grade.push_back(temp),i=flag+1;
        }
    }
    }
};

