#ifndef __COUR_H__
#define __COUR_H__

#define NAMESIZE 20

struct course{
	int id;
	char name[NAMESIZE];
	char nature[NAMESIZE];
	int hours;
	double credit;
	int number;
	int limit;
	struct course *next;
};

struct course *initcourse(int newid, char newname[],char newnature[], int newhours, double newcredit, int newnumber, int newlimit);//创建课程
void search_cour(struct course *headcour, struct student *headstu);
int  output_cour(struct course *t);//打印课程简单信息
void output_courses(struct course *h);//打印所有课程信息
void output_cour_detailed(struct course *t, struct student *headstu);//打印课程详细信息
void credit_calulate_single(struct course *headcour, struct student *t);//计算一个学生的学分
void credit_caulate_all(struct course *headcour, struct student *headstu);//计算所有学生学分
void dele_cour(struct student *hstu, struct course *h);
void dele_cour_core(struct student *hstu, struct course *h, struct course *t);
int addcour(struct course *h);//添加课程
void changecour(struct course *h, struct student *hstu);
void changecour_id(struct course *hcour, struct course *t, struct student *hstu);
void changecour_name(struct course *t);
void changecour_nature(struct course *t);
void changecour_hours(struct course *t);
void changecour_credit(struct course *t, struct student *hstu);
void changecour_stu(struct course *t, struct student *hstu);
void changecour_limit(struct course *t);
void output_changecour_stu();
void output_changecour();
void creatcourses_keyboard(struct course *h);
void creatcourses_file(struct course *h);
void number_caulate(struct course *headcour, struct student *headstu);
void savefile_cour(struct course *h);
struct course *searchcour_id(struct course *headcour, int courid);

#endif
