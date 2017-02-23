#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


#define FORMAT "%9s%9s%14s%8s%8s%18s%18s%10s%14d%8d%8d\n"
#define DATA stu[i].no,stu[i].name,stu[i].birthday,stu[i].sex,stu[i].nation,stu[i].department,stu[i].major,stu[i].province,stu[i].score,stu[i].add,stu[i].total
#define LEN sizeof(struct student)
#define TITLEBAR "\n\n     学号     姓名      出生日期    性别    民族              院系              专业      省份      卷面成绩    加分    总分\n"

void enter();
void print();
void search();
void insert();
void del();

struct student               //定义结构体类型
{
    char no[10];         //学号
    char name[10];       //姓名
    char birthday[10];    //出生日期
    char sex[3];         //性别
    char nation[10];      //民族
    char department[20];  //院系
    char major[20];      //专业
    char province[20];    //省份
    int score;           //卷面成绩
    int add;             //加分
    int total;            //总分=卷面成绩+加分
} stu[100];

void gotoxy(int x,int y)                ///光标定位
{
    COORD coord= {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void menu()
{
    printf("\n\n=====================================================================\n");
    printf("===============================学生成绩管理系统======================\n");
    printf("=====================================================================\n");
    printf("===1、输入数据  2、显示数据  3、查询数据  4、插入学生  5、删除学生===\n");
    printf("===6、保存数据  7、读入数据  8、成绩排序  9、修改数据  0、退出    ===\n");
    printf("=====================================================================\n\n");
    printf("请输入：");
}



void enter()
{
    int m=0,j,personNumber;
    FILE *fp;                                          ///读取文件内容
    if((fp=fopen("学生信息.txt","r"))==NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    while(!feof(fp))
    {
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    }
    fclose(fp);

    if(m==0)                                         ///文件中有内容则打印出来，方便录入
        printf("源文件内无学生记录\n");
    else
    {
        system("cls");
        print();
    }

    if((fp=fopen("学生信息.txt","a"))==NULL)             ///打开文件开始读入信息
    {
        printf("文件打开失败！");
        return;
    }
    printf("请输入要录入的学生人数:");                 ///设定录入学生个数
    scanf("%d",&personNumber);
    while(personNumber--)
    {
        printf("请输入学生的学号：\n");                ///学号不允许重复
no:
        scanf("%s",stu[m].no);
        for(j=0; j<m; j++)
        {
            if(strcmp(stu[m].no,stu[j].no)==0)
            {
                printf("此学号已被注册,请重新输入学号:\n");
                goto no;
            }
        }
        printf("请输入学生的姓名：\n");
        scanf("%s",stu[m].name);
        printf("请输入学生的出生日期：\n");
        scanf("%s",stu[m].birthday);
        printf("请输入学生的性别：\n");
        scanf("%s",stu[m].sex);
        printf("请输入学生的民族：\n");
        scanf("%s",stu[m].nation);
        printf("请输入学生的院系：\n");
        scanf("%s",stu[m].department);
        printf("请输入学生的专业：\n");
        scanf("%s",stu[m].major);
        printf("请输入学生的省份：\n");
        scanf("%s",stu[m].province);
        printf("请输入学生的卷面成绩：\n");
        scanf("%d",&stu[m].score);
        printf("请输入学生的加分：\n\n");
        scanf("%d",&stu[m].add);

        stu[m].total=stu[m].score+stu[m].add;

        if(fwrite(&stu[m],LEN,1,fp)!=1)                  ///成块写入文件
        {
            printf("数据写入失败");
            return;
        }
        else
        {
            printf("数据保存成功!!!\n\n\n");
            m++;
        }
    }
    fclose(fp);
}

void print()
{
    int i;
    FILE *fp;
    if((fp=fopen("学生信息.txt","r"))==NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    printf(TITLEBAR);
    for(i=0; !feof(fp); i++)
    {
        fread(&stu[i],LEN,1,fp);
        printf(FORMAT,DATA);
    }
}

void search()
{
    int m=0,i,flag=0;
    char name[10];
    FILE *fp;
    if((fp=fopen("学生信息.txt","r"))==NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    while(!feof(fp))
    {
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    }
    fclose(fp);

    printf("请输入您要查找的学生的姓名：\n");
    scanf("%s",name);
    for(i=0; i<=m; i++)
    {
        if(strcmp(name,stu[i].name)==0&&flag==1)     ///允许重名，设置重名读入方案
            printf(FORMAT,DATA);
        else if(strcmp(name,stu[i].name)==0&&flag==0)
        {
            printf(TITLEBAR);
            printf(FORMAT,DATA);
            flag=1;                         ///找到
        }

    }
    if(flag==0)
        printf("数据库里无该学生信息！\n\n");
    else
        printf("\n");//好看~

}

void insert()
{
    char no[10];
    int m=0,i,j,k,flag=0;
    FILE *fp;
    if((fp=fopen("学生信息.txt","r"))==NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    while(!feof(fp))
    {
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    }
    fclose(fp);

    printf("您将把数据插入到哪个记录之前，请输入该记录的学号:\n");
trueNo:
    scanf("%s",no);
    for(i=0; i<m; i++)
    {
        if(strcmp(no,stu[i].no)==0)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("无此人信息，请重新输入学号：\n");
        goto trueNo;                                          ///输入错误则返回重新输入
    }


    for(j=m-1; j>i-1; j--)
        stu[j+1]=stu[j];

    printf("请输入新学生的信息：\n\n");
    printf("请输入新学生的学号：\n");
newNo:
    scanf("%s",stu[i].no);
    for(k=0; k<m; k++)
    {
        if(k==i)                                             ///检查是否注册过该学号，躲过自己。
            continue;
        if(strcmp(stu[i].no,stu[k].no)==0)
        {
            printf("此学号已被注册,请重新输入学号:\n");
            goto newNo;
        }
    }
    printf("请输入学生的姓名：\n");
    scanf("%s",stu[i].name);
    printf("请输入学生的出生日期：\n");
    scanf("%s",stu[i].birthday);
    printf("请输入学生的性别：\n");
    scanf("%s",stu[i].sex);
    printf("请输入学生的民族：\n");
    scanf("%s",stu[i].nation);
    printf("请输入学生的院系：\n");
    scanf("%s",stu[i].department);
    printf("请输入学生的专业：\n");
    scanf("%s",stu[i].major);
    printf("请输入学生的省份：\n");
    scanf("%s",stu[i].province);
    printf("请输入学生的卷面成绩：\n");
    scanf("%d",&stu[i].score);
    printf("请输入学生的加分：\n\n");
    scanf("%d",&stu[i].add);
    stu[i].total=stu[i].score+stu[i].add;

    if((fp=fopen("学生信息.txt","w"))==NULL)
    {
        printf("文件打开失败！");
        return;
    }
    for(j=0; j<=m; j++)
    {
        fwrite(&stu[j],LEN,1,fp);
    }
    fclose(fp);

}

void del()
{
    int m=0,i,j,flag=0;
    char no[10];
    FILE *fp;
    if((fp=fopen("学生信息.txt","r"))==NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    while(!feof(fp))
    {
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    }
    fclose(fp);

    printf("请输入您要删除的学生的学号：\n");
    scanf("%s",no);
    for(i=0; i<m; i++)
    {
        if(strcmp(no,stu[i].no)==0)
        {
            flag=1;
            break;
        }
    }
    for(j=i; j<m; j++)                             ///删除覆盖
        stu[j]=stu[j+1];
    m--;
    if((fp=fopen("学生信息.txt","w"))==NULL)
    {
        printf("文件打开失败！");
        return;
    }
    for(j=0; j<m; j++)
    {
        fwrite(&stu[j],LEN,1,fp);                  ///重新写入
    }
    fclose(fp);
    if(flag==0)
        printf("无该学生的记录！\n");
    else
        printf("数据已删除！\n");
}

void modify()
{
    char no[10],ch[2];
    int m=0,i,j,flag=0;
    FILE *fp;
    if((fp=fopen("学生信息.txt","r"))==NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    while(!feof(fp))
    {
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    }
    fclose(fp);

    printf("\n\n请输入要修改信息的学生的学号:\n");
    scanf("%s",no);
    for(i=0; i<m; i++)
    {
        if(strcmp(no,stu[i].no)==0)
        {
            flag=1;
            printf(TITLEBAR);
            printf(FORMAT,DATA);
            break;
        }
    }
    if(flag==0)
    {
        printf("无此学生信息");
        return;
    }


    printf("是否修改学号？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入学号：\n");
        scanf("%s",stu[i].no);

    }
    printf("是否修改姓名？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入姓名：\n");
        scanf("%s",stu[i].name);

    }
    printf("是否修改出生日期？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入出生日期\n");
        scanf("%s",stu[i].birthday);

    }
    printf("是否修改性别？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入性别：\n");
        scanf("%s",stu[i].sex);

    }
    printf("是否修改民族？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入民族：\n");
        scanf("%s",stu[i].nation);

    }
    printf("是否修改院系？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入院系：\n");
        scanf("%s",stu[i].department);

    }
    printf("是否修改专业？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入专业：\n");
        scanf("%s",stu[i].major);

    }
    printf("是否修改省份？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入省份：\n");
        scanf("%s",stu[i].province);

    }
    printf("是否修改卷面成绩？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入卷面成绩：\n");
        scanf("%d",&stu[i].score);

    }
    printf("是否修改加分？(y/n)");
    scanf("%s",ch);
    if(strcmp(ch,"y")==0||strcmp(ch,"Y")==0)
    {
        printf("请输入加分：\n");
        scanf("%d",&stu[i].add);

    }
    stu[i].total=stu[i].score+stu[i].add;

    if((fp=fopen("学生信息.txt","w"))==NULL)
    {
        printf("文件打开失败！");
        return;
    }
    for(j=0; j<m; j++)
    {
        fwrite(&stu[j],LEN,1,fp);
    }
    fclose(fp);
}

