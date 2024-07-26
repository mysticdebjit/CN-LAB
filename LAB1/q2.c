#include <stdio.h>
#include <string.h>

struct dob
{
    int day;
    int month;
    int year;
};

struct student_info
{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

void call_by_value(struct student_info s)
{
    printf("Roll No: %d\n", s.roll_no);
    printf("Name: %s\n", s.name);
    printf("CGPA: %.2f\n", s.CGPA);
    printf("DOB: %d-%d-%d\n", s.age.day, s.age.month, s.age.year);
}

void call_by_address(struct student_info *s)
{
    printf("Roll No: %d\n", s->roll_no);
    printf("Name: %s\n", s->name);
    printf("CGPA: %.2f\n", s->CGPA);
    printf("DOB: %d-%d-%d\n", s->age.day, s->age.month, s->age.year);
}

int main(void)
{
    struct student_info s1;
    s1.roll_no = 1;
    strcpy(s1.name, "John Doe");
    s1.CGPA = 9.5;
    s1.age.day = 1;
    s1.age.month = 1;
    s1.age.year = 2000;

    call_by_value(s1);
    call_by_address(&s1);

    return 0;
}

