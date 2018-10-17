#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stu.h"
#include"cour.h"
#include<time.h>

void output_menu();//打印菜单
void output_menu_init();
void mode_manageinfor(struct student *headstu, struct course *headcour);
void mode_electivecourse(struct student *headstu, struct course *headcour);
void output_menu_electivecourse();
void output_choicemode();
void ms_log_cour(char *k1, int k2);

void ms_log_electivecourse(char *k1, int k2, int k3)
{
	FILE *fp = fopen("ms.log", "a+");
	time_t timep;
	struct tm *p;
	if(fp == 0)
	{
		printf("写入日志失败。\n");
		return;
	}
	fseek(fp, 0, SEEK_END);
	time (&timep);
	p=gmtime(&timep);
	fprintf(fp, "%d-%d-%d %d:%d:%d\t",1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 8+p->tm_hour, p->tm_min, p->tm_sec);
	fprintf(fp, "%s", k1);
	fprintf(fp, "选课  ");
	fprintf(fp, "学生编号:%d   课程编号:%d\n", k2, k3);
}
void output_menu()
{
	printf("**************** 菜单 ****************\n");
	printf("-------------学生信息管理-------------\n");
	printf("1.打印所有学生信息      2.新增学生信息\n");
	printf("3.修改学生信息          4.删除学生信息\n");
	printf("5.查询学生信息\n");
	printf("-------------课程管理模块-------------\n");
	printf("6.打印所有课程信息     7.新增课程\n");
	printf("8.选课、修改课程信息   9.删除课程\n");
	printf("10.查询课程信息\n");
	printf("--------------- 退 出 ---------------\n");
	printf("11.保存并退出\n");
	printf("12.取消保存,直接退出\n");
	printf("-------------------------------------\n");
	printf("输入选项:");
}
void output_menu_init()
{
	printf("*******初始化菜单*******\n");
	printf("1.键盘输入    2.文件输入\n");
	printf("输入选择:");
}
void output_choicemode()
{
	printf("************菜 单************\n");
	printf("1.选课系统 2.信息管理 3.退出\n");
	printf("-----------------------------\n输入选择:");
}
void output_menu_electivecourse()
{
	printf("***********选课菜单************\n");
	printf("1.添加选课        2.删除选课\n");
	printf("3.查看可选课程    4.查看个人选课\n");
	printf("5.退出\n");
	printf("-------------------------------\n输入选择:");
}

void mode_electivecourse(struct student *headstu, struct course *headcour)
{
	struct student *stu = NULL;
	struct course *cour = NULL;
	int flg, courid, stu_id, i;
	printf("输入学号:");
	scanf("%d", &stu_id);
	stu = search_id(headstu, stu_id);
	if(stu == NULL)
	{
		printf("学号不存在。\n");
		return;
	}
	printf("学号:%d   姓名:%s\n", stu_id, stu->name);

	output_menu_electivecourse();
	scanf("%d", &flg);
	while(flg != 5)
	{
		switch(flg)
		{
			case 1 : 
				printf("输入课程编号:");
				scanf("%d", &courid);
				cour = searchcour_id(headcour, courid);
				if(cour == NULL)
				{
					printf("没有这门课程。\n");
					break;
				}
				if(cour->number >= cour->limit)
				{
					printf("已达人数上限。\n");
					return;
				}
				if(stu->courcount >= COURMAX)
				{
					printf("已达选课上限。\n");
					break;
				}
				for(i=0; i<stu->courcount; i++)
				{
					if(stu->cour[i] == cour->id)
					{
						break;
					}
				}
				if(i < stu->courcount)
				{
					break;
				}
				stu->courcount++;
				stu->cour[stu->courcount-1] = cour->id;
				stu->credit += cour->credit;
				cour->number ++;
				printf("添加成功。\n");
				ms_log_electivecourse("添加", stu->id, cour->id);
				break;
			case 2 : 
				printf("输入课程编号:");
				scanf("%d", &courid);
				cour = searchcour_id(headcour, courid);
				if(cour == NULL)
				{
					printf("没有这门课程。\n");
					break;
				}
				for(i=0; i<stu->courcount; i++)
				{
					if(stu->cour[i] == cour->id)
						break;
				}
				if(i == stu->courcount)
				{
					printf("该学生未选此课程。\n");
					return;
				}
				for(; i<stu->courcount; i++)
				{
					stu->cour[i] = stu->cour[i+1];
				}
				stu->courcount --;
				stu->credit -= cour->credit;
				cour->number --;
				printf("操作成功。\n");
				ms_log_electivecourse("删除", stu->id, cour->id);
				break;
			case 3 : 
				output_courses(headcour);break;
			case 4 : 
				output_stu(stu); break;
			default : printf("没有这个选项，请重新输入。\n");
		}
		output_menu_electivecourse();
		scanf("%d", &flg);
	}
	savefile_stu(headstu);
	savefile_cour(headcour);
	return;
}
void mode_manageinfor(struct student *headstu, struct course *headcour)
{
	int flg = 0;
	output_menu();
	scanf("%d", &flg);
	while(flg != 11 && flg != 12)
	{
		switch(flg){
			case 1 : output_students(headstu);break;
			case 2 : addstu_later(headstu);break;
			case 3 : changestu(headstu);break;
			case 4 : delestu(headstu);break;
			case 5 : searchstu(headstu);break;
			case 6 : output_courses(headcour);break;
			case 7 : addcour(headcour);break;
			case 8 : changecour(headcour, headstu);break;
			case 9 : dele_cour(headstu, headcour);break;

			case 10 : search_cour(headcour, headstu);break;
			default : printf("没有这个选项，请重新输入。\n");
		}
		output_menu();
		scanf("%d", &flg);
	}
	if(flg == 11)
	{
		savefile_stu(headstu);
		savefile_cour(headcour);
	}
	return;
}

int main()
{
	int flg = 0, id;
	char name[20];
	struct student *headstu = (struct student *)malloc(sizeof(struct student));
	struct course *headcour = (struct course *)malloc(sizeof(struct course));

	output_menu_init();
	scanf("%d", &flg);
	while(flg != 1 && flg != 2)
	{
		printf("输入错误。请重新输入:");
		scanf("%d", &flg);
	}
	if(flg == 1)
	{
		creatcourses_keyboard(headcour);
		creatstudents_keyboard(headstu);
		number_caulate(headcour, headstu);
		credit_caulate_all(headcour, headstu);
	}
	else
	{
		creatstudents_file(headstu);
		creatcourses_file(headcour);
		number_caulate(headcour, headstu);
		credit_caulate_all(headcour, headstu);
	}
	printf("初始化完成。\n");

	output_choicemode();
	scanf("%d", &flg);
	while(flg != 3)
	{
		switch(flg)
		{
			case 1 : mode_electivecourse(headstu, headcour);break;
			case 2 : mode_manageinfor(headstu, headcour);break;
			default : printf("输入错误。\n");break;
		}
		output_choicemode();
		scanf("%d", &flg);
	}
	return 0;
}

