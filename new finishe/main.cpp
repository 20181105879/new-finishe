#include <iostream>
#include <algorithm>
#include <cstring>
#include<fstream>
#define Student_number 5
#define Teacher_number 7
using namespace std;
long long i,j,k;
char output_headline[100]={"学号------名字--性别--学院---班级--平均分----号码"};
char show_headline1[250]={"学号---------------------姓名------性别---------------------学院-----------------------班级------分数-------2---------3---------4----------5---------6--------7-----------号码-------平均分\n"};
char Stuenden_headline[100];
char Teacher_headline[100];
//{"学号-------姓名------性别--学院---班级-------分数2--3--4--5--6--7-号码\n"};
//学生结构体（读）
struct Students1{
    char id[30];
    char name[30];
    char sex[20];
    char college[50];
    char st_class[30];
    long long phone;
    double sore[Teacher_number];
    double avg;
    double sum;
    
}student1[Student_number];
// 老师的结构体
struct Teachers{
    
    char name[30];
    char  id[30];
    double sore[Student_number];
    char sex[20];
    
}teacher[Teacher_number];


//给结构体排序
bool cmp( Students1  &p1,Students1 &p2)
{
    if(p1.avg>p2.avg)
    {
        return 1;
    }
    else if(p1.avg==p2.avg)
    {
        if(p1.name-p2.name>0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
    }
    else
    {
        return 0;
    }
}


int main()
{
    //读老师的数据
    FILE *p1=NULL;
    p1=fopen("/Users/s20181105879/Desktop/teacher.txt","r");
    // p1=fopen("teacher.txt","r");
    if(!p1)
    {
        printf("open fail\n");
        return 0;
    }
    fscanf(p1,"%s",Teacher_headline);
    for(i=0;i<Teacher_number;i++)
    {
        fscanf(p1,"%s %s",teacher[i].id,teacher[i].name);
        fscanf(p1,"%s",teacher[i].sex);
        for(j=0;j<Student_number;j++)
        {
            fscanf(p1,"%lf",&teacher[i].sore[j]);
        }
    }
    fclose(p1);
    
    
    
    //读学生数据
    FILE *fp=NULL;
    fp=fopen("/Users/s20181105879/Desktop/student.txt","r");
    //fp=fopen("student.txt","r");
    if(!fp)
    {
        printf("open fail\n");
        return 0;
    }
    fscanf(fp,"%s",Stuenden_headline);
    for(i=0;i<Student_number;i++)
    {
        fscanf(fp,"%s",student1[i].id);
        fscanf(fp,"%s",student1[i].name);
        fscanf(fp,"%s",student1[i].sex);
        fscanf(fp,"%s",student1[i].college);
        fscanf(fp,"%s",student1[i].st_class);
        fscanf(fp,"%lld",&student1[i].phone);
    }
    fclose(fp);
    
    
    //把裁判的打分复制给学生
    for(j=0;j<Student_number;j++)
    {
        for(k=0;k<Teacher_number;k++)
        {
            student1[j].sore[k]=teacher[k].sore[j];
        }
    }
    
    
    
    for(i=0;i<Student_number;i++)
    {
        sort(student1[i].sore,student1[i].sore+Teacher_number);//给七个分数排序
        student1[i].sum=0;
        
        for(j=1;j<Teacher_number-1;j++)
        {
            student1[i].sum+=student1[i].sore[j];
        }
        student1[i].avg=student1[i].sum/(Teacher_number-2);
    }
    
    
    //结构体排序
    sort(student1,student1+Student_number,cmp);
    
    
    
    //屏幕显示
    printf("%s\n",output_headline);
    for(i=0;i<Student_number;i++)
    {
        printf("rank %lld:\n",(i+1));
        printf("%-10s%-8s%-6s",student1[i].id,student1[i].name,student1[i].sex);
        printf("%-10s%-10s",student1[i].college,student1[i].st_class);
        printf("%-6.2f  %-10lld\n",student1[i].avg,student1[i].phone);
        printf("\n");
    }
    
    
    
    //输出文件显示
    FILE *pp=NULL;
    pp=fopen("/Users/s20181105879/Desktop/show.txt","w");
    //pp=fopen("show.txt","w");
    if(!pp)
    {
        printf("open false\n");
        return 0;
    }
    fprintf(pp,"%s",show_headline1);
    for(i=0;i<Student_number;i++)
    {
        fprintf(pp,"rank %4lld:\n",i+1);
        fprintf(pp,"%-10s",student1[i].id);
        fprintf(pp,"%20s",student1[i].name);
        fprintf(pp,"%10s",student1[i].sex);
        fprintf(pp,"%30s",student1[i].college);
        fprintf(pp,"%30s",student1[i].st_class);
        for(int j=0;j<Teacher_number;j++)
        {
            fprintf(pp,"%10.2f",student1[i].sore[j]);
        }
        fprintf(pp,"%15lld",student1[i].phone);
        fprintf(pp,"%10.2f",student1[i].avg);
        fprintf(pp,"\n\n");
        
    }
    fclose(pp);
    return 0;
}




//学生表格
//学号------姓名---性别--学院----班级------号码
//2018110  邱健军  男    机械      机械工程  1008611
//2018111  二胖    女     医学院   护理学     1008612
//2018112  教授    男      计算机  飞机学     1008613
//2018113  蜗牛    人     鬼知道   你猜啊     1008614
//2018114  阳建波 男    计科院    软件工程  1008615
//老师表格
//编号--姓名--性别--1--2--3--4--5--6--7--8......
//110   张三    男    72 88 69 11 28
//111   李四    男   32 58 99 11 22
//112   王五    男   62 88 99 33 22
//113   赵六    男   72 88 79 11 62
//114   刘启    女   72 22 99 11 22
//115  李八    男    22 88 29 51 72
//116  何九   男     72 96 99 11 92


