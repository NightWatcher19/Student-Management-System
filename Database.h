#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<time.h>

//定义结构体：文件操作的变量，使用匿名结构
struct File
{
	char *filename;
	FILE *pfile;
}Global = { "Studentpdata.bin",NULL };

//根据专业分课程，DQ代表电气，后面两位数字是专业代码
struct Subject
{
	char Subject1[25];
	char Subject2[25];
	char Subject3[25];
	char Subject4[25];
	char Subject5[25];
	char Subject6[25];
};
	Subject DQ_01{ "高等数学","大学英语","C语言程序设计","工程制图      ","思想道德基础与法律修养","体育" };
	Subject DQ_02{ "高等数学","大学英语","C语言程序设计","工程制图      ","思想道德基础与法律修养","体育" };
	Subject DQ_03{ "高等数学","大学英语","C语言程序设计","大学计算机基础","马克思主义基本原理    ","体育" };
	Subject DQ_04{ "高等数学","大学英语","C语言程序设计","线性代数      ","马克思主义基本原理    ","体育" };
	Subject DQ_12{ "高等数学","大学英语","C语言程序设计","工程制图      ","中国近代史纲要        ","体育" };
	Subject DQ_23{ "高等数学","大学英语","C语言程序设计","心理健康      ","马克思主义基本原理    ","体育" };

	//定义结构体：专业库
	struct StudentMajor
	{
		char szMajor01[20];
		char szMajor02[20];
		char szMajor03[20];
		char szMajor04[20];
		char szMajor12[20];
		char szMajor23[20];
	};
	StudentMajor DQ_StudentMajor{ "电气工程及其自动化", "自动化", "电子信息工程", "电子科学与技术", "测控技术与仪器", "新能源科学与工程" };

//定义结构体：分数
struct Grade
{
	char Grade1[5];
	char Grade2[5];
	char Grade3[5];
	char Grade4[5];
	char Grade5[5];
	char Grade6[5];
};

//定义结构体：一名学生的资料
struct StudentData
{
	//基本信息
	char szStudentNum[20];
	char szName[20];
	char szInstitude[20];
	char szMajor[20];
	//学号组成
	char szyear[10];
	char szinstitude[10];
	char szmajor[10];
	char szclass[10];
	char sznum[10];
	Subject szSubject;
	Grade szGrade;
};

//声明函数区域
void MouseButtonBehavior ();
void InitWindow();

//函数：打开文件
void fnOpenFile(char *mode)
{
	if (Global.pfile)
	{
		fclose(Global.pfile);
		Global.pfile = NULL;
	}
	if (fopen_s(&Global.pfile, Global.filename, mode))
	{
		MessageBox(NULL, "当前学生信息库中没有学生信息\n请先添加学生信息！", "警告", MB_OK | MB_ICONWARNING);
		InitWindow();
	}
}

//函数：写入数据
void fnGetData(char *ch, size_t size)
{
	scanf_s("%s", ch, size);
}

//函数：显示学生信息
void fnShowStudentData(StudentData data)
{
	system("cls");
	printf_s("学生的基本信息如下:\n姓名:%s\n", data.szName);
	printf_s("学号:%s\n", data.szStudentNum);
	printf_s("所属学院:%s\n", data.szInstitude);
	printf_s("专业:%s\n", data.szMajor);
	printf_s("班级:%s班\n", data.szclass);
	printf_s("\t\t%s\t\t成绩:%s\n", data.szSubject.Subject1, data.szGrade.Grade1);
	printf_s("\t\t%s\t\t成绩:%s\n", data.szSubject.Subject2, data.szGrade.Grade2);
	printf_s("\t\t%s\t\t成绩:%s\n", data.szSubject.Subject3, data.szGrade.Grade3);
	printf_s("\t\t%s\t\t成绩:%s\n", data.szSubject.Subject4, data.szGrade.Grade4);
	printf_s("\t\t%s\t成绩:%s\n", data.szSubject.Subject5, data.szGrade.Grade5);
	printf_s("\t\t%s\t\t\t成绩:%s\n", data.szSubject.Subject6, data.szGrade.Grade6);

	system("pause");
	system("cls");
	
}

