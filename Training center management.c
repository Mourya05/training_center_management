#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct StudentInfo
{
    char ID[10];
    char Name[20];
    char Email[30];
    char Phone[20];
    int  NumberOfCourse;
};

struct CourseInfo
{
    char StudentID[10];
    char Code[10];
    char Name[20];
};

struct Course
{
    char courseCode[10];
    char courseName[50];
    int credits;
};

# define MAX_COURSES 20


struct StudentInfo Students[100];
struct CourseInfo Courses[500];
struct Course courses[MAX_COURSES];

// some global variables
int i,j;
int TotalStudents = 0;
int TotalCourse = 0;
int numCourses=0;
char StudentID[10];
char courseCode[10];
FILE *AllStudents;
FILE *AllCourses;
FILE *ExistingAllStudents;
FILE *TempAllStudents;
FILE *ExistingAllCourses;
FILE *TempAllCourses;
// end

bool IsRunning = true;
void Menu();
void AddNewStudent();
void ShowAllStudents();
int  SearchStudent(char StudentID[10]);
void EditStudent(int StudentFoundIndex);
void DeleteStudent(int StudentIndex);
void DeleteAllStudents();
void AddNewCourse();
void ShowAllCourses();
int  SearchCourse(char courseCode[10]);
void EditCourse(int courseIndex);
void DeleteCourse(int courseIndex);
void DeleteAllCourses();
int  IsAlreadyExists(char GivenLine[30],char InfoType, char StudentID[300]);
void ErrorAndRestart(char *Error[100]);
void DeleteCourseByIndex(int CourseIndex);
void DeleteStudentByIndex(int CourseIndex);
void UserGuideline();
void AboutUs();
void GoBackOrExit();
void ExitProject();
void DataSeed();

