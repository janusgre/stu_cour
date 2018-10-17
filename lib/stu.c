#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"stu.h"

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
void output_menu_init_stu();  //打印初始化菜单
void output_menu_changestu();//打印修改学生信息菜单
void savefile_stu(struct student *h);//保存到文档
int addstu_later(struct student *h);
void searchstu(struct student *headstu);
void ms_log_stu(char *k1, int k2);

void ms_log_stu(char *k1, int k2)
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
	fprintf(fp, "学生");
	fprintf(fp, "  学生编号:");
	fprintf(fp, "%d\n", k2);
	fclose(fp);
}

struct student *initstu(int newid, char newname[], int newcourcount, int newcour[COURMAX])
{
	int i;
	struct student *new = (struct student *)malloc(sizeof(struct student));
	new->id = newid;
	strcpy(new->name, newname);
	new->courcount = newcourcount;
	for(i=0; i<newcourcount; i++)
	{
		new->cour[i] = newcour[i];
	}
	for(; i<COURMAX; i++)
	{
		new->cour[i] = 0;
	}
	new->next = NULL;
	ms_log_stu("新建", newid);
	return new;
}
struct student *search_id(struct student *h, int id)
{
	struct student *p = h->next;
	while(p != NULL)
	{
		if(p->id == id)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}
void search_name(struct student *h, char name[])
{
	int count = 0;
	struct student *p = h->next;
	while(p != NULL)
	{
		if(strcmp(name, p->name) == 0)
		{
			count ++;
			output_stu(p);
		}
		p = p->next;
	}
	if(count == 0)
	{
		printf("该学生不存在。\n");
	}
}
void searchstu(struct student *headstu)
{
	int flg = 0, id;
	char name[20];
	while(flg != 1 && flg != 2)
	{
		printf("*******查询学生信息*******\n");
		printf("1.按学号查询  2.按姓名查询\n输入选项:");
		scanf("%d", &flg);
	}
	if(flg == 1)
	{
		 printf("输入学号:");
		 scanf("%d", &id);
		 output_stu(search_id(headstu, id));
	}
	else
	{
		 printf("输入姓名:");
		 scanf("%s", name);
		 search_name(headstu, name);
	}
}
int addstu(struct student *h)
{
	struct student *p = h;
	int i, newid, newcourcount, newcour[COURMAX];
	char newname[20];
	printf("***新建学生档案***\n");
	printf("id(id为-1时结束添加。):");
	scanf("%d", &newid);
	if(newid == -1)
	{
		printf("结束添加。\n");
		return 0;
	}
	while(search_id(h, newid) != NULL)
	{
		printf("该学号已存在!");
		output_stu(search_id(h, newid));
		printf("请重新输入。\nid:");
		scanf("%d", &newid);
	}
	printf("name:");
	scanf("%s", newname);
	printf("所选课程数:");
	scanf("%d", &newcourcount);
	printf("输入课程编号:\n");
	for(i=0; i<newcourcount; i++)
	{
		printf("No%d:", i+1);
		scanf("%d", &newcour[i]);
	}
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = initstu(newid, newname, newcourcount, newcour);
	output_stu(p->next);
	printf("添加成功。\n");
	return newid;
}
int addstu_later(struct student *h)
{
	struct student *p = h;
	int i, newid, newcour[COURMAX] = {0};
	char newname[20];
	printf("***新建学生档案***\n");
	printf("id(id为-1时结束添加。):");
	scanf("%d", &newid);
	if(newid == -1)
	{
		printf("结束添加。\n");
		return 0;
	}
	while(search_id(h, newid) != NULL)
	{
		printf("该学号已存在!");
		output_stu(search_id(h, newid));
		printf("请重新输入。\nid:");
		scanf("%d", &newid);
	}
	printf("name:");
	scanf("%s", newname);
	while(p->next != NULL)
	{
		p = p->next;
	}
	p->next = initstu(newid, newname, 0, newcour);
	output_stu(p->next);
	printf("添加成功。\n");
	return newid;
}
void creatstudents_keyboard(struct student *h) //学生信息初始化，键盘输入信息
{
	while(1)
	{
		if(addstu(h) == 0)
		{
			break;
		}
	}
}
void creatstudents_file(struct student *h)//学生信息初始化，文件输入信息
{
	int i, newid;
	struct student *p = NULL, *pr = h;
	FILE *pstu = fopen("stu.txt", "r");
	if(pstu == NULL)
	{
		printf("打开文件出错。\n");
		return;
	}
	while(fscanf(pstu, "%d", &newid) != EOF)
	{
		if(newid == 0)
			break;
		p = (struct student *)malloc(sizeof(struct student));
		pr->next = p;
		p->id = newid;
		fscanf(pstu, "%s", p->name);
		fscanf(pstu, "%d", &p->courcount);
		for(i=0; i<p->courcount; i++)
		{
			fscanf(pstu, "%d", &p->cour[i]);
		}
		fscanf(pstu, "%lf", &p->credit);
		p->next = NULL;
		pr = p;
	}
	printf("读取文件完成。\n");
	return;
}
void delestu(struct student *h)
{
	struct student *p = NULL, *pr = h;
	int id;
	char flg;
	printf("***删除学生信息***\n");
	printf("请输入学号:");
	scanf("%d", &id);
	p = search_id(h, id);
	while(p == NULL)
	{
		printf("学号%d不存在。请重新输入。\n学号:", id);
		scanf("%d", &id);
		p = search_id(h, id);
	}
	output_stu(p);
	printf("确认删除?(y/n)");
	getchar();
	scanf("%c", &flg);
	while(flg != 'n' && flg != 'y')
	{
		printf("请输入y或者n.");
		scanf("%c", &flg);
	}
	if(flg == 'n')
	{
		printf("取消删除。\n");
		return;
	}
	if(flg == 'y')
	{
		while(pr->next != p)
		{
			pr = pr->next;
		}
		pr->next = p->next;
		free(p);
		printf("删除成功。\n");
	}
	ms_log_stu("删除", id);
	return;
}
void changestu(struct student *h)
{
	int i, id, newid, flg = 0;
	struct student *t = NULL;
	printf("***修改学生信息***\n");
	printf("输入学生学号:");
	scanf("%d", &id);
	t = search_id(h, id);
	if(t == NULL)
	{
		printf("该学号不存在。\n");
		return;
	}
	printf("当前学生信息:\n");
	output_stu(t);
	output_menu_changestu();
	scanf("%d", &flg);
	while(flg != 3)
	{
		switch (flg)
		{
			case 1 :
					printf("学号:");
					scanf("%d", &newid);
					while(newid != id && search_id(h, newid) != NULL)
	 				{
						printf("该学号已存在，请重新输入。\n学号:");
						scanf("%d", &newid);
					}
					t->id = newid;
					printf("学号修改成功。\n");
					break;
			case 2 :
					printf("姓名:");
					scanf("%s", t->name);
					printf("姓名修改成功。\n");
					break;
			default :
					printf("输入不正确。");
		}
		printf("输入选项:");
		scanf("%d", &flg);
	}
	printf("退出修改。\n");
	ms_log_stu("修改", t->id);
	output_stu(t);
	return;
}
void output_stu(struct student *t)
{
	int i;
	if(t == NULL)
	{
		printf("NULL.\n");
		return;
	}
	printf("id : %02d\tname : %s\tcourse : ", t->id, t->name);
	for(i=0; i<t->courcount; i++)
	{
		printf("%d ", t->cour[i]);
	}
	printf("\tcredit : %.1f\n", t->credit);
}
void output_students(struct student *h)
{
	struct student *p = h->next;
	while(p != NULL)
	{
		output_stu(p);
		p = p->next;
	}
}
void savefile_stu(struct student *h)//保存到文档
{
	int i;
	FILE *fp = fopen("stu.txt", "w+");
	struct student *p = h->next;
	if(fp == NULL)
	{
		printf("保存为文档失败。\n");
		return;
	}
	while(p != NULL)
	{
		fprintf(fp, "%d %s %d ", p->id, p->name, p->courcount);
		for(i=0; i<p->courcount; i++)
		{
			fprintf(fp, "%d ", p->cour[i]);
		}
		fprintf(fp, "%.1f\n", p->credit);
		fflush(fp);
		p = p->next;
	}
	fclose(fp);
	printf("已保存\n");
}
void output_menu_changestu()//打印修改学生信息菜单
{
	printf("***修改学生信息菜单***\n");
	printf("1.修改学号  2.修改姓名\n3.退出\n输入选项:");
}
