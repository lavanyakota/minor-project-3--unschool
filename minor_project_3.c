#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int add();
int view();
int edit();
int dele();
struct record
{
    char time[6];
    char name[30];
    char place[25];
    char duration[10];
    char note[500];
};
int main()
{
    int choice;
    printf("\n*************************************\n");
    printf("**PASSWORD PROTECTED PERSONAL DIARY**");
    printf("\n*************************************\n");
    while(1)
    {
        printf("\n\t    MAIN MENU :\n");
        printf("\t*******************");
        printf("\nADD RECORD       [1]");
        printf("\nVIEW RECORD      [2]");
        printf("\nEDIT RECORD      [3]");
        printf("\nDELETE RECORD    [4]");
        printf("\nEXIT             [5]\n");
        printf("\nENTER YOUR CHOICE:");
        scanf("%d",&choice);
        while(choice!=5)
        {
            if(choice==1)
            {
                add();
                break;
            }
            else if(choice==2)
            {
                view();
                break;
            }
            else if(choice==3)
            {
                edit();
                break;
            }
            else if(choice==4)
            {
                dele();
                break;
            }
            else
            {
                printf("\nYOU HAVE ENTERED WRONG CHOICE..\n");
                printf("\nCHOOSE AGAIN..\n");
            }
        }
        if(choice==5)
        {
            printf("  ");
            break;
        }
    }
    return 0;
}
int add()
{
    FILE *fp;
    char another='y',time[20],new,temp;
    struct record a;
    char date[15];
    int option,d;
    printf("\n\t***********************\n");
    printf("\t**WELCOME TO ADD MENU**");
    printf("\n\t***********************\n");
    label1:
    printf("\n\n\tENTER DATE OF YOU RECORD;:[yyyy-mm-dd]:");
    scanf("%s",&date);
    fp=fopen(date,"ab+");
    if(fp==NULL)
    {
        fp=fopen(date,"wb+");
        if(fp==NULL)
        {
            printf("\nSYSTEM ERROR...");
            return;
        }
    }
    label2:
    while(another=='Y'||another=='y')
    {
        option=0;
        printf("\tENTER TIME:[hh:mm]:");
        scanf("%s",&time);
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(strcmp(a.time,time)==0)
            {
                printf("\n\tRECORD ALREADY EXIST.\n");
                option=1;
            }
        }
        if(option==0)
        {
            strcpy(a.time,time);
            printf("\tENTER NAME:");
            scanf("%s",&a.name);
            printf("\tENTER PLACE:");
            scanf("%s",&a.place);
            printf("\tENTER DURATION:");
            scanf("%s",&a.duration);
            printf("\tNOTE:");
            scanf("%c",&temp);
            scanf("%[^\n]",&a.note);
            fwrite(&a,sizeof(a),1,fp);
            printf("\n\nYOUR RECORD IS ADDED...\n");
        }
        printf("\n\tADD ANOTHER RECORD...(y/n)");
        scanf("%s",&another);
        if(another=='n')
          break;
        else if(another=='y')
        {
            printf("\n\tON THE SAME DATE OR ANOTHER:[1.same  2.another]:");
            scanf("%d",&d);
            if(d==1)
              goto label2;
            else if(d==2)
              goto label1;
        }
    }
    fclose(fp);
}
int view()
{
    FILE *fp2;
    struct record v;
    char time[6],select,date[15];
    int n;
    printf("\n\t************************\n");
    printf("\t**WELCOME TO VIEW MENU**");
    printf("\n\t************************\n");
    do
    {
        printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED:[yyyy-mm-dd]:");
        scanf("%s",&date);
        fp2=fopen(date,"rb");
        if(fp2==NULL)
        {
            printf("\nTHE RECORD DOES NOT EXIST...\n");
            return;
        }
        printf("\n\tHOW WOULD YOU LIKE TO VIEW:\n");
        printf("\n\t1.WHOLE RECORD OF THE DAY.");
        printf("\n\t2.RECORD OF FIX TIME.");
        printf("\n\t\tENTER YOUR CHOICE:");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
            {
                printf("\nTHE WHOLE RECORD FOR %s IS:\n",date);
                while(fread(&v,sizeof(v),1,fp2)==1)
                {
                    printf("\nTIME :%s",v.time);
                    printf("\nMEETING WITH :%s",v.name);
                    printf("\nMEETING AT :%s",v.place);
                    printf("\nDURATION :%s",v.duration);
                    printf("\nNOTE :%s",v.note);
                }
                break;
            }
            case 2:
            {
                printf("\nENTER TIME:[hh:mm]:");
                scanf("%s",&time);
                while(fread(&v,sizeof(v),1,fp2)==1)
                {
                    if(strcmp(v.time,time)==0)
                    {
                        printf("\nYOUR RECORD IS:\n");
                        printf("\nTIME :%s",v.time);
                        printf("\nMEETING WITH :%s",v.name);
                        printf("\nMEETING AT :%s",v.place);
                        printf("\nDURATION :%s",v.duration);
                        printf("\nNOTE :%s",v.note);
                    }
                }
                break;
            }
            default:
            {
                printf("\nYOU HAVE ENTERED WRONG CHOICE\n");
                break;
            }
        }
        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(y/n):");
        scanf("%s",&select);
    }while(select=='y'||select=='Y');
    fclose(fp2);
    return;
}
int edit()
{
    FILE *fp2;
    struct record v;
    char time[6],choice,date[15],temp;
    int num,count=0;
    printf("\n\t************************\n");
    printf("\t**WELCOME TO EDIT MENU**");
    printf("\n\t************************\n");
    do
    {
        printf("\nENTER THE DATE OF RECORD TO BE EDITED:[yyyy-mm-dd]:");
        scanf("%s",&date);
        printf("\nENTER TIME:[hh:mm]:");
        scanf("%s",&time);
        fp2=fopen(date,"rb+");
        if(fp2==NULL)
        {
            printf("\nRECORD DOES NOT EXIST:");
            return;
        }
        while(fread(&v,sizeof(v),1,fp2)==1)
        {
            if(strcmp(v.time,time)==0)
            {
                printf("\nYOUR OLD RECORD WAS :");
                printf("\nTIME :%s",v.time);
                printf("\nMEETING WITH :%s",v.name);
                printf("\nMEETING AT :%s",v.place);
                printf("\nDURATION :%s",v.duration);
                printf("\nNOTE :%s",v.note);
                label3:
                printf("\n\nWHAT WOULD YOU LIKE TO EDIT..:\n");
                printf("\n1.TIME.");
                printf("\n2.MEETING PERSON.");
                printf("\n3.MEETING PLACE.");
                printf("\n4.DURATION.");
                printf("\n5.NOTE.");
                printf("\n6.WHOLE RECORD.");
                printf("\n7.GO BACK TO MAIN MENU..");
                do
                {
                    printf("\n\tENTER YOUR CHOICE:");
                    scanf("%d",&num);
                    switch(num)
                    {
                        case 1:
                        {
                            printf("\n\tENTER NEW DATA:");
                            printf("\nNEW TIME[hh:mm]:");
                            scanf("%s",&v.time);
                            break;
                        }
                        case 2:
                        {
                            printf("\n\tENTER NEW DATA:");
                            printf("\nNEW MEETING PERSON:");
                            scanf("%s",&v.name);
                            break;
                        }
                        case 3:
                        {
                            printf("\n\tENTER NEW DATA:");
                            printf("\nNEW MEETING PLACE:");
                            scanf("%s",&v.place);
                            break;
                        }
                        case 4:
                        {
                            printf("\n\tENTER NEW DATA:");
                            printf("\nNEW DURATION:");
                            scanf("%s",&v.duration);
                            break;
                        }
                        case 5:
                        {
                            printf("\n\tENTER NEW DATA:");
                            printf("\nNEW NOTE:");
                            scanf("%c",&temp);
                            scanf("%[^\n]",&v.note);
                            break;
                        }
                        case 6:
                        {
                            printf("\n\tENTER NEW DATA:");
                            printf("\nNEW TIME[hh:mm]:");
                            scanf("%s",&v.time);
                            printf("\nNEW MEETING PERSON:");
                            scanf("%s",&v.name);
                            printf("\nNEW MEETING PLACE:");
                            scanf("%s",&v.place);
                            printf("\nNEW DURATION:");
                            scanf("%s",&v.duration);
                            printf("\nNEW NOTE:");
                            scanf("%c",&temp);
                            scanf("%[^\n]",&v.note);
                            break;
                        }
                        case 7:
                        {
                            return;
                            break;
                        }
                        default:
                        {
                            printf("\nYOU HAVE ENTERED WRONG CHOICE\n");
                            break;
                        }
                    }
                }while(num<1||num>8);
                fseek(fp2,-sizeof(v),SEEK_CUR);
                fwrite(&v,sizeof(v),1,fp2);
                fseek(fp2,-sizeof(v),SEEK_CUR);
                fread(&v,sizeof(v),1,fp2);
                choice=5;
                break;
            }
        }
        if(choice==5)
        {
            printf("\n\n\tEDITING COMPLETED....\n");
            printf("\nYOUR NEW RECORD WAS :");
            printf("\nTIME :%s",v.time);
            printf("\nMEETING WITH :%s",v.name);
            printf("\nMEETING AT :%s",v.place);
            printf("\nDURATION :%s",v.duration);
            printf("\nNOTE :%s",v.note);
            printf("\n\nWOULD YOU LIKE TO EDIT ANOTHER RECORD(y/n):");
            scanf("%s",&choice);
            count++;
            if(choice=='y')
              goto label3;
            else
              break;
        }
        else
        {
            printf("\nRECORD DOES NOT EXIST...");
            printf("\n\nWOULD YOU LIKE TO TRY AGAIN..(y/n):  ");
            scanf("%c",&choice);
        }
    }while(choice=='Y'||choice=='y');
    fclose(fp2);
    if(count==1)
    {
        printf("\n%d FILE IS EDITED..\n",count);
    }
    else
    {
        printf("\n%d FILES ARE EDITED..\n",count);
    }
}
int dele()
{
    FILE *fp,*fptr;
    struct record d;
    char date[15],another='y',time[10];
    int choice;
    printf("\n\t**************************\n");
    printf("\t**WELCOME TO DELETE MENU**");
    printf("\n\t**************************\n");
    while(another=='y')
    {
        printf("\n\tHOW WOULD YOU LIKE TO DELETE:\n");
        printf("\n\t1.DELETE WHOLE RECORD.");
        printf("\n\t2.DELETE A PARTICULAR RECORD BY TIME.");
        do
        {
            printf("\n\t\tENTER YOUR CHOICE:");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                {
                    printf("\nENTER THE DATE OF RECORD TO BE DELETED:[yyyy-mm-dd]:");
                    scanf("%s",&date);
                    fp=fopen(date,"wb");
                    if(fp==NULL)
                    {
                        printf("\n\nRECORD DOES NOT EXIST..");
                        return;
                    }
                    fclose(fp);
                    remove(date);
                    printf("\n\n\tDELETED SUCCESSFULLY...");
                    break;
                }
                case 2:
                {
                    printf("\nENTER THE DATE OF RECORD:[yyyy-mm-dd]:");
                    scanf("%s",&date);
                    fp=fopen(date,"rb");
                    if(fp==NULL)
                    {
                        printf("\n\nRECORD DOES NOT EXIST..");
                        return;
                    }
                    fptr=fopen("temp","wb");
                    if(fptr==NULL)
                    {
                        printf("\nSYSTEM ERROR...");
                        return;
                    }
                    printf("\nENTER THE TIME OF RECORD TO BE DELETED:[yyyy-mm-dd]:");
                    scanf("%s",&time);
                    while(fread(&d,sizeof(d),1,fp)==1)
                    {
                        if(strcmp(d.time,time)!=0)
                        fwrite(&d,sizeof(d),1,fptr);
                    }
                    fclose(fp);
                    fclose(fptr);
                    remove(date);
                    rename("temp",date);
                    printf("\n\nDELETED SUCCESFULLY...");
                    break;
                }
                default:
                {
                    printf("\nYOU HAVE ENTERED WRONG CHOICE\n");
                    break;
                }
            }
        }while(choice<1||choice>2);
        printf("\n\nWOULD YOU LIKE TO EDIT ANOTHER RECORD(y/n):");
        scanf("%s",&another);
    }
}