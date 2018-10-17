#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"stu.h"
#include"cour.h"

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
void ms_log_cour(char *k1, int k2);

void ms_log_cour(char *k1, int k2)
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
	fprintf(fp, "课程  课程编号:%d\n", k2);
	fclose(fp);
}

struct course *initcourse(int newid, char newname[], 
		char newnature[], int newhours, double newcredit, 
		int newnumber, int newlimit)
{
	struct course *new = (struct course *)malloc(sizeof(struct course));
	new->id = newid;
	strcpy(new->name, newname);
	strcpy(new->nature, newnature);
	new->hours = newhours;
	new->credit = newcredit;
	new->number = newnumber;
	new->limit = newlimit;
	new->next = NULL;
	ms_log_cour("新建", new->id);
	return new;
}
int output_cour(struct course *t)
{
	if(t == NULL)
	{
		printf("NULL.\n");
		return 0;
	}
	printf("编号:%03d\t课程名称:%s\t课程性质:%s\t授课学时:%d\n",t->id, t->name, t->nature, t->hours);
	printf("学分:%.1f\t课程已选人数:%d\t课程上限人数:%d\n",t->credit, t->number, t->limit);
	return 1;
}
void output_cour_detailed(struct course *t, struct student *headstu)
{
	int i;
	struct student *p = headstu->next;
	if(t == NULL)
	{
		printf("NULL.\n");
		return;
	}
	output_cour(t);
	printf("选课学生:\n");
	while(p != NULL)
	{
		for(i=0; i<p->courcount; i++)
		{
			if(p->cour[i] == t->id)
			{
				printf("%03d %s\n", p->id, p->name);
				break;
			}
		}
		p = p->next;
	}
}
void search_cour(struct course *headcour, struct student *headstu)
{
	int courid, flg = 0;
	char courname[NAMESIZE];
	struct student *pstu = headstu->next;
	struct course *pcour = headcour->next;
	printf("1.按课程编号查找\t2.按课程名查找\n输入选项:");
	scanf("%d", &flg);
	while(flg != 1 && flg != 2)
	{
		printf("输入错误，请重新输入:");
		scanf("%d", &flg);
	}
	if(flg == 1)
	{
		printf("输入课程编号:");
		scanf("%d", &courid);
		while(pcour != NULL)
		{
			if(pcour->id == courid)
			{
				output_cour_detailed(pcour, headstu);
				printf("查找结束。\n");
				return;
			}
			pcour = pcour->next;
		}
	}
	else
	{
		printf("输入课程名:");
		scanf("%s", courname);
		while(pcour != NULL )
		{
			if(strcmp(pcour->name, courname) == 0)
			{
				output_cour_detailed(pcour, headstu);
				printf("查找结束。\n");
				return;
			}
			pcour = pcour->next;
		}
	}
	printf("无记录。\n");
	return;
}
void changecour(struct course *h, struct student *hstu)
{
	int courid, newid, flg = 0;
	char courname[NAMESIZE];
	struct course *pcour = h->next, *t = NULL;
	struct student *stu = hstu->next;
	printf("1.按课程编号修改\t\t2.按课程名修改\n输入选项:");
	scanf("%d", &flg);
	while(flg != 1 && flg != 2)
	{
		printf("输入错误，请重新输入:");
		scanf("%d", &flg);
	}
	if(flg == 1)
	{
		printf("输入课程编号:");
		scanf("%d", &courid);
		while(pcour != NULL)
		{
			if(pcour->id == courid)
			{
				t = pcour;
				break;
			}
			pcour = pcour->next;
		}
		if(pcour == NULL)
		{
			printf("未找到该课程。\n");
			return;
		}
	}
	else
	{
		printf("输入课程名:");
		scanf("%s", courname);
		while(pcour != NULL )
		{
			if(strcmp(pcour->name, courname) == 0)
			{
				t = pcour;
				break;
			}
			pcour = pcour->next;
		}
		if(pcour == NULL)
		{
			printf("未找到该课程。\n");
			return;
		}
	}
	printf("当前课程信息:\n");
	output_cour_detailed(t, hstu);
	output_changecour();
	scanf("%d", &flg);
	while(flg != 8)
	{
		switch(flg)
		{
			case 1 : changecour_id(h, t, hstu);break;
			case 2 : changecour_name(t);break;
			case 3 : changecour_nature(t);break;
			case 4 : changecour_hours(t);break;
			case 5 : changecour_credit(t, hstu);break;
			case 6 : changecour_stu(t, hstu);break;
			case 7 : changecour_limit(t); break;
			default :
				printf("输入错误。\n");
				break;
		}
		output_changecour();
		scanf("%d", &flg);
	}
	printf("修改完成。\n");
	output_cour_detailed(t, hstu);
	ms_log_cour("修改",t->id);
	return;
}
void changecour_id(struct course *hcour, struct course *t, struct student *hstu)
{
	int i, newid, flg = 0;
	struct student *stu = hstu->next;
	struct course *p = hcour->next;
	printf("输入新的课程编号:");
	scanf("%d", &newid);
	if(newid == t->id)
	{
		return;
	}
	while(flg == 0)
	{
		p = hcour->next;
		flg = 1;
		while(p != NULL)
		{
			if(newid == p->id)
			{
				output_cour(p);
				printf("该编号已存在,请重新输入:\n");
				scanf("%d", &newid);
				flg = 0;
				break;
			}
			p = p->next;
		}
	}
	while(stu != NULL)
	{
		for(i=0; i<stu->courcount; i++)
		{
			if(stu->cour[i] == t->id)
			{
				stu->cour[i] = newid;
				break;
			}
		}
		stu = stu->next;
	}
	t->id = newid;
	printf("修改完成。\n");
}
void changecour_name(struct course *t)
{
	printf("输入新的课程名:");
	scanf("%s", t->name);
	return;
}
void changecour_nature(struct course *t)
{
	printf("输入新的课程性质:");
	scanf("%s", t->nature);
	return;
}
void changecour_hours(struct course *t)
{
	printf("输入新的学时:");
	scanf("%d", &t->hours);
	return;
}
void changecour_limit(struct course *t)
{
	printf("输入新的课程人数上限:");
	scanf("%d", &t->limit);
	return;
}
void changecour_credit(struct course *t, struct student *hstu)
{
	int i;
	double newcredit;
	struct student *stu = hstu->next;
	printf("输入新的学分:");
	scanf("%lf", &newcredit);
	while(stu != NULL)
	{
		for(i=0; i<stu->courcount; i++)
		{
			if(stu->cour[i] == t->id)
			{
				stu->credit -= t->credit;
				stu->credit += newcredit;
				break;
			}
		}
		stu = stu->next;
	}
	t->credit = newcredit;
}
void output_changecour_stu()
{
	printf("*******选课菜单*******\n");
	printf("1.添加选课\t2.取消选课\n");
	printf("3.退出\n");
	printf("---------------------------\n输入选项:");
}
void changecour_stu(struct course *t, struct student *hstu)
{
	int flg, stu_id, i, j;
	struct student *stu;
	output_changecour_stu();
	scanf("%d", &flg);
	while(flg != 3)
	{
		switch (flg)
		{
			case 1 :
				if(t->number >= t->limit)
				{
					printf("已达人数上限。\n");
					return;
				}
				printf("输入学号:");
				scanf("%d", &stu_id);
				stu = search_id(hstu, stu_id);
				if(t == NULL)
				{
					printf("学号不存在。\n");
					return;
				}
				printf("学号:%d   姓名:%s\n", stu_id, stu->name);
				for(i=0 ;i<stu->courcount; i++)
				{
					if(stu->cour[i] == t->id)
					{
						return;
					}
				}
				stu->courcount++;
				stu->cour[stu->courcount-1] = t->id;
				stu->credit += t->credit;
				t->number ++;
				printf("添加成功。\n");
				break;
			case 2 :
				printf("输入学号:");
				scanf("%d", &stu_id);
				stu = search_id(hstu, stu_id);
				if(t == NULL)
				{
					printf("学号不存在。\n");
					return;
				}
				printf("学号:%d   姓名:%s\n", stu_id, stu->name);
				for(i=0; i<stu->courcount; i++)
				{
					if(stu->cour[i] == t->id)
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
				stu->credit -= t->credit;
				t->number --;
				printf("操作成功。\n");
				break;
			default : 
				printf("输入错误。\n");
				break;
		}
		output_changecour_stu();
		scanf("%d", &flg);
	}
	return;
}
void output_changecour()
{
	printf("*********修改课程信息菜单*********\n");
	printf("1.修改课程编号       2.修改课程名\n");
	printf("3.修改课程性质       4.修改学时\n");
	printf("5.修改学分           6.修改选课学生\n");
	printf("7.修改课程人数上限   8.退出修改\n");
	printf("----------------------------\n");
	printf("输入选项:");
}
void dele_cour_core(struct student *hstu, struct course *h, struct course *t)
{
	char key;
	int i, j;
	struct course *pr = h;
	struct student *stu = hstu->next;
	output_cour(t);
	printf("确认删除?(y/n)");
	getchar();
	scanf("%c", &key);
	while(key != 'y' && key != 'n')
	{
		printf("输入错误,请重新输入:");
	}
	if(key == 'y')
	{
		while(stu != NULL)
		{
			for(i=0; i<stu->courcount; i++)
			{
				if(stu->cour[i] == t->id)
				{
					for(j=i+1; j<stu->courcount; j++)
					{
						stu->cour[j-1] = stu->cour[j];
					}
					stu->courcount--; 
					stu->credit -= t->credit;
					continue;
				}
			}
			stu = stu->next;
		}
		while(pr->next != NULL && pr->next != t)
		{
			pr = pr->next;
		}
		if(pr->next == t)
		{
			pr->next = t->next;
			ms_log_cour("删除", t->id);
			free(t);
			printf("删除成功。\n");
		}
		else
		{
			printf("出错了QAQ，找不到数据。");
		}
		return;
	}
	printf("取消删除。\n");
	return;
}
void dele_cour(struct student *hstu, struct course *h)
{
	int flg, courid;
	char key, courname[NAMESIZE];
	struct course *pcour = h->next;

	printf("1.按课程编号删除\t\t2.按课程名删除\n输入选项:");
	scanf("%d", &flg);
	while(flg != 1 && flg != 2)
	{
		printf("输入错误，请重新输入:");
		scanf("%d", &flg);
	}
	if(flg == 1)
	{
		printf("输入课程编号:");
		scanf("%d", &courid);
		while(pcour != NULL)
		{
			if(pcour->id == courid)
			{
				dele_cour_core(hstu, h, pcour);
				return;
			}
			pcour = pcour->next;
		}
	}
	else
	{
		printf("输入课程名:");
		scanf("%s", courname);
		while(pcour != NULL )
		{
			if(strcmp(pcour->name, courname) == 0)
			{
				dele_cour_core(hstu, h, pcour);
				return;
			}
			pcour = pcour->next;
		}
	}
	printf("无记录。\n");
	return;
}
int addcour(struct course *h)
{
	struct course *p = h;
	int flg = 0, newid = 0,  newlimit, newhours;
	double newcredit;
	char newname[NAMESIZE], newnature[NAMESIZE];
	printf("输入课程编号(输入-1结束添加):");
	scanf("%d", &newid);
	if(newid == -1)
	{
		printf("结束添加。\n");
		return 0;
	}
	while(flg == 0)
	{
		p = h->next;
		flg = 1;
		while(p != NULL)
		{
			if(newid == p->id)
			{
				output_cour(p);
				printf("该编号已存在,请重新输入:\n");
				scanf("%d", &newid);
				flg = 0;
				break;
			}
			p = p->next;
		}
	}
	printf("课程名称:");
	scanf("%s", newname);
	printf("课程性质:");
	scanf("%s", newnature);
	printf("课时:");
	scanf("%d", &newhours);
	printf("学分:");
	scanf("%lf", &newcredit);
	printf("课程人数上限:");
	scanf("%d", &newlimit);
	p = h;
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = initcourse(newid, newname, newnature, newhours, 
			newcredit, 0, newlimit);
	output_cour(p->next);
	printf("创建成功。\n");
	return 1;
}
void creatcourses_keyboard(struct course *h)
{
	int flg = 1;
	while(flg != 0)
	{
		flg = addcour(h);
	}
	return;
}
void creatcourses_file(struct course *h)
{
	int i, newid;
	struct course *p = NULL, *pr = h;
	FILE *fp = fopen("cour.txt", "r");
	if(fp == NULL)
	{
		printf("打开文件错误。\n");
		return;
	}
	while(fscanf(fp, "%d", &newid) != EOF)
	{
		p = (struct course *)malloc(sizeof(struct course));
		pr->next = p;
		p->id = newid;
		fscanf(fp, "%s", p->name);
		fscanf(fp, "%s", p->nature);
		fscanf(fp, "%d%lf%d%d", &p->hours, &p->credit, &p->number, &p->limit);
		p->next = NULL;
		pr = p;
	}
	printf("读取文件完成。\n");
}
void savefile_cour(struct course *h)
{
	int i;
	FILE *fp = fopen("cour.txt", "w+");
	struct course *p = h->next;
	if(fp == NULL)
	{
		printf("保存文件失败。\n");
		return;
	}
	while(p != NULL)
	{
		fprintf(fp, "%d %s %s %d %.1f %d %d\n", p->id, p->name, p->nature, p->hours,
				p->credit, p->number, p->limit);
		fflush(fp);
		p = p->next;
	}
	fclose(fp);
	printf("已保存\n");
}
void credit_calulate_single(struct course *headcour, struct student *t)
{
	int i;
	struct course *p = headcour->next;
	double credit = 0;
	for(i=0; i<t->courcount; i++)
	{
		p = headcour->next;
		while(p != NULL)
		{
			if(p->id == t->cour[i])
			{
				credit += p->credit;
			}
			p = p->next;
		}
	}
	t->credit = credit;
	return;
}
void credit_caulate_all(struct course *headcour, struct student *headstu)
{
	struct student *p = headstu->next;
	while(p)
	{
		credit_calulate_single(headcour, p);
		p = p->next;
	}
}
void number_caulate(struct course *headcour, struct student *headstu)
{
	int count, i;
	struct student *pstu = headstu->next;
	struct course *pcour = headcour->next;
	while(pcour)
	{
		count = 0;
		pstu = headstu->next;
		while(pstu != NULL)
		{
			for(i=0; i<pstu->courcount; i++)
			{
				if(pstu->cour[i] == pcour->id)
				{
					count++;
					break;
				}
			}
			pstu = pstu->next;
		}
		pcour->number = count;
		pcour = pcour->next;
	}
}
void output_courses(struct course *h)
{
	struct course *p = h->next;
	while(p != NULL)
	{
		output_cour(p);
		printf("\n");
		p = p->next;
	}
}

struct course *searchcour_id(struct course *headcour, int courid)
{
	struct course *pcour = headcour->next;
	while(pcour != NULL)
	{
		if(pcour->id == courid)
		{
			return pcour;
		}
		pcour = pcour->next;
	}
	return NULL;
}