//函数：删除学生信息
void fnDeleteStudent()
{
	closegraph();
	system("cls");

	StudentData read;
	char num[15];
	int i = 0;
	InputBox(num, 13, TEXT("请输入学号进行查询"));

	fnOpenFile("rb");
	while (fread(&read, sizeof(StudentData), 1, Global.pfile))
	{
		if (strcmp(read.szStudentNum, num) == 0)
		{
			i =1;
			fnShowStudentData(read);
			int mb;
			fclose(Global.pfile);
			Global.pfile = NULL;

			mb = MessageBox(NULL, "你确定要删除此学生的信息吗？", "警告", MB_YESNO | MB_ICONWARNING);
			if (mb == IDYES)
			{
				char *newfilename = "Temple.bin";
				FILE *pnewfile = NULL;

				fopen_s(&Global.pfile, Global.filename, "rb");
				fopen_s(&pnewfile, newfilename, "wb");
				while (fread(&read, sizeof(StudentData), 1, Global.pfile))
				{
					if (strcmp(read.szStudentNum, num) != 0)
						fwrite(&read, sizeof(StudentData), 1, pnewfile);
					else
						continue;
				}

				fclose(pnewfile);
				pnewfile = NULL;
				fclose(Global.pfile);
				Global.pfile = NULL;

				remove(Global.filename);
				rename(newfilename, Global.filename);
				break;
			}
			else
				InitWindow();
		}
	}

	if (i == 0)
	{
		MessageBox(NULL, "未查询该同学的相关信息", "提示", MB_ICONMASK);
		fclose(Global.pfile);
		Global.pfile = NULL;
	}
}

