#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>
#include<time.h>

//����ṹ�壺�ļ������ı�����ʹ�������ṹ
struct File
{
	char *filename;
	FILE *pfile;
}Global = { "Studentpdata.bin",NULL };

//����רҵ�ֿγ̣�DQ���������������λ������רҵ����
struct Subject
{
	char Subject1[25];
	char Subject2[25];
	char Subject3[25];
	char Subject4[25];
	char Subject5[25];
	char Subject6[25];
};
	Subject DQ_01{ "�ߵ���ѧ","��ѧӢ��","C���Գ������","������ͼ      ","˼����»����뷨������","����" };
	Subject DQ_02{ "�ߵ���ѧ","��ѧӢ��","C���Գ������","������ͼ      ","˼����»����뷨������","����" };
	Subject DQ_03{ "�ߵ���ѧ","��ѧӢ��","C���Գ������","��ѧ���������","���˼�������ԭ��    ","����" };
	Subject DQ_04{ "�ߵ���ѧ","��ѧӢ��","C���Գ������","���Դ���      ","���˼�������ԭ��    ","����" };
	Subject DQ_12{ "�ߵ���ѧ","��ѧӢ��","C���Գ������","������ͼ      ","�й�����ʷ��Ҫ        ","����" };
	Subject DQ_23{ "�ߵ���ѧ","��ѧӢ��","C���Գ������","������      ","���˼�������ԭ��    ","����" };

	//����ṹ�壺רҵ��
	struct StudentMajor
	{
		char szMajor01[20];
		char szMajor02[20];
		char szMajor03[20];
		char szMajor04[20];
		char szMajor12[20];
		char szMajor23[20];
	};
	StudentMajor DQ_StudentMajor{ "�������̼����Զ���", "�Զ���", "������Ϣ����", "���ӿ�ѧ�뼼��", "��ؼ���������", "����Դ��ѧ�빤��" };

//����ṹ�壺����
struct Grade
{
	char Grade1[5];
	char Grade2[5];
	char Grade3[5];
	char Grade4[5];
	char Grade5[5];
	char Grade6[5];
};

//����ṹ�壺һ��ѧ��������
struct StudentData
{
	//������Ϣ
	char szStudentNum[20];
	char szName[20];
	char szInstitude[20];
	char szMajor[20];
	//ѧ�����
	char szyear[10];
	char szinstitude[10];
	char szmajor[10];
	char szclass[10];
	char sznum[10];
	Subject szSubject;
	Grade szGrade;
};

//������������
void MouseButtonBehavior ();
void InitWindow();

//���������ļ�
void fnOpenFile(char *mode)
{
	if (Global.pfile)
	{
		fclose(Global.pfile);
		Global.pfile = NULL;
	}
	if (fopen_s(&Global.pfile, Global.filename, mode))
	{
		MessageBox(NULL, "��ǰѧ����Ϣ����û��ѧ����Ϣ\n�������ѧ����Ϣ��", "����", MB_OK | MB_ICONWARNING);
		InitWindow();
	}
}

//������д������
void fnGetData(char *ch, size_t size)
{
	scanf_s("%s", ch, size);
}

//��������ʾѧ����Ϣ
void fnShowStudentData(StudentData data)
{
	system("cls");
	printf_s("ѧ���Ļ�����Ϣ����:\n����:%s\n", data.szName);
	printf_s("ѧ��:%s\n", data.szStudentNum);
	printf_s("����ѧԺ:%s\n", data.szInstitude);
	printf_s("רҵ:%s\n", data.szMajor);
	printf_s("�༶:%s��\n", data.szclass);
	printf_s("\t\t%s\t\t�ɼ�:%s\n", data.szSubject.Subject1, data.szGrade.Grade1);
	printf_s("\t\t%s\t\t�ɼ�:%s\n", data.szSubject.Subject2, data.szGrade.Grade2);
	printf_s("\t\t%s\t\t�ɼ�:%s\n", data.szSubject.Subject3, data.szGrade.Grade3);
	printf_s("\t\t%s\t\t�ɼ�:%s\n", data.szSubject.Subject4, data.szGrade.Grade4);
	printf_s("\t\t%s\t�ɼ�:%s\n", data.szSubject.Subject5, data.szGrade.Grade5);
	printf_s("\t\t%s\t\t\t�ɼ�:%s\n", data.szSubject.Subject6, data.szGrade.Grade6);

	system("pause");
	system("cls");
	
}

//������ɾ��ѧ����Ϣ
void fnDeleteStudent()
{
	closegraph();
	system("cls");

	StudentData read;
	char num[15];
	int i = 0;
	InputBox(num, 13, TEXT("������ѧ�Ž��в�ѯ"));

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

			mb = MessageBox(NULL, "��ȷ��Ҫɾ����ѧ������Ϣ��", "����", MB_YESNO | MB_ICONWARNING);
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
		MessageBox(NULL, "δ��ѯ��ͬѧ�������Ϣ", "��ʾ", MB_ICONMASK);
		fclose(Global.pfile);
		Global.pfile = NULL;
	}
}

