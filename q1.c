#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct student
{
    int roll;
    char name[30];
    int branch_id;
    float cgpa;
    struct student *next;
};
struct university
{
    int university_id;
    char university_name[100];
    char university_location[100];
    int start;
    struct university *next;
};
struct branch
{
    int branch_id;
    int university_id;
    char branch_name[50];
    struct branch *next;
};
void create_student();
void read_file_student();
void traverse_student(struct student *);
void delete_student();
void update_student();
void create_university();
void read_file_university();
void traverse_university(struct university *);
void delete_university();
void update_university();
void create_branch();
void read_file_branch();
void traverse_branch(struct branch *);
void delete_branch();
void update_branch();
int unique_roll(int);
int unique_uni_id(int);
int unique_branch_id(int, int);
void branch_list();
void uppercase(char *);
void create_student()
{
    struct student *p;
    int roll, branch_id, temp;
    float cgpa;
    char name[30];
    p = (struct student *)malloc(sizeof(struct student));
    printf("Enter Student's Name: ");
    fgets(name, sizeof(name), stdin);
    gets(name);
    uppercase(name);
    printf("Enter Student's Roll no: ");
    scanf("%d", &roll);
    temp = unique_roll(roll);
    if (temp != -1)
    {
        printf("Enter Student's Branch ID: ");
        scanf("%d", &branch_id);
        printf("Enter Student's CGPA: ");
        scanf("%f", &cgpa);
        strcpy(p->name, name);
        p->roll = roll;
        p->branch_id = branch_id;
        p->cgpa = cgpa;
        p->next = NULL;
        FILE *fp_student;
        fp_student = fopen("student", "a");
        fwrite(p, sizeof(struct student), 1, fp_student);
        fclose(fp_student);
    }
}
void read_file_student()
{
    struct student s1, *head = NULL, *p, *temp;
    FILE *fp_student;
    fp_student = fopen("student", "rb");
    while (fread(&s1, sizeof(struct student), 1, fp_student))
    {
        p = (struct student *)malloc(sizeof(struct student));
        strcpy(p->name, s1.name);
        p->roll = s1.roll;
        p->branch_id = s1.branch_id;
        p->cgpa = s1.cgpa;
        if (head == NULL)
        {
            head = p;
            p->next = NULL;
        }
        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = p;
            p->next = NULL;
        }
    }
    fclose(fp_student);
    traverse_student(head);
}
void traverse_student(struct student *head)
{
    printf("NAME\t\t\tROLL NO.\tBRANCH ID\tCGPA\n");
    printf("-----------------------------------------------------------------\n");
    while (head != NULL)
    {
        printf("%-23s %-15d %-15d %.2f\t\n", head->name, head->roll, head->branch_id, head->cgpa);
        head = head->next;
    }
    printf("\n");
}
void delete_student()
{
    int num, flag = 0, count = 0;
    struct student s1;
    FILE *fp_student, *fp_temp;
    printf("Enter roll number of the student: ");
    scanf("%d", &num);
    fp_student = fopen("student", "rb");
    fp_temp = fopen("temp_student", "w");
    while (fread(&s1, sizeof(struct student), 1, fp_student))
    {
        if (num != s1.roll)
        {
            fwrite(&s1, sizeof(struct student), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_student", "a");
        }
        else
        {
            flag = 1;
        }
    }
    fclose(fp_student);
    fclose(fp_temp);
    if (flag != 0)
    {
        fp_temp = fopen("temp_student", "rb");
        fp_student = fopen("student", "w");
        while (fread(&s1, sizeof(struct student), 1, fp_temp))
        {
            if (count == 0)
            {
                fwrite(&s1, sizeof(struct student), 1, fp_student);
                fclose(fp_student);
                fp_student = fopen("student", "a");
            }
            else
            {
                fwrite(&s1, sizeof(struct student), 1, fp_student);
            }
            ++count;
        }
        fclose(fp_temp);
        fclose(fp_student);
    }
}
void update_student()
{
    float cgpa;
    char name[30];
    int roll, branch_id, num, flag = 0, count = 0, temp = 0;
    struct student s1, *p;
    FILE *fp_student, *fp_temp;
    printf("Enter roll number of the student: ");
    scanf("%d", &num);
    fp_student = fopen("student", "rb");
    fp_temp = fopen("temp_student", "w");
    while (fread(&s1, sizeof(struct student), 1, fp_student))
    {
        if (num == s1.roll)
        {
            flag = 1;
            printf("Enter Student's Roll no: ");
            scanf("%d", &roll);
            printf("Enter Student's Name: ");
            fgets(name, sizeof(name), stdin);
            gets(name);
            uppercase(name);
            printf("Enter Student's Branch ID: ");
            scanf("%d", &branch_id);
            printf("Enter Student's CGPA: ");
            scanf("%f", &cgpa);
            p = (struct student *)malloc(sizeof(struct student));
            strcpy(p->name, name);
            p->branch_id = branch_id;
            p->cgpa = cgpa;
            p->roll = roll;
            fwrite(p, sizeof(struct student), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_student", "a");
        }
        else
        {
            fwrite(&s1, sizeof(struct student), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_student", "a");
        }
    }
    fclose(fp_temp);
    fclose(fp_student);
    fp_temp = fopen("temp_student", "rb");
    fp_student = fopen("student", "w");
    if (flag != 0)
    {
        while (fread(&s1, sizeof(struct student), 1, fp_temp))
        {
            if (count == 0)
            {
                fwrite(&s1, sizeof(struct student), 1, fp_student);
                fclose(fp_student);
                fp_student = fopen("student", "a");
            }
            else
            {
                fwrite(&s1, sizeof(struct student), 1, fp_student);
            }
            ++count;
        }
    }
    fclose(fp_student);
    fclose(fp_temp);
}
void create_university()
{
    struct university *p;
    int id, yos, temp;
    char name[50];
    p = (struct university *)malloc(sizeof(struct student));
    printf("Enter University's Name: ");
    fgets(name, sizeof(name), stdin);
    gets(name);
    uppercase(name);
    printf("Enter University's ID: ");
    scanf("%d", &id);
    temp = unique_uni_id(id);
    if (temp != -1)
    {
        printf("Enter University's Location: ");
        fgets(p->university_location, sizeof(p->university_location), stdin);
        gets(p->university_location);
        printf("Enter University's Year of Start: ");
        scanf("%d", &yos);
        strcpy(p->university_name, name);
        p->university_id = id;
        p->start = yos;
        p->next = NULL;
        FILE *fp_university;
        fp_university = fopen("university_info", "a");
        fwrite(p, sizeof(struct university), 1, fp_university);
        fclose(fp_university);
    }
}
void read_file_university()
{
    struct university s1, *p, *temp, *head = NULL;
    FILE *fp_university;
    fp_university = fopen("university_info", "rb");
    while (fread(&s1, sizeof(struct university), 1, fp_university))
    {
        p = (struct university *)malloc(sizeof(struct university));
        strcpy(p->university_name, s1.university_name);
        strcpy(p->university_location, s1.university_location);
        p->university_id = s1.university_id;
        p->start = s1.start;
        if (head == NULL)
        {
            head = p;
            p->next = NULL;
        }
        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = p;
            p->next = NULL;
        }
    }
    traverse_university(head);
    fclose(fp_university);
}
void traverse_university(struct university *head)
{
    printf("UNIVERSITY NAME\t\t\tUNIVERSITY ID\t\tUNIVERSITY LOCATION\t\tYEAR OF START\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    while (head != NULL)
    {
        printf("%-31s %-23d %-31s %d\t\n", head->university_name, head->university_id, head->university_location, head->start);
        head = head->next;
    }
    printf("\n");
}
void delete_university()
{
    int num, flag = 0, count = 0;
    struct university s1;
    FILE *fp_university, *fp_temp;
    printf("Enter University ID: ");
    scanf("%d", &num);
    fp_university = fopen("university_info", "rb");
    fp_temp = fopen("temp_university", "w");
    while (fread(&s1, sizeof(struct university), 1, fp_university))
    {
        if (num != s1.university_id)
        {
            fwrite(&s1, sizeof(struct university), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_university", "a");
        }
        else
        {
            flag = 1;
        }
    }
    fclose(fp_university);
    fclose(fp_temp);
    if (flag != 0)
    {
        fp_temp = fopen("temp_university", "rb");
        fp_university = fopen("university_info", "w");
        while (fread(&s1, sizeof(struct university), 1, fp_temp))
        {
            if (count == 0)
            {
                fwrite(&s1, sizeof(struct university), 1, fp_university);
                fclose(fp_university);
                fp_university = fopen("university_info", "a");
            }
            else
            {
                fwrite(&s1, sizeof(struct university), 1, fp_university);
            }
            count++;
        }
        fclose(fp_temp);
        fclose(fp_university);
    }
}
void update_university()
{
    int id, start;
    char name[100], location[100];
    int flag = 0, count = 0, temp = 0;
    struct university s1, *p;
    FILE *fp_university, *fp_temp;
    printf("Enter University ID: ");
    scanf("%d", &id);
    fp_university = fopen("university_info", "rb");
    fp_temp = fopen("temp_university", "w");
    while (fread(&s1, sizeof(struct university), 1, fp_university))
    {
        if (id == s1.university_id)
        {
            flag = 1;
            printf("Enter University ID: ");
            scanf("%d", &id);
            printf("Enter University Name: ");
            fgets(name, sizeof(name), stdin);
            gets(name);
            uppercase(name);
            printf("Enter University's year of start: ");
            scanf("%d", &start);
            printf("Enter University's Location: ");
            fgets(location, sizeof(location), stdin);
            gets(location);
            p = (struct university *)malloc(sizeof(struct university));
            strcpy(p->university_name, name);
            strcpy(p->university_location, location);
            p->university_id = id;
            p->university_id = id;
            p->start = start;
            fwrite(p, sizeof(struct university), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_university", "a");
        }
        else
        {
            fwrite(&s1, sizeof(struct university), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_university", "a");
        }
    }
    fclose(fp_temp);
    fclose(fp_university);
    fp_temp = fopen("temp_university", "rb");
    fp_university = fopen("university_info", "w");
    if (flag != 0)
    {
        while (fread(&s1, sizeof(struct university), 1, fp_temp))
        {
            if (count == 0)
            {
                fwrite(&s1, sizeof(struct university), 1, fp_university);
                fclose(fp_university);
                fp_university = fopen("university_info", "a");
            }
            else
            {
                fwrite(&s1, sizeof(struct university), 1, fp_university);
            }
            ++count;
        }
    }
    fclose(fp_university);
    fclose(fp_temp);
}
void create_branch()
{
    struct branch *p;
    int university, branch, temp;
    char name[30];
    p = (struct branch *)malloc(sizeof(struct branch));
    printf("Enter Branch's Name: ");
    fgets(name, sizeof(name), stdin);
    gets(name);
    uppercase(name);
    printf("Enter Branch's ID: ");
    scanf("%d", &branch);
    printf("Enter University's ID: ");
    scanf("%d", &university);
    temp = unique_branch_id(branch, university);
    if (temp != -1)
    {
        strcpy(p->branch_name, name);
        p->branch_id = branch;
        p->university_id = university;
        p->next = NULL;
        FILE *fp_branch;
        fp_branch = fopen("branch_info", "a");
        fwrite(p, sizeof(struct branch), 1, fp_branch);
        fclose(fp_branch);
    }
}
void read_file_branch()
{
    struct branch s1, *head = NULL, *p, *temp;
    FILE *fp_branch;
    fp_branch = fopen("branch_info", "rb");
    while (fread(&s1, sizeof(struct branch), 1, fp_branch))
    {
        p = (struct branch *)malloc(sizeof(struct branch));
        strcpy(p->branch_name, s1.branch_name);
        p->branch_id = s1.branch_id;
        p->university_id = s1.university_id;
        if (head == NULL)
        {
            head = p;
            p->next = NULL;
        }
        else
        {
            temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = p;
            p->next = NULL;
        }
    }
    traverse_branch(head);
    fclose(fp_branch);
}
void traverse_branch(struct branch *head)
{
    printf("UNIVERSITY ID\t\tBRANCH NAME\t\tBRANCH ID\n");
    printf("-----------------------------------------------------------\n");
    while (head != NULL)
    {
        printf("%-23d %-23s %d\t\n", head->university_id, head->branch_name, head->branch_id);
        head = head->next;
    }
    printf("\n");
}
void delete_branch()
{
    int num, flag = 0, count = 0;
    struct branch s1;
    FILE *fp_branch, *fp_temp;
    printf("Enter Branch ID: ");
    scanf("%d", &num);
    fp_branch = fopen("branch_info", "rb");
    fp_temp = fopen("temp_branch", "w");
    while (fread(&s1, sizeof(struct branch), 1, fp_branch))
    {
        if (num != s1.branch_id)
        {
            fwrite(&s1, sizeof(struct branch), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_branch", "a");
        }
        else
        {
            flag = 1;
        }
    }
    fclose(fp_branch);
    fclose(fp_temp);
    if (flag != 0)
    {
        fp_temp = fopen("temp_branch", "rb");
        fp_branch = fopen("branch_info", "w");
        while (fread(&s1, sizeof(struct branch), 1, fp_temp))
        {
            if (count == 0)
            {
                fwrite(&s1, sizeof(struct branch), 1, fp_branch);
                fclose(fp_branch);
                fp_branch = fopen("branch_info", "a");
            }
            else
            {
                fwrite(&s1, sizeof(struct branch), 1, fp_branch);
            }
            count++;
        }
        fclose(fp_temp);
        fclose(fp_branch);
    }
}
void update_branch()
{
    int id, uni;
    char name[50];
    int flag = 0, count = 0, temp = 0;
    struct branch s1, *p;
    FILE *fp_branch, *fp_temp;
    printf("Enter Branch ID: ");
    scanf("%d", &id);
    fp_branch = fopen("branch_info", "rb");
    fp_temp = fopen("temp_branch", "w");
    while (fread(&s1, sizeof(struct branch), 1, fp_branch))
    {
        if (id == s1.branch_id)
        {
            flag = 1;
            printf("Enter Branch ID: ");
            scanf("%d", &id);
            printf("Enter Branch Name: ");
            fgets(name, sizeof(name), stdin);
            gets(name);
            uppercase(name);
            printf("Enter University's ID: ");
            scanf("%d", &uni);
            p = (struct branch *)malloc(sizeof(struct branch));
            strcpy(p->branch_name, name);
            p->branch_id = id;
            p->university_id = uni;
            fwrite(p, sizeof(struct branch), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_branch", "a");
        }
        else
        {
            fwrite(&s1, sizeof(struct branch), 1, fp_temp);
            fclose(fp_temp);
            fp_temp = fopen("temp_branch", "a");
        }
    }
    fclose(fp_temp);
    fclose(fp_branch);
    fp_temp = fopen("temp_branch", "rb");
    fp_branch = fopen("branch_info", "w");
    if (flag != 0)
    {
        while (fread(&s1, sizeof(struct branch), 1, fp_temp))
        {
            if (count == 0)
            {
                fwrite(&s1, sizeof(struct branch), 1, fp_branch);
                fclose(fp_branch);
                fp_branch = fopen("branch_info", "a");
            }
            else
            {
                fwrite(&s1, sizeof(struct branch), 1, fp_branch);
            }
            ++count;
        }
    }
    fclose(fp_branch);
    fclose(fp_temp);
}
int unique_roll(int num)
{
    struct student s1;
    FILE *fp_student;
    fp_student = fopen("student", "rb");
    while (fread(&s1, sizeof(struct student), 1, fp_student))
    {
        if (s1.roll == num)
        {
            fclose(fp_student);
            printf("Entered ROLL NUMBER already in use\n");
            return -1;
            break;
        }
    }
}
int unique_uni_id(int num)
{
    struct university s1;
    FILE *fp_university;
    fp_university = fopen("university_info", "rb");
    while (fread(&s1, sizeof(struct university), 1, fp_university))
    {
        if (s1.university_id == num)
        {
            fclose(fp_university);
            printf("Entered UNIVERSITY ID already in use\n");
            return -1;
            break;
        }
    }
}
int unique_branch_id(int num, int numb)
{
    struct branch s1;
    FILE *fp_branch;
    fp_branch = fopen("branch_info", "rb");
    while (fread(&s1, sizeof(struct branch), 1, fp_branch))
    {
        if (s1.branch_id == num && s1.university_id == numb)
        {
            fclose(fp_branch);
            printf("Entered BRANCH ID already in use for same university\n");
            return -1;
            break;
        }
    }
}
void branch_list()
{
    struct university s1;
    struct branch s2;
    char name[30];
    int num, temp;
    printf("Enter University's Name: ");
    fgets(name, sizeof(name), stdin);
    gets(name);
    FILE *fp_university, *fp_branch;
    fp_university = fopen("university_info", "rb");
    while (fread(&s1, sizeof(struct university), 1, fp_university))
    {
        temp = strcmp(name, s1.university_name);
        if (temp == 0)
        {
            fclose(fp_university);
            num = s1.university_id;
            break;
        }
    }
    fp_branch = fopen("branch_info", "rb");
    while (fread(&s2, sizeof(struct branch), 1, fp_branch))
    {
        if (num == s2.university_id)
        {
            printf("%s\n", s2.branch_name);
        }
    }
    fclose(fp_branch);
}
void uppercase(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        str[i] = toupper(str[i]);
    }
}
int main()
{
    int n = 1, ch;
    while (n == 1)
    {
        printf("1. Add student\n2. Diplay Student List\n3. Add University\n4. Display University List\n5. Add Branch\n6. Display Branch List\n7. Search Branch List of a university\n8. Delete Student\n9. Delete University\n10. Delete Branch\n11. Update Student\n12. Update University\n13. Update Branch\n14. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            create_student();
            break;
        case 2:
            read_file_student();
            break;
        case 3:
            create_university();
            break;
        case 4:
            read_file_university();
            break;
        case 5:
            create_branch();
            break;
        case 6:
            read_file_branch();
            break;
        case 7:
            branch_list();
            break;
        case 8:
            delete_student();
            break;
        case 9:
            delete_university();
            break;
        case 10:
            delete_branch();
            break;
        case 11:
            update_student();
            break;
        case 12:
            update_university();
            break;
        case 13:
            update_branch();
            break;
        case 14:
            exit(0);
        }
        printf("Press 1 to continue || 0 to exit: ");
        scanf("%d", &n);
        if (n == 0)
        {
            exit(0);
        }
    }
    return 0;
}