//函数：录入一个学生的信息
void fnAddStudent()
{
	StudentData data;
	StudentData read;
	closegraph();

	//学号生成系统
	{
		printf_s("请输入学生的姓名:");
		fnGetData(data.szName, sizeof(data.szName));
		printf_s("学生名字：%s\n\n", data.szName);

		printf_s("请输入入学时间（年）：");
		fnGetData(data.szyear, sizeof(data.szyear));
		printf_s("入学年份：%s\n\n", data.szyear);

		//学院选择
		{
			printf_s("请输入学院编号：\n01.电气信息学院\n02.机械工程学院\n03.计算机与通信学院\n04.外国语学院\n05.经济学院\n");
			printf_s("06.化学化工学院\n07.管理学院\n08.纺织服装学院\n09.建筑工程学院\n10.理学院\n11.国际教育学院\n12.设计艺术学院\n");
			fnGetData(data.szinstitude, sizeof(data.szinstitude));
			if (!strcmp(data.szinstitude, "01\0"))
			{
				strcpy(data.szInstitude, "电气信息学院\0");
				printf_s("您已选择：%s\n\n", data.szInstitude);
			}
			else
			{
				printf_s("管理系统V1.0  只能记录电气信息学院的学生成绩\n");
				Sleep(2000);
				InitWindow();
			}
		}

		//专业选择	
		{
			printf_s("请输入专业编号：");
			printf_s("\n01.%s\t02.%s", DQ_StudentMajor.szMajor01, DQ_StudentMajor.szMajor02);
			printf_s("\n03.%s\t\t04.%s", DQ_StudentMajor.szMajor03, DQ_StudentMajor.szMajor04);
			printf_s("\n12.%s\t23.%s\n", DQ_StudentMajor.szMajor12, DQ_StudentMajor.szMajor23);
			fnGetData(data.szmajor, sizeof(data.szmajor));
			if (!strcmp(data.szmajor, "01\0"))
			{
				sprintf(data.szMajor, DQ_StudentMajor.szMajor01);
				printf_s("您已选择：%s\n\n", data.szMajor);
				sprintf(data.szSubject.Subject1, DQ_01.Subject1);
sprintf(data.szSubject.Subject2, DQ_01.Subject2);
sprintf(data.szSubject.Subject3, DQ_01.Subject3);
sprintf(data.szSubject.Subject4, DQ_01.Subject4);
sprintf(data.szSubject.Subject5, DQ_01.Subject5);
sprintf(data.szSubject.Subject6, DQ_01.Subject6);
			}
			if (!strcmp(data.szmajor, "02\0"))
			{
				sprintf(data.szMajor, DQ_StudentMajor.szMajor02);
				printf_s("您已选择：%s\n\n", data.szMajor);
				sprintf(data.szSubject.Subject1, DQ_02.Subject1);
				sprintf(data.szSubject.Subject2, DQ_02.Subject2);
				sprintf(data.szSubject.Subject3, DQ_02.Subject3);
				sprintf(data.szSubject.Subject4, DQ_02.Subject4);
				sprintf(data.szSubject.Subject5, DQ_02.Subject5);
				sprintf(data.szSubject.Subject6, DQ_02.Subject6);
			}
			if (!strcmp(data.szmajor, "03\0"))
			{
				sprintf(data.szMajor, DQ_StudentMajor.szMajor03);
				printf_s("您已选择：%s\n\n", data.szMajor);
				sprintf(data.szSubject.Subject1, DQ_03.Subject1);
				sprintf(data.szSubject.Subject2, DQ_03.Subject2);
				sprintf(data.szSubject.Subject3, DQ_03.Subject3);
				sprintf(data.szSubject.Subject4, DQ_03.Subject4);
				sprintf(data.szSubject.Subject5, DQ_03.Subject5);
				sprintf(data.szSubject.Subject6, DQ_03.Subject6);
			}
			if (!strcmp(data.szmajor, "04\0"))
			{
				sprintf(data.szMajor, DQ_StudentMajor.szMajor04);
				printf_s("您已选择：%s\n\n", data.szMajor);
				sprintf(data.szSubject.Subject1, DQ_04.Subject1);
				sprintf(data.szSubject.Subject2, DQ_04.Subject2);
				sprintf(data.szSubject.Subject3, DQ_04.Subject3);
				sprintf(data.szSubject.Subject4, DQ_04.Subject4);
				sprintf(data.szSubject.Subject5, DQ_04.Subject5);
				sprintf(data.szSubject.Subject6, DQ_04.Subject6);
			}
			if (!strcmp(data.szmajor, "12\0"))
			{
				sprintf(data.szMajor, DQ_StudentMajor.szMajor12);
				printf_s("您已选择：%s\n\n", data.szMajor);
				sprintf(data.szSubject.Subject1, DQ_12.Subject1);
				sprintf(data.szSubject.Subject2, DQ_12.Subject2);
				sprintf(data.szSubject.Subject3, DQ_12.Subject3);
				sprintf(data.szSubject.Subject4, DQ_12.Subject4);
				sprintf(data.szSubject.Subject5, DQ_12.Subject5);
				sprintf(data.szSubject.Subject6, DQ_12.Subject6);
			}
			if (!strcmp(data.szmajor, "23\0"))
			{
				sprintf(data.szMajor, DQ_StudentMajor.szMajor23);
				printf_s("您已选择：%s\n\n", data.szMajor);
				sprintf(data.szSubject.Subject1, DQ_23.Subject1);
				sprintf(data.szSubject.Subject2, DQ_23.Subject2);
				sprintf(data.szSubject.Subject3, DQ_23.Subject3);
				sprintf(data.szSubject.Subject4, DQ_23.Subject4);
				sprintf(data.szSubject.Subject5, DQ_23.Subject5);
				sprintf(data.szSubject.Subject6, DQ_23.Subject6);
			}
		}

		//选择班级
		{
		printf_s("请输入班级：（例如：一班——01）\n");
		scanf_s("%s", &data.szclass, sizeof(data.szclass));
		printf_s("您已选择：%s班\n\n", data.szclass);
		}

		//班级内编号
		{
			int mb;
			mb = MessageBox(NULL, TEXT("请问是否使用电脑生成学生序号？\n手动输入请点击否"), TEXT("提示"), MB_YESNO | MB_ICONINFORMATION);
			if (mb == IDYES)
			{
				Address1:
				while (true)
				{
					srand((unsigned int)time(NULL));
					sprintf(data.sznum, "%d", rand() % 90 + 10);

					//判断学号是否重复
					fnOpenFile("ab+");
					while (fread(&read, sizeof(StudentData), 1, Global.pfile))//必须读取完
					{
						//只要班级，专业，编号任意一个不相同即可
						if (strcmp(data.szyear, read.szyear) == 0 && strcmp(data.szclass, read.szclass) == 0 && strcmp(data.szmajor, read.szmajor) == 0 && strcmp(data.sznum, read.sznum) == 0)
						{
							printf_s("%s%s班该编号已存在，请重新输入编号\n", data.szmajor, data.szclass);
							fclose(Global.pfile);
							Global.pfile = NULL;
							goto Address1;
						}
					}
					fclose(Global.pfile);
					Global.pfile = NULL;
					break;
				}
				puts(data.sznum);
			}
			else
			{
				Address2:
				while (true)
				{
					printf_s("请输入班级内编号：(编号必须是两位数字)\n");
					while (!scanf_s("%s", data.sznum, sizeof(data.sznum)))
						printf_s("您的输入有误，请重新输入！\n");
					
					//判断学号是否重复
					fnOpenFile("ab+");
					while (fread(&read, sizeof(StudentData), 1, Global.pfile))//必须读取完
					{
						//只要班级，专业，编号任意一个不相同即可
						if (strcmp(data.szyear, read.szyear) == 0 && strcmp(data.szclass, read.szclass) == 0 && strcmp(data.szmajor, read.szmajor) == 0 && strcmp(data.sznum, read.sznum) == 0)
						{
							printf_s("%s%s班该编号已存在，请重新输入编号\n", data.szMajor, data.szclass);
							fclose(Global.pfile);
							Global.pfile = NULL;
							goto Address2;
						}
					}

					break;
				}
			}
		}

		//合成学号
		{
			char szStudentNumber[13];
			sprintf(szStudentNumber, "%s%s%s%s%s", data.szyear, data.szinstitude, data.szmajor, data.szclass, data.sznum);
			strcpy(data.szStudentNum, szStudentNumber);
			printf_s("已生成学号：%s\n\n", data.szStudentNum);
		}
	}

	
	//录入成绩
		printf_s("请输入%s同学的\t\t%s\t\t成绩:", data.szName, data.szSubject.Subject1);
		scanf_s("%s", data.szGrade.Grade1, sizeof(data.szGrade.Grade1));
		printf_s("请输入%s同学的\t\t%s\t\t成绩:", data.szName, data.szSubject.Subject2);
		scanf_s("%s", data.szGrade.Grade2, sizeof(data.szGrade.Grade2));
		printf_s("请输入%s同学的\t\t%s\t\t成绩:", data.szName, data.szSubject.Subject3);
		scanf_s("%s", data.szGrade.Grade3, sizeof(data.szGrade.Grade3));
		printf_s("请输入%s同学的\t\t%s\t\t成绩:", data.szName, data.szSubject.Subject4);
		scanf_s("%s", data.szGrade.Grade4, sizeof(data.szGrade.Grade4));
		printf_s("请输入%s同学的\t\t%s\t成绩:", data.szName, data.szSubject.Subject5);
		scanf_s("%s", data.szGrade.Grade5, sizeof(data.szGrade.Grade5));
		printf_s("请输入%s同学的\t\t%s\t\t\t成绩:", data.szName, data.szSubject.Subject6);
		scanf_s("%s", data.szGrade.Grade6, sizeof(data.szGrade.Grade6));

	
		//写入文件
			fnOpenFile("ab+");
			fwrite(&data, sizeof(data), 1, Global.pfile);
			printf_s("学生信息保存成功!\n");
			Sleep(1000);
			fclose(Global.pfile);
			Global.pfile = NULL;

			fnShowStudentData(data);
}

