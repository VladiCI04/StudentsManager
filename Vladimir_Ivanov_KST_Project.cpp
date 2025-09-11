#include <iostream>

const unsigned short CONSTANT1 = 11;
const unsigned short CONSTANT2 = 30;
const unsigned short CONSTANT3 = 10;

FILE* file = nullptr;   

struct Student {
    char name[CONSTANT2];
    char EGN[CONSTANT1];
    char fNum[CONSTANT1];
    float grades[CONSTANT1];
    float avGrade = 0;
};

bool readStudentsData(unsigned short studentsCount, Student* allStudents) {
    Student curStudent;
    for (unsigned short i = 0; i < studentsCount; i++) {
        printf("Student %d \n", i + 1);

        printf("Write Student Name (First and Last Name): ");
        getchar();
        gets_s(curStudent.name, CONSTANT2);

        printf("Write Student EGN: ");
        gets_s(curStudent.EGN, CONSTANT1);
        if (strlen(curStudent.EGN) < CONSTANT3) {
            return false;
        }
        

        printf("Write Student Faculty Number: ");
        scanf_s("%s", curStudent.fNum, CONSTANT1);

        float gradesSum = 0;
        for (unsigned short i = 0; i < CONSTANT3; i++) {
            printf("   %d. Grade (2-6): ", i + 1);
            scanf_s("%f", &curStudent.grades[i]);
            if (curStudent.grades[i] > 6 || curStudent.grades[i] < 2) {
                return false;
            }
            gradesSum += curStudent.grades[i];
        }
        printf("\n");

        curStudent.avGrade = gradesSum / 10;
        allStudents[i] = curStudent;
    }

    printf("\n\n");
    return true;
}

void createStudentsFile(unsigned short studentsCount, Student* allStudents) {
    errno_t err = fopen_s(&file, "students.txt", "w+t"); 
    if (err != 0) {
        printf("Error opening file!\n");
        return;
    }

    for (unsigned short i = 0; i < studentsCount; i++) {
        printf("Name: %s\n", allStudents[i].name);
        fprintf(file, "Name: %s\n", allStudents[i].name);

        printf("EGN: %s\n", allStudents[i].EGN);
        fprintf(file, "EGN: %s\n", allStudents[i].EGN);

        printf("Faculty Number: %s\n", allStudents[i].fNum);
        fprintf(file, "Faculty Number: %s\n", allStudents[i].fNum);

        for (unsigned short j = 0; j < CONSTANT3; j++) {
            printf("    %d. %.2f\n", j+1, allStudents[i].grades[j]);
            fprintf(file, "    %d. %.2f\n", j + 1, allStudents[i].grades[j]);
        }

        printf("\n");
        fprintf(file, "\n");
    }

    fclose(file);
}

void studentsAverageGrades(unsigned short studentsCount, Student* allStudents) {
    for (unsigned short i = 0; i < studentsCount; i++) {
        printf("Name: %s - ", allStudents[i].name);
        printf("Faculty Number: %s - ", allStudents[i].fNum);
        printf("Average Grade: %.2f\n", allStudents[i].avGrade);
        printf("\n");
    }
}

void allStudentsWithMoreThanTwoFailGrades(unsigned short studentsCount, Student* allStudents) {
    unsigned short failGradeSum = 0;
    for (unsigned short i = 0; i < studentsCount; i++) {
        for (unsigned short j = 0; j < CONSTANT3; j++) {
            if (allStudents[i].grades[j] == 2) {
                failGradeSum++;
            }
        }

        if (failGradeSum <= 2) {
            printf("Faculty Number: %s\n", allStudents[i].fNum);
            printf("\n");
        }

        failGradeSum = 0;
    }
}

bool menu(unsigned short studentsCount, Student* allStudents) {
    unsigned short option = 0;
    while (true) {
        printf("---Menu---\n");
        printf("1. Create file with information about students\n");
        printf("2. Average grade of every student\n");
        printf("3. All students with not more than 2 Fail grades\n");
        printf("4. Quit\n");
        printf("Choose (1-4): ");
        scanf_s("%hd", &option);
        printf("\n");

        switch (option) {
        case 1:
            createStudentsFile(studentsCount, allStudents);
            break;
        case 2:
            studentsAverageGrades(studentsCount, allStudents);
            break;
        case 3:
            allStudentsWithMoreThanTwoFailGrades(studentsCount, allStudents);
            break;
        case 4:
            printf("Bye! Bye!\n");
            exit(0);
        default:
            return false;
        }
        option = 0;
    }
}

int main()
{
    unsigned short studentsCount = 0;

    printf("----------StudentsManagerSystem----------\n");
    printf("Write Students Count (1-200): ");
    scanf_s("%hd", &studentsCount);
    if (studentsCount == 0) {
        printf("Incorrect data! Try again!");
        return 0;
    }
    printf("\n");
   
    Student* allStudents = new Student[studentsCount];
    if (!readStudentsData(studentsCount, allStudents) || !menu(studentsCount, allStudents)) {
        printf("Incorrect data! Try again!");
        return 0;
    }
    
    delete[] allStudents;
}