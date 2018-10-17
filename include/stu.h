#ifndef __STU_H__
#define __STU_H__

#define COURMAX 5 
struct student{
	int id;
	char name[20];
	int courcount;
	int cour[COURMAX];
	double credit;
	struct student *next;
};

struct student *initstu(int newid, char newname[], int newcourcount, int newcour[COURMAX]);//新建学生
int addstu(struct student *h);//增加学生
struct student *creatstudents_1();//学生信息初始化 临时
void creatstudents_keyboard(struct student *h);//学生信息初始化，键盘输入信息
void creatstudents_file(struct student *h);//学生信息初始化，文件输入信息
void output_stu(struct student *t);//给定指针，输出单个学生信息
void output_students(struct student *h);//输出所有学生信息
struct student *search_id(struct student *h, int id);//按学号搜索学生
void search_name(struct student *h, char name[]);//按姓名搜索学生
void changestu(struct student *h);//修改学生信息
void delestu(struct student *h);//删除学生信息
void output_menu_changestu();//打印修改学生信息菜单
void savefile_stu(struct student *h);//保存学生信息到文档
int addstu_later(struct student *h);
void searchstu(struct student *headstu);


#endif