int main()
{
    DataSeed(); // you can comment this line if not want dummy data

    while(IsRunning)
    {
        Menu();
        int Option;
        scanf("%d",&Option);
        switch(Option)
        {
        case 0:
            IsRunning = false;
            ExitProject();
            break;
        case 1:
            system("cls");
            printf("\n\t\t **** \\\\Add A New Student// ****\n\n");
            AddNewStudent();
            GoBackOrExit();
            break;
        case 2:
            system("cls");
            printf("\n\t\t **** \\\\All Students// ****\n\n");
            ShowAllStudents();
            GoBackOrExit();
            break;
        case 3:
        {
            system("cls");
            printf("\n\t\t **** \\\\Search Students// ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int IsFound = SearchStudent(StudentID);
            if(IsFound<0)
            {
                printf(" No Student Found\n\n");
            }
            printf("\n");
            GoBackOrExit();
            break;
        }
        case 4:
            system("cls");
            printf("\n\t\t **** \\\\Edit a Student// ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int StudentFoundIndex = SearchStudent(StudentID);

            if(StudentFoundIndex>=0)
            {
                EditStudent(StudentFoundIndex);
            }
            else
            {
                printf(" No Student Found\n\n");
            }
            GoBackOrExit();
            break;
        case 5:
            system("cls");
            printf("\n\t\t **** \\\\Delete a Student// ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);

            int DeleteStudentFoundIndex = SearchStudent(StudentID);

            if(DeleteStudentFoundIndex>=0)
            {
                char Sure = 'N';
                getchar();
                printf("\n\n");
                printf(" Are you sure want to delete this student? (Y/N): ");
                scanf("%c",&Sure);

                if(Sure == 'Y' || Sure == 'y')
                {
                    DeleteStudent(DeleteStudentFoundIndex);
                }
                else
                {
                    printf(" Your Data is Safe.\n\n");
                    GoBackOrExit();
                }

            }
            else
            {
                printf(" No Student Found\n\n");
                GoBackOrExit();
            }

            break;
        case 6:
        {
            char Sure = 'N';
            getchar();
            system("cls");
            printf("\n\t\t **** \\\\Delete ALL Students// ****\n\n");

            printf(" Are you sure want to delete all the students? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y')
            {
                DeleteAllStudents();
            }
            else
            {
                printf(" Your Data is Safe.\n\n");
                GoBackOrExit();
            }
            break;
        }

        case 7:
            system("cls");
            printf("\n\t\t **** \\\\Add A New Course// ****\n\n");
            AddNewCourse();
            GoBackOrExit();
            break;
        case 8:
            system("cls");
            printf("\n\t\t **** \\\\All Courses// ****\n\n");
            ShowAllCourses();
            GoBackOrExit();
            break;
        case 9:
        {
            system("cls");
            printf("\n\t\t **** \\\\Search Course// ****\n\n");
            printf(" Enter The Course Code: ");
            scanf("%s",courseCode);
            int IsFound = SearchCourse(courseCode);
            if(IsFound<0)
            {
                printf(" No Course Found\n\n");
            }
            else
            {
                printf("Course available");
            }
            
            printf("\n");
            GoBackOrExit();
            break;
        }
        case 10:
            system("cls");
            printf("\n\t\t **** \\\\Edit a Course// ****\n\n");
            printf(" Enter The Course Code: ");
            scanf("%s",courseCode);
            int courseIndex = SearchCourse(courseCode);

            if(courseIndex>=0)
            {
                EditCourse(courseIndex);
            }
            else
            {
                printf(" No Course Found\n\n");
            }
            GoBackOrExit();
            break;
        case 11:
            system("cls");
            printf("\n\t\t **** \\\\Delete a Course// ****\n\n");
            printf(" Enter The Course Code: ");
            scanf("%s",courseCode);

            int DeletecourseIndex = SearchCourse(courseCode);

            if(DeletecourseIndex>=0)
            {
                char Sure = 'N';
                getchar();
                printf("\n\n");
                printf(" Are you sure want to delete this course? (Y/N): ");
                scanf("%c",&Sure);

                if(Sure == 'Y' || Sure == 'y')
                {
                    DeleteCourse(DeletecourseIndex);
                }
                else
                {
                    printf(" Your Data is Safe.\n\n");
                    GoBackOrExit();
                }

            }
            else
            {
                printf(" No Student Found\n\n");
                GoBackOrExit();
            }

            break;
        case 12:
        {
            char Sure = 'N';
            getchar();
            system("cls");
            printf("\n\t\t **** \\\\Delete ALL Courses// ****\n\n");

            printf(" Are you sure want to delete all the courses? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y')
            {
                DeleteAllCourses();
            }
            else
            {
                printf(" Your Data is Safe.\n\n");
                GoBackOrExit();
            }
            break;
        }

        case 13:
            system("cls");
            break;
        case 14:
            system("cls");
            UserGuideline();
            GoBackOrExit();
            break;
        case 15:
            system("cls");
            AboutUs();
            GoBackOrExit();
            break;
        default:
            ExitProject();
            break;
        }
    }

    return 0;
} // end main function

void Menu()
{
    printf("\n\n\t***Welcome to Team 7's Training Center***\n\n");
    printf("\t\t\tOur services\n");
    printf("\t\t==========================\n");
    printf("\t\t1. Add A New student.\n");
    printf("\t\t2. Show All students.\n");
    printf("\t\t3. Search A student.\n");
    printf("\t\t4. Edit A student.\n");
    printf("\t\t5. Delete A student.\n");
    printf("\t\t6. Delete All students.\n");
    printf("\t\t7. Add A New course.\n");
    printf("\t\t8. Show All courses.\n");
    printf("\t\t9. Search A course.\n");
    printf("\t\t10. Edit A course.\n");
    printf("\t\t11. Delete A course.\n");
    printf("\t\t12. Delete All courses.\n");
    printf("\t\t13. Clear The window.\n");
    printf("\t\t14. User Guideline.\n");
    printf("\t\t15. About Us.\n");
    printf("\t\t0. Exit the Program.\n");
    printf("\t\t=======================\n");
    printf("\t\tEnter The Choice: ");
} // end menu

// Function to add a new course
void AddNewCourse() {
    if (numCourses < MAX_COURSES) {
        printf("Enter course code: ");
        scanf("%s", courses[numCourses].courseCode);
        printf("Enter course name: ");
        scanf("%s", courses[numCourses].courseName);
        printf("Enter credits: ");
        scanf("%d", &courses[numCourses].credits);

        numCourses++;

        printf("Course added successfully!\n");
    } else {
        printf("Maximum number of courses reached!\n");
    }
}

// Function to display all courses
void ShowAllCourses() {
    if (numCourses > 0) {
        printf("Courses:\n");
        for (int i = 0; i < numCourses; i++) {
            printf("Course Code: %s\n", courses[i].courseCode);
            printf("Course Name: %s\n", courses[i].courseName);
            printf("Credits: %d\n", courses[i].credits);
            printf("\n");
        }
    } else {
        printf("No courses available.\n");
    }
}

// Function to search for a course by course code
int SearchCourse(char courseCode[10]) {
    for (int i = 0; i < numCourses; i++) {
        if (strcmp(courses[i].courseCode, courseCode) == 0) {
            return i;  // Return the index if the course is found
        }
    }
    return -1;  // Return -1 if the course is not found
}

// Function to edit a course
void EditCourse(int courseIndex) {
    printf("Enter new course name: ");
    scanf("%s", courses[courseIndex].courseName);
    printf("Enter new credits: ");
    scanf("%d", &courses[courseIndex].credits);

    printf("Course edited successfully!\n");
}

// Function to delete a course
void DeleteCourse(int courseIndex) {
    // Shift elements to remove the course
    for (int i = courseIndex; i < numCourses - 1; i++) {
        courses[i] = courses[i + 1];
    }

    numCourses--;

    printf("Course deleted successfully!\n");
}

// Function to delete all courses
void DeleteAllCourses() {
    numCourses = 0;
    printf("All courses deleted successfully!\n");
}

void AddNewStudent()
{
    char StudentID[300];
    char Name[300];
    char Phone[300];
    char Email[300];
    int NumberOfCourses;
    char CourseCode[300];
    char CourseName[300];

    int IsValidID = 0;
    while(!IsValidID)
    {
        printf("1. CS001=Advanced Java\n");
        printf("2. CS002=Advanced Python\n");
        printf("3. CS003=Intro to React\n");
        printf("4. AI001=Scope of AI\n");
        printf("5. AI002=Machine Learning\n");
        printf("6. AI003=Robotics\n");
        printf("7. DS001=Data Mining\n");
        printf("8. DS002=Data Visualization\n");
        printf("9. DS003=Business Understanding\n");
        printf("10. EH001=Phising Attack\n");
        printf("11. EH002=Wifi Hacking\n");
        printf("12. EH003=Viruses and Security\n");
        printf(" ID: ");
        scanf("%s",&StudentID);
        if(IsAlreadyExists(StudentID,'i',StudentID) > 0)
        {
            printf(" Error: This ID is already exists.\n\n");
            IsValidID = 0;
        }
        else if(strlen(StudentID) > 10)
        {
            printf(" Error: ID cannot be more than 10 characters.\n\n");
            IsValidID = 0;
        }
        else if(strlen(StudentID) <= 0)
        {
            printf(" Error: ID cannot be empty.\n\n");
            IsValidID = 0;
        }
        else
        {
            IsValidID = 1;
        }
    }

    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" Name: ");
        scanf(" %[^\n]s",&Name);
        if(strlen(Name) > 20)
        {
            printf(" Error: Name cannot be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        if(strlen(Name) <= 0)
        {
            printf(" Error: Name cannot be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" Email: ");
        scanf("%s",&Email);
        if(IsAlreadyExists(Email,'e',StudentID) > 0)
        {
            printf(" This Email already exists.\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) > 30)
        {
            printf(" Error: Email cannot be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else if(strlen(Email) <= 0)
        {
            printf(" Error: Email cannot be empty.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" Phone Number: ");
        scanf("%s",&Phone);
        if(IsAlreadyExists(Phone,'p',StudentID) > 0)
        {
            printf(" This Phone Number is Already Exists\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) != 10)
        {
            printf(" Error: Phone should contain 10 characters.\n\n");
            IsValidPhone = 0;
        }
        else if(strlen(Phone) <= 0)
        {
            printf(" Error: Phone cannot be empty.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }

    int IsValidNumberOfCourse = 0;
    while(!IsValidNumberOfCourse)
    {
        printf(" Number of courses: ");
        scanf("%d",&NumberOfCourses);
        if(NumberOfCourses <= 0 || NumberOfCourses > 4)
        {
            printf(" Error: Number of courses cannot be more than 4 and less than 1.\n\n");
            IsValidNumberOfCourse = 0;
        }
        else
        {
            IsValidNumberOfCourse = 1;
        }
    }

    strcpy(Students[TotalStudents].ID,StudentID);
    strcpy(Students[TotalStudents].Name,Name);
    strcpy(Students[TotalStudents].Phone,Phone);
    strcpy(Students[TotalStudents].Email,Email);
    Students[TotalStudents].NumberOfCourse = NumberOfCourses;
    TotalStudents++;

    for(i=0; i<NumberOfCourses; i++)
    {

        printf(" Enter Course %d Code: ",i+1);
        scanf("%s",&CourseCode);

        printf(" Enter Course %d Name: ",i+1);
        scanf(" %[^\n]s",&CourseName);

        strcpy(Courses[TotalCourse].StudentID,StudentID);
        strcpy(Courses[TotalCourse].Code,CourseCode);
        strcpy(Courses[TotalCourse].Name,CourseName);
        TotalCourse++;
    }

    printf("\n Student Added Successfully.\n\n");
}

void ShowAllStudents()
{
    printf("|==========|====================|==============================|====================|=============|\n");
    printf("|    ID    |        Name        |            Email             |       Phone        |  NO.Course  |\n");
    printf("|==========|====================|==============================|====================|=============|\n");

    for(i=0; i<TotalStudents; i++)
    {
        printf("|");
        printf("%s",Students[i].ID);
        for(j=0; j < (10-strlen(Students[i].ID)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Name);
        for(j=0; j < (20-strlen(Students[i].Name)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Email);
        for(j=0; j < (30-strlen(Students[i].Email)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%s",Students[i].Phone);
        for(j=0; j < (20-strlen(Students[i].Phone)); j++)
        {
            printf(" ");
        }
        printf("|");
        printf("%d",Students[i].NumberOfCourse);
        for(j=0; j < 12; j++)
        {
            printf(" ");
        }
        printf("|\n");
        printf("|----------|--------------------|------------------------------|--------------------|-------------|\n");

    }
    printf("\n");
}

int SearchStudent(char StudentID[10])
{
    system("cls");
    int StudentFoundIndex = -1;

    int i;
    for(i=0; i<TotalStudents; i++)
    {
        if(strcmp(StudentID,Students[i].ID) == 0)
        {
            StudentFoundIndex = i;
            printf("\n One Student Found for ID: %s\n\n",StudentID);
            printf(" Student Informations\n");
            printf("-------------------------\n");

            printf(" ID:    %s\n",Students[i].ID);
            printf(" Name:  %s\n",Students[i].Name);
            printf(" Email: %s\n",Students[i].Email);
            printf(" Phone: %s\n",Students[i].Phone);
            printf("\n Total Number of Courses: %d\n",Students[i].NumberOfCourse);
        }
    }
    int CourseCount = 0;
    int j;
    for(j=0; j<TotalCourse; j++)
    {
        if(strcmp(StudentID,Courses[j].StudentID) == 0)
        {
            CourseCount++;
            printf(" Course %d Code: %s\n",CourseCount,Courses[j].Code);
            printf(" Course %d Name: %s\n",CourseCount,Courses[j].Name);
        }
    }

    return StudentFoundIndex;
}

void EditStudent(int StudentFoundIndex)
{
    printf("\n\t\t **** \\\\Update The New Student// ****\n\n");

    char NewName[300];
    char NewPhone[300];
    char NewEmail[300];
    int NewNumberOfCourses;
    char StudentID[300];
    strcpy(StudentID, Students[StudentFoundIndex].ID);
    int OldTotalNumberOfCourse = Students[StudentFoundIndex].NumberOfCourse;

    int IsValidName = 0;
    while(!IsValidName)
    {
        printf(" New Name(0 for skip): ");
        scanf(" %s",&NewName);
        if(strlen(NewName) > 20)
        {
            printf(" Error: Name cannot be more than 20 characters.\n\n");
            IsValidName = 0;
        }
        else if(strlen(NewName) <= 0)
        {
            printf(" Error: Name cannot be empty.\n\n");
            IsValidName = 0;
        }
        else
        {
            IsValidName = 1;
        }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail)
    {
        printf(" New Email(0 for skip): ");
        scanf("%s",&NewEmail);

        if(strlen(NewEmail) > 30)
        {
            printf(" Error: Email cannot be more than 30 characters.\n\n");
            IsValidEmail = 0;
        }
        else if(strlen(NewEmail) <= 0)
        {
            printf(" Error: Email cannot be empty.\n\n");
            IsValidEmail = 0;
        }
        else if(IsAlreadyExists(NewEmail,'e',StudentID) > 0)
        {
            printf(" Error: This Email Already Exists.\n\n");
            IsValidEmail = 0;
        }
        else
        {
            IsValidEmail = 1;
        }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone)
    {
        printf(" New Phone Number(0 for skip): ");
        scanf("%s",&NewPhone);

        if(strlen(NewPhone) != 10)
        {
            printf(" Error: Phone should be 10 characters.\n\n");
            IsValidPhone = 0;
        }
        else if(strlen(NewPhone) <= 0)
        {
            printf(" Error: Phone cannot be empty.\n\n");
            IsValidPhone = 0;
        }
        else if(IsAlreadyExists(NewPhone,'p',StudentID) > 0)
        {
            printf(" Error: This Phone Number Already Exists.\n\n");
            IsValidPhone = 0;
        }
        else
        {
            IsValidPhone = 1;
        }
    }

    int IsValidNumberOfCourse = 0;
    while(!IsValidNumberOfCourse)
    {
        printf(" Number of New courses(0 for skip): ");
        scanf("%d",&NewNumberOfCourses);

        if(NewNumberOfCourses > 4 || NewNumberOfCourses < 0)
        {
            printf(" Error: A Student can have maximum 4 and Minimum 0 number of courses.\n\n");
            IsValidNumberOfCourse = 0;
        }
        else
        {
            IsValidNumberOfCourse = 1;
        }
    }

    if(strcmp(NewName,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Name,NewName);
    }

    if(strcmp(NewEmail,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Email,NewEmail);
    }

    if(strcmp(NewPhone,"0") != 0)
    {
        strcpy(Students[StudentFoundIndex].Phone,NewPhone);
    }

    if(NewNumberOfCourses != 0)
    {
        int OldTotalCourse = Students[StudentFoundIndex].NumberOfCourse;
        Students[StudentFoundIndex].NumberOfCourse = NewNumberOfCourses;


        int FirstCourseIndex;
        int dc;
        for(dc=0; dc<TotalCourse; dc++)
        {
            if(strcmp(StudentID,Courses[dc].StudentID) == 0)
            {
                FirstCourseIndex = dc; // store the index for delete
                break;
            }
        }
        // after every delete array index will update (decrease by one)
        // we store the courses sequential
        // so if we know the first course index and total number of course we can delete all
        for(dc=1; dc<=OldTotalCourse; dc++)
        {
            DeleteCourseByIndex(FirstCourseIndex);
        }

        char CourseCode[300];
        char CourseName[300];
        for(i=1; i<=NewNumberOfCourses; i++)
        {
            printf(" New Course %d Code: ",i);
            scanf("%s",&CourseCode);

            printf(" New Course %d Name: ",i);
            scanf(" %[^\n]s",&CourseName);

            strcpy(Courses[TotalCourse].StudentID,StudentID);
            strcpy(Courses[TotalCourse].Code,CourseCode);
            strcpy(Courses[TotalCourse].Name,CourseName);
            TotalCourse++;
        }
    }

    printf(" Student Updated Successfully.\n\n");

}

void DeleteStudent(int StudentIndex)
{
    int d;
    int FirstCourseIndexs;
    struct StudentInfo ThisStudents;
    ThisStudents = Students[StudentIndex];
    for(d=0; d<TotalCourse; d++)
    {
        if(strcmp(ThisStudents.ID,Courses[d].StudentID) == 0)
        {
            FirstCourseIndexs = d;
            break;
        }
    }
    for(d=1; d<=ThisStudents.NumberOfCourse; d++)
    {
        DeleteCourseByIndex(FirstCourseIndexs);
    }
    DeleteStudentByIndex(StudentIndex);
    printf(" Student Deleted Successfully.\n\n");
    GoBackOrExit();
}

void DeleteAllStudents()
{
    TotalStudents = 0;
    TotalCourse = 0;
    printf(" All Students Deleted Successfully.\n\n");
    GoBackOrExit();
}


void DeleteCourseByIndex(int CourseIndex)
{
    int c;
    for(c=0; c<TotalCourse-1; c++)
    {
        if(c>=CourseIndex)
        {
            Courses[c] = Courses[c+1];
        }
    }
    TotalCourse--;

}

void DeleteStudentByIndex(int CourseIndex)
{
    int s;
    for(s=0; s<TotalStudents-1; s++)
    {
        if(s>=CourseIndex)
        {
            Students[s] = Students[s+1];
        }
    }
    TotalStudents--;
}


int IsAlreadyExists(char GivenLine[300],char InfoType, char StudentID[300])
{
    int EmailExists = 0;
    int PhoneExists = 0;
    int IDExists = 0;
    int ep;

    for(ep=0; ep<TotalStudents; ep++)
    {
        if(strcmp(GivenLine,Students[ep].ID) == 0)
        {
            IDExists++;
        }
        if(strcmp(GivenLine,Students[ep].Email) == 0 && strcmp(StudentID,Students[ep].ID) != 0 )
        {
            EmailExists++;
        }
        if(strcmp(GivenLine,Students[ep].Phone) == 0 && strcmp(StudentID,Students[ep].ID) != 0)
        {
            PhoneExists++;
        }

    }

    if(InfoType == 'i')
    {
        return IDExists;
    }
    else if(InfoType == 'e')
    {
        return EmailExists;
    }
    else if(InfoType == 'p')
    {
        return PhoneExists;
    }
    else
    {
        return 0;
    }
}

void ErrorAndRestart(char *error[100])
{
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}

void UserGuideline()
{
    printf("\n\t\t **** \\\\How it Works?// ****\n\n");
    printf(" -> You will only able to store the Student's ID, Name, Email, Phone, Number of Courses.\n");
    printf(" -> A student can have maximum 4 courses and minimum 1 course.\n");
    printf(" -> Student ID can be maximum 10 characters long and unique for every students.\n");
    printf(" -> Student Name can be maximum 20 characters long.\n");
    printf(" -> Student Email can be maximum 30 characters long and unique for every students.\n");
    printf(" -> Student Phone number should be 10 characters long and unique for every students.\n");
    printf(" -> Course code can be maximum 10 characters long.\n");
    printf(" -> Course Name can be maximum 20 characters long.\n\n");

}

void AboutUs()
{
    printf("\n\t\t **** \\\\About US?// ****\n\n");

    printf(" Some important note we should remember.\n");
    printf(" -> This is a simple student management system project.\n");
    printf(" -> You can modify the source code.\n");
    printf(" -> You can use this project only for personal purpose not for business.\n\n");

    printf(" ->> visit www.insideTheDiv.com for more project like this. <<-\n\n");
}

void GoBackOrExit()
{
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        ExitProject();
    }
    else
    {
        system("cls");
    }
}

void ExitProject()
{
    system("cls");
    int i;
    char ThankYou[100]     = " ========= Thank You =========\n";
    char SeeYouSoon[100]   = " ========= See You Soon ======\n";
    for(i=0; i<strlen(ThankYou); i++)
    {
        printf("%c",ThankYou[i]);
        Sleep(40);
    }
    for(i=0; i<strlen(SeeYouSoon); i++)
    {
        printf("%c",SeeYouSoon[i]);
        Sleep(40);
    }
    exit(0);
}

void DataSeed()
{

    //-- store some dummy data
    //-- student 1
    strcpy(Students[0].ID,"01");
    strcpy(Students[0].Name,"Student 1");
    strcpy(Students[0].Phone,"0161111111");
    strcpy(Students[0].Email,"std1@gmail.com");
    Students[0].NumberOfCourse=1;

    strcpy(Courses[0].StudentID,"01");
    strcpy(Courses[0].Code,"CS001");
    strcpy(Courses[0].Name,"Advanced Java");

    //-- student 2
    strcpy(Students[1].ID,"02");
    strcpy(Students[1].Name,"Student 2");
    strcpy(Students[1].Phone,"0161111112");
    strcpy(Students[1].Email,"std2@gmail.com");
    Students[1].NumberOfCourse=2;

    strcpy(Courses[1].StudentID,"02");
    strcpy(Courses[1].Code,"EH001");
    strcpy(Courses[1].Name,"Phising Attack");

    strcpy(Courses[2].StudentID,"02");
    strcpy(Courses[2].Code,"AI002");
    strcpy(Courses[2].Name,"Machine Learning");


    //-- student 3
    strcpy(Students[2].ID,"03");
    strcpy(Students[2].Name,"Student 3");
    strcpy(Students[2].Phone,"0161111113");
    strcpy(Students[2].Email,"std3@gmail.com");
    Students[2].NumberOfCourse=3;

    strcpy(Courses[3].StudentID,"03");
    strcpy(Courses[3].Code,"AI003");
    strcpy(Courses[3].Name,"Robotics");

    strcpy(Courses[4].StudentID,"03");
    strcpy(Courses[4].Code,"AI001");
    strcpy(Courses[4].Name,"Scope of AI");

    strcpy(Courses[5].StudentID,"03");
    strcpy(Courses[5].Code,"DS001");
    strcpy(Courses[5].Name,"Data Mining");

    TotalStudents = 3;
    TotalCourse = 6;
}
