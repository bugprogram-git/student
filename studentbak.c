#include <stdio.h>
#include <stdlib.h>
typedef struct tmp
{
    int id;
    char name[5];
    char sex[3];
    int age;
    int chinese;
    int math;
    int english;
    int total;
} student;
typedef struct tmp1
{
    student data;
    struct tmp1 *lnext;
    struct tmp1 *rnext;
} linklist;
typedef struct tmp2
{
    linklist *key;
    struct tmp2 *next;
} linklist_tmp;
linklist *head = NULL;
double avg_chinese, avg_math, avg_english, avg_total;
void menu() //定义菜单栏函数
{
    printf("1.display all student info");
    printf("\n2.display all student order by student's total score");
    printf("\n3.insert new student ");
    printf("\n4.update student info");
    printf("\n5.delete student info");
    printf("\n6.search student info");
    printf("\n7.save student info");
    printf("\n8.load student info file");
    printf("\n9.exit this system");
    return;
}
void display(linklist *tmp) //显示学生信息函数
{
    printf("%-4d\t", tmp->data.id);
    printf("%-5s\t", tmp->data.name);
    printf("%-3s\t", tmp->data.sex);
    printf("%-7d\t", tmp->data.chinese);
    printf("%-4d\t", tmp->data.math);
    printf("%-7d\t", tmp->data.english);
    printf("%-5d\t", tmp->data.total);
    return;
}
linklist *search_student_info_ptr(int id) //定义检索函数,返回节点指针或NULL
{
    linklist *tmp = head;
    if (head == NULL)
        return NULL;
    while (1)
    {
        if (tmp->data.id == id)
            return tmp;
        else
        {
            if (tmp->rnext == NULL)
                return NULL;
            else
                tmp = tmp->rnext;
        }
    }
}
void output_line() //打印横线
{
    int a;
    for (a = 1; a <= 63; a++)
        printf("-");
    putchar('\n');
}
void display_all_student_info() //显示所有学生信息函数
{
    double total_chinese = 0, total_math = 0, total_english = 0, total_total = 0;
    int i = 0;
    linklist *tmp = head;
    if (head == NULL)
    {
        printf("linklist is empty\n");
        return;
    }
    printf("id  \tname \tsex\tchinese\tmath\tenglish\ttotal\t\n");
    int a;
    for (a = 1; a <= 63; a++)
        printf("-");
    putchar('\n');
    while (1)
    {
        total_chinese += tmp->data.chinese;
        total_math += tmp->data.math;
        total_english += tmp->data.english;
        total_total += tmp->data.total;
        display(tmp);
        putchar('\n');
        output_line();
        i++;
        if (tmp->rnext != NULL)
            tmp = tmp->rnext;
        else
        {
            i = (double)(i);
            avg_chinese = total_chinese / i;
            avg_math = total_math / i;
            avg_english = total_english / i;
            avg_total = total_total / i;
            printf("avg  \t    \t   \t%-7.3f\t%-4.3f\t%-7.3f\t%-5.3f  \t\n", avg_chinese, avg_math, avg_english, avg_total);
            printf("all student info is print complete!\n");
            return;
        }
    }
}
linklist *input_student_info() //定义输入函数,返回该节点的指针
{
    linklist *tmp = (linklist *)malloc(sizeof(linklist));
    printf("please input student id:");
    scanf("%d", &tmp->data.id);
    if (search_student_info_ptr(tmp->data.id) != NULL)
    {
        printf("this student is exist\n");
        return NULL;
    }
    printf("please input student name:");
    scanf("%s", &tmp->data.name);
    printf("please input student sex:");
    scanf("%s", &tmp->data.sex);
    printf("please input student chinese:");
    scanf("%d", &tmp->data.chinese);
    printf("please input student math score:");
    scanf("%d", &tmp->data.math);
    printf("please input student english score:");
    scanf("%d", &tmp->data.english);
    tmp->lnext = NULL;
    tmp->rnext = NULL;
    tmp->data.total = tmp->data.chinese + tmp->data.math + tmp->data.english;
    return tmp;
}
void sort_student_info_display() //以总分成绩为根据,根据排名显示学生信息
{
    linklist_tmp *head_tmp = NULL, *end_tmp = NULL;
    linklist *tmp = head;
    if (tmp == NULL)
    {
        printf("linklist is empty!\n");
        return;
    } //创建指针链表,用于交换指针对学生信息进行排序
    while (tmp != NULL)
    {
        linklist_tmp *node_tmp = (linklist_tmp *)malloc(sizeof(linklist_tmp));
        node_tmp->key = tmp;
        if (head_tmp == NULL)
        {
            head_tmp = node_tmp;
            end_tmp = head_tmp;
            node_tmp->next = NULL;
            tmp = tmp->rnext;
            continue;
        }
        node_tmp->next = NULL;
        end_tmp->next = node_tmp;
        end_tmp = node_tmp;
        tmp = tmp->rnext;
    }
    linklist_tmp *tmp2 = head_tmp;
    while (tmp2->next != NULL)
    {
        linklist_tmp *tmp1 = tmp2;
        while (tmp1->next != NULL)
        {
            linklist *trash;
            if (tmp1->key->data.total < tmp1->next->key->data.total)
            {
                trash = tmp1->key;
                tmp1->key = tmp1->next->key;
                tmp1->next->key = trash;
            }
            tmp1 = tmp1->next;
        }
        tmp2 = tmp2->next;
    } //指针链表冒泡排序
    linklist_tmp *tmp3 = head_tmp;
    printf("id  \tname \tsex\tchinese\tmath\tenglish\ttotal\trank\n");
    output_line();
    int rank = 1;
    while (tmp3 != NULL) //遍历二级指针链表,循环输出学生信息
    {
        display(tmp3->key);
        printf("%d", rank);
        rank++;
        putchar('\n');
        output_line();
        tmp3 = tmp3->next;
    }
    return;
}
void insert_student_info() //插入学生信息函数
{
    int a, b;
    printf("please input do you want to add the students count:");
    scanf("%d", &a);
    for (b = 1; b <= a; b++)
    {
        printf("\nplease input the %d student info\n", b);
        linklist *tmp = input_student_info();
        if (tmp == NULL)
            return;
        if (head == NULL)
        {
            head = tmp;
        }
        else
        {
            linklist *tmp2 = head;
            while (tmp2->rnext != NULL)
            {
                tmp2 = tmp2->rnext;
            } //遍历链表,找出尾部指针
            tmp2->rnext = tmp;
            tmp->lnext = tmp2;
        }
    }
    printf("successful!\n");
    return;
}
void search_student_info() //定义查找函数
{
    int id;
    printf("please input student's id that you want to search:");
    scanf("%d", &id);
    linklist *tmp = search_student_info_ptr(id);
    if (tmp != NULL)
    {
        printf("id  \tname \tsex\tchinese\tmath\tenglish\ttotal\t");
        putchar('\n');
        output_line();
        display(tmp);
        putchar('\n');
        output_line();
        return;
    }
    else
    {
        printf("\nthis student info is not exist!");
        return;
    }
}
void update_student_info() //定义更新函数
{
    int id;
    printf("please input this student's id that you want to update:");
    scanf("%d", &id);
    linklist *tmp = search_student_info_ptr(id);
    if (tmp == NULL)
    {
        printf("this student is not  exist!");
        return;
    }
    else
    {
        printf("this student's info current is this:\n");
        printf("id  \tname \tsex\tchinese\tmath\tenglish\ttotal\t\n");
        display(tmp);
        putchar('\n');
        output_line();
        while (1)
        {
            char choice;
            printf("\ndo you want to update this student?(Y/N):");
            getchar();
            scanf("%c", &choice);
            if (choice == 'Y')
            {
                linklist *tmp2 = input_student_info();
                if (tmp->lnext == NULL && tmp->rnext == NULL)
                {
                    free(tmp);
                    head = tmp2;
                }
                else
                {
                    if (tmp->lnext == NULL && tmp->rnext != NULL)
                    {
                        tmp->rnext->lnext = tmp2;
                        head = tmp2;
                        free(tmp);
                    }
                    else
                    {
                        if (tmp->lnext != NULL && tmp->rnext == NULL)
                        {
                            tmp->lnext->rnext = tmp2;
                            free(tmp);
                        }
                        else
                        {
                            tmp2->lnext = tmp->lnext;
                            tmp2->rnext = tmp->rnext;
                            free(tmp);
                        }
                    }

                    printf("update successful!");
                    return;
                }
            }
            else
            {
                if (choice == 'N')
                {
                    printf("\ncancel to update!");
                    return;
                }
                else
                    continue;
            }
        }
    }
}
void delete_student_info() //定义删除函数
{
    int a;
    printf("please input the student that you want to delete student:");
    scanf("%d", &a);
    linklist *tmp = search_student_info_ptr(a);
    if (tmp == NULL)
    {
        printf("this student is not exist!");
        return;
    }
    else
    {
        printf("this student's info current is this:\n");
        output_line();
        printf("id  \tname \tsex\tchinese\tmath\tenglish\ttotal\t\n");
        display(tmp);
        getchar();
        while (1)
        {
            printf("\ndo you want to comfirm delete this student info?(Y/N):");
            char choice;
            scanf("%d", &choice);
            if (choice == 1)
            {
                if (tmp->lnext == NULL && tmp->rnext == NULL)
                {
                    free(tmp);
                    head = NULL;
                }
                else
                {
                    if (tmp->lnext == NULL && tmp->rnext != NULL)
                    {
                        tmp->rnext->lnext == NULL;
                        head = tmp->rnext;
                        free(tmp);
                    }
                    else
                    {
                        if (tmp->lnext != NULL && tmp->rnext == NULL)
                        {
                            tmp->lnext->rnext == NULL;
                            free(tmp);
                        }
                        else
                        {
                            tmp->lnext->rnext = tmp->rnext;
                            tmp->rnext->lnext = tmp->lnext;
                            free(tmp);
                        }
                    }
                }
                printf("delete successful\n");
                return;
            }
            else
            {
                if (choice == 2)
                {
                    printf("cancel delete!");
                    return;
                }
                else
                {
                    printf("\nyou input is fail!please retry input!\n");
                    continue;
                }
            }
        }
    }
}
void save() //保存学生信息函数
{
    linklist *tmp = head;
    FILE *fp = fopen("student", "wb");
    if (fp == NULL)
    {
        printf("error!");
        return;
    }
    while (tmp != NULL)
    {
        fwrite(tmp, sizeof(linklist), 1, fp);
        tmp = tmp->rnext;
    }
    return;
}
void load() //加载数据库文件函数
{
    linklist *tmp = head;
    FILE *fp = fopen("student", "rb");
    if (fp == NULL)
    {
        printf("open the file is fail!\n");
        return;
    }
    linklist *end = NULL;
    while (!feof(fp))
    {
        linklist *tmp = (linklist *)malloc(sizeof(linklist));
        tmp->rnext = NULL;
        if (fread(tmp, sizeof(linklist), 1, fp) < 1)
            continue;
        if (head == NULL)
        {
            tmp->lnext = NULL;
            tmp->rnext = NULL;
            head = tmp;
            end = tmp;
            continue;
        }
        end->rnext = tmp;
        tmp->lnext = end;
        end = tmp;
    }
    return;
}
int main()
{
    printf("%d", sizeof(linklist));
    putchar('\n');
    while (1)
    {
        menu();
        int answer;
        printf("\nplease input your select:");
        scanf("%d", &answer);
        switch (answer)
        {
        case 1:
            display_all_student_info();
            break;
        case 2:
            sort_student_info_display();
            break;
        case 3:
            insert_student_info();
            break;
        case 4:
            update_student_info();
            break;
        case 5:
            delete_student_info();
            break;
        case 6:
            search_student_info();
            break;
        case 7:
            save();
            break;
        case 8:
            load();
            break;
        case 9:
            printf("exit");
            return 0;
        default:
            printf("your input is fail!\n");
            continue;
        }
    }
}