//������¼��һ��ѧ������Ϣ
void fnAddStudent()
{
	StudentData data;
	StudentData read;
	closegraph();

	//ѧ������ϵͳ
	{
		printf_s("������ѧ��������:");
		fnGetData(data.szName, sizeof(data.szName));
		printf_s("ѧ�����֣�%s\n\n", data.szName);

		printf_s("��������ѧʱ�䣨�꣩��");
		fnGetData(data.szyear, sizeof(data.szyear));
		printf_s("��ѧ��ݣ�%s\n\n", data.szyear);

		//ѧԺѡ��
		{
			printf_s("������ѧԺ��ţ�\n01.������ϢѧԺ\n02.��е����ѧԺ\n03.�������ͨ��ѧԺ\n04.�����ѧԺ\n05.����ѧԺ\n");
			printf_s("06.��ѧ����ѧԺ\n07.����ѧԺ\n08.��֯��װѧԺ\n09.��������ѧԺ\n10.��ѧԺ\n11.���ʽ���ѧԺ\n12.�������ѧԺ\n");
			fnGetData(data.szinstitude, sizeof(data.szinstitude));
			if (!strcmp(data.szinstitude, "01\0"))
			{
				strcpy(data.szInstitude, "������ϢѧԺ\0");
				printf_s("����ѡ��%s\n\n", data.szInstitude);
			}
			else
			{
				printf_s("����ϵͳV1.0  ֻ�ܼ�¼������ϢѧԺ��ѧ���ɼ�\n");
				Sleep(2000);
				InitWindow();
			}
		}

		//רҵѡ��	
		{
			printf_s("������רҵ��ţ�");
			printf_s("\n01.%s\t02.%s", DQ_StudentMajor.szMajor01, DQ_StudentMajor.szMajor02);
			printf_s("\n03.%s\t\t04.%s", DQ_StudentMajor.szMajor03, DQ_StudentMajor.szMajor04);
			printf_s("\n12.%s\t23.%s\n", DQ_StudentMajor.szMajor12, DQ_StudentMajor.szMajor23);
			fnGetData(data.szmajor, sizeof(data.szmajor));
			if (!strcmp(data.szmajor, "01\0"))
			{
				sprintf(data.szMajor, DQ_StudentMajor.szMajor01);
				printf_s("����ѡ��%s\n\n", data.szMajor);
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
				printf_s("����ѡ��%s\n\n", data.szMajor);
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
				printf_s("����ѡ��%s\n\n", data.szMajor);
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
				printf_s("����ѡ��%s\n\n", data.szMajor);
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
				printf_s("����ѡ��%s\n\n", data.szMajor);
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
				printf_s("����ѡ��%s\n\n", data.szMajor);
				sprintf(data.szSubject.Subject1, DQ_23.Subject1);
				sprintf(data.szSubject.Subject2, DQ_23.Subject2);
				sprintf(data.szSubject.Subject3, DQ_23.Subject3);
				sprintf(data.szSubject.Subject4, DQ_23.Subject4);
				sprintf(data.szSubject.Subject5, DQ_23.Subject5);
				sprintf(data.szSubject.Subject6, DQ_23.Subject6);
			}
		}

		//ѡ��༶
		{
		printf_s("������༶�������磺һ�ࡪ��01��\n");
		scanf_s("%s", &data.szclass, sizeof(data.szclass));
		printf_s("����ѡ��%s��\n\n", data.szclass);
		}

		//�༶�ڱ��
		{
			int mb;
			mb = MessageBox(NULL, TEXT("�����Ƿ�ʹ�õ�������ѧ����ţ�\n�ֶ�����������"), TEXT("��ʾ"), MB_YESNO | MB_ICONINFORMATION);
			if (mb == IDYES)
			{
				Address1:
				while (true)
				{
					srand((unsigned int)time(NULL));
					sprintf(data.sznum, "%d", rand() % 90 + 10);

					//�ж�ѧ���Ƿ��ظ�
					fnOpenFile("ab+");
					while (fread(&read, sizeof(StudentData), 1, Global.pfile))//�����ȡ��
					{
						//ֻҪ�༶��רҵ���������һ������ͬ����
						if (strcmp(data.szyear, read.szyear) == 0 && strcmp(data.szclass, read.szclass) == 0 && strcmp(data.szmajor, read.szmajor) == 0 && strcmp(data.sznum, read.sznum) == 0)
						{
							printf_s("%s%s��ñ���Ѵ��ڣ�������������\n", data.szmajor, data.szclass);
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
					printf_s("������༶�ڱ�ţ�(��ű�������λ����)\n");
					while (!scanf_s("%s", data.sznum, sizeof(data.sznum)))
						printf_s("���������������������룡\n");
					
					//�ж�ѧ���Ƿ��ظ�
					fnOpenFile("ab+");
					while (fread(&read, sizeof(StudentData), 1, Global.pfile))//�����ȡ��
					{
						//ֻҪ�༶��רҵ���������һ������ͬ����
						if (strcmp(data.szyear, read.szyear) == 0 && strcmp(data.szclass, read.szclass) == 0 && strcmp(data.szmajor, read.szmajor) == 0 && strcmp(data.sznum, read.sznum) == 0)
						{
							printf_s("%s%s��ñ���Ѵ��ڣ�������������\n", data.szMajor, data.szclass);
							fclose(Global.pfile);
							Global.pfile = NULL;
							goto Address2;
						}
					}

					break;
				}
			}
		}

		//�ϳ�ѧ��
		{
			char szStudentNumber[13];
			sprintf(szStudentNumber, "%s%s%s%s%s", data.szyear, data.szinstitude, data.szmajor, data.szclass, data.sznum);
			strcpy(data.szStudentNum, szStudentNumber);
			printf_s("������ѧ�ţ�%s\n\n", data.szStudentNum);
		}
	}

	
	//¼��ɼ�
		printf_s("������%sͬѧ��\t\t%s\t\t�ɼ�:", data.szName, data.szSubject.Subject1);
		scanf_s("%s", data.szGrade.Grade1, sizeof(data.szGrade.Grade1));
		printf_s("������%sͬѧ��\t\t%s\t\t�ɼ�:", data.szName, data.szSubject.Subject2);
		scanf_s("%s", data.szGrade.Grade2, sizeof(data.szGrade.Grade2));
		printf_s("������%sͬѧ��\t\t%s\t\t�ɼ�:", data.szName, data.szSubject.Subject3);
		scanf_s("%s", data.szGrade.Grade3, sizeof(data.szGrade.Grade3));
		printf_s("������%sͬѧ��\t\t%s\t\t�ɼ�:", data.szName, data.szSubject.Subject4);
		scanf_s("%s", data.szGrade.Grade4, sizeof(data.szGrade.Grade4));
		printf_s("������%sͬѧ��\t\t%s\t�ɼ�:", data.szName, data.szSubject.Subject5);
		scanf_s("%s", data.szGrade.Grade5, sizeof(data.szGrade.Grade5));
		printf_s("������%sͬѧ��\t\t%s\t\t\t�ɼ�:", data.szName, data.szSubject.Subject6);
		scanf_s("%s", data.szGrade.Grade6, sizeof(data.szGrade.Grade6));

	
		//д���ļ�
			fnOpenFile("ab+");
			fwrite(&data, sizeof(data), 1, Global.pfile);
			printf_s("ѧ����Ϣ����ɹ�!\n");
			Sleep(1000);
			fclose(Global.pfile);
			Global.pfile = NULL;

			fnShowStudentData(data);
}

//��������ȡ�������
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

//��������ʼ������
void InitWindow()
{
	system("cls");
	printf_s("��ӭʹ��ѧ������ϵͳ��\n");
	IMAGE img;
	loadimage(&img, _T("background.jpg"), 1100, 700);
	initgraph(1100, 700, SHOWCONSOLE);
	putimage(0, 0, &img);
//	fnGetMouseXY();
	MouseButtonBehavior();
}

//�����������Ϊ�ж�
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
			
			//¼��
			if (m.x > 380 && m.x < 750 && m.y>230 && m.y < 230 + 60)
			{
				fnAddStudent();
				a = 0;
			}

			//��ѯ
			else if (m.x > 380 && m.x < 750 && m.y>230 + 120 && m.y < 230 + 60 + 120)
			{
				StudentData read;
				char num[15];
				closegraph();
				InputBox(num, 13, TEXT("��������Ҫ��ѯ��ѧ����ѧ��:"));

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
					MessageBox(NULL, "δ��ѯ��ͬѧ�������Ϣ", "��ʾ", MB_ICONMASK);

				a = 0;
			}

			//ɾ��
			else if (m.x > 380 && m.x < 750 && m.y>230 + 120 + 120 && m.y < 230 + 60 + 120+120)
			{
				fnDeleteStudent();
				a = 0;
			}

			//����
			else if (m.x > 380 && m.x < 750 && m.y>230 + 120 + 120 + 120 && m.y < 230 + 60 + 120 + 120 + 120)
			{

				StudentData read;
				closegraph();

				fnOpenFile("rb");
				while (fread(&read, sizeof(StudentData), 1, Global.pfile))
					fnShowStudentData(read);
				fclose(Global.pfile);
				Global.pfile = NULL;

				printf_s("ѧ����Ϣ��չʾ���\n");
				system("pause");
				a = 0;
			}

			//�˳�
			else if (m.x > 880 && m.x < 1070 && m.y>630 && m.y < 670)
			{
				closegraph();
				exit(1);
			}
			
			break;
		}
	}

}