void sort()
{
    int m=0,i,j,k;
    struct student temp;
    FILE *fp;
    if((fp=fopen("学生信息.txt","r"))==NULL)
    {
        printf("打开文件失败！\n");
        return;
    }
    while(!feof(fp))
    {
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    }
    fclose(fp);

    for(i=0;i<m;i++)                ///选择排序
    {
        k=i;
        for(j=i;j<m;j++)
        {
            if(stu[j].total>stu[k].total)
            {
                temp=stu[j];
                stu[j]=stu[k];
                stu[k]=temp;
            }
        }
        if(k!=i)
            stu[i]=stu[k];
    }

    printf(TITLEBAR);
    for(i=0; i<m; i++)
        printf(FORMAT,DATA);
}


int main()
{
    char n;
    while(1)
    {
        system("cls");
        menu();
        scanf("%c",&n);
        switch(n)
        {
        case '1':
            system("cls");
            enter();
            system("pause");
            break;
        case '2':
            system("cls");
            print();
            system("pause");
            break;
        case '3':
            system("cls");
            search();
            system("pause");
            break;
        case '4':
            system("cls");
            insert();
            system("pause");
            break;
        case '5':
            system("cls");
            del();
            system("pause");
            break;
        case '6':
            system("cls");
            gotoxy(25,10);
            printf("鉴于为用户着想，不用每次修改数据时都要存取，此函数已写入各个函数内部。\n");
            system("pause");
            break;
        case '7':
            system("cls");
            gotoxy(25,10);
            printf("鉴于为用户着想，不用每次修改数据时都要存取，此函数已写入各个函数内部。\n");
            system("pause");
            break;
        case '8':
            system("cls");
            sort();
            system("pause");
            break;
        case '9':
            system("cls");
            modify();
            system("pause");
            break;
        case '0':
            exit(0);
            break;
        default:
            break;
        }
    }

    return 0;
}