//函数：获取鼠标坐标
void fnGetMouseXY()
{

	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			TCHAR x[10], y[10];
			_stprintf(x, _T("%d"), m.x);
			_stprintf(y, _T("%d"), m.y);

			solidrectangle(0, 0, 70, 15);
			setbkmode(TRANSPARENT);
			settextcolor(RGB(0, 0, 0));
			outtextxy(0, 0, x);
			outtextxy(35, 0, ',');
			outtextxy(40, 0, y);
			break;
		case WM_LBUTTONDOWN:
			_stprintf(x, _T("%d"), m.x);
			_stprintf(y, _T("%d"), m.y);

			solidrectangle(1030, 0, 1100, 15);
			setbkmode(TRANSPARENT);
			settextcolor(RGB(0, 0, 0));
			outtextxy(1030, 0, x);
			outtextxy(1065, 0, ',');
			outtextxy(1070, 0, y);
			break;
		case WM_RBUTTONDOWN:
			closegraph();
			exit(1);
			break;
		}
	}
}

//函数：初始化窗口
void InitWindow()
{
	system("cls");
	printf_s("欢迎使用学生管理系统！\n");
	IMAGE img;
	loadimage(&img, _T("background.jpg"), 1100, 700);
	initgraph(1100, 700, SHOWCONSOLE);
	putimage(0, 0, &img);
//	fnGetMouseXY();
	MouseButtonBehavior();
}

//函数：鼠标行为判断
void MouseButtonBehavior()
{
	MOUSEMSG m;
	int a = 1;

	while (a)
	{
		m = GetMouseMsg();
		int i = 0;
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			
			//录入
			if (m.x > 380 && m.x < 750 && m.y>230 && m.y < 230 + 60)
			{
				fnAddStudent();
				a = 0;
			}

			//查询
			else if (m.x > 380 && m.x < 750 && m.y>230 + 120 && m.y < 230 + 60 + 120)
			{
				StudentData read;
				char num[15];
				closegraph();
				InputBox(num, 13, TEXT("请输入你要查询的学生的学号:"));

				fnOpenFile("rb");
				while (fread(&read, sizeof(StudentData), 1, Global.pfile))
				{
					if (strcmp(read.szStudentNum, num) == 0)
					{
						i = 1;
						fnShowStudentData(read);
					}
				}
				fclose(Global.pfile);
				Global.pfile = NULL;

				if (i==0)
					MessageBox(NULL, "未查询该同学的相关信息", "提示", MB_ICONMASK);

				a = 0;
			}

			//删除
			else if (m.x > 380 && m.x < 750 && m.y>230 + 120 + 120 && m.y < 230 + 60 + 120+120)
			{
				fnDeleteStudent();
				a = 0;
			}

			//遍历
			else if (m.x > 380 && m.x < 750 && m.y>230 + 120 + 120 + 120 && m.y < 230 + 60 + 120 + 120 + 120)
			{

				StudentData read;
				closegraph();

				fnOpenFile("rb");
				while (fread(&read, sizeof(StudentData), 1, Global.pfile))
					fnShowStudentData(read);
				fclose(Global.pfile);
				Global.pfile = NULL;

				printf_s("学生信息已展示完毕\n");
				system("pause");
				a = 0;
			}

			//退出
			else if (m.x > 880 && m.x < 1070 && m.y>630 && m.y < 670)
			{
				closegraph();
				exit(1);
			}
			
			break;
		}
	}

}

