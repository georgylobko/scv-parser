#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User {
    char *name;
    int year;
    char *jobTitle;
    char *gender;
};

int ascendingCompare(struct User a, struct User b) {
    return strcmp(a.name, b.name) > 0 ? 1 : -1;
}

void sort(struct User array[5], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - 1; j++) {
            if (ascendingCompare(array[j], array[j + 1]) > 0) {
                struct User temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

struct User* extractUserDataFromString(char *string) {
    int i = 0;
    char *p = strtok(string, ",");
    char *array[4];

    while (p != NULL) {
        array[i++] = p;
        p = strtok(NULL, ",");
    }

    struct User* user = (struct User*)malloc(sizeof(struct User));

    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                user->name = array[i];
                break;
            case 1:
                user->year = atoi(array[i]);
                break;
            case 2:
                user->jobTitle = array[i];
                break;
            case 3:
                user->gender = array[i];
                break;
            default:
                printf("default case");
                break;
        }
    }

    return user;
}

void writeStringToFile(FILE *fp, struct User* user) {
    char *name = user->name;
    int *year = &user->year;
    char *jobTitle = user->jobTitle;
    char *gender = user->gender;
    char template[] = "name: %s, year of birth: %d, job title: %s, gender: %s \n";

    printf(template, name, year, jobTitle, gender);
    fprintf(fp, template, name, year, jobTitle, gender);
}

int getNumberOfUsers(char *string) {
    const char delimiter = ';';
    int length = strlen(string);
    int numberOfElements = 0;

    for (int i = 0; i < length; i++) {
        if (string[i] == delimiter) {
            numberOfElements++;
        }
    }

    return numberOfElements;
}

void parseString(char *string) {
    int numberOfElements = getNumberOfUsers(string);

    int i = 0;
    char *p = strtok(string, ";");
    char *arrayOfUserStrings[numberOfElements];
    struct User* arrayOfUserStructs = malloc(numberOfElements * sizeof *arrayOfUserStructs);

    while (p != NULL) {
        arrayOfUserStrings[i++] = p;
        p = strtok(NULL, ";");
    }

    FILE *fp;
    fp = fopen("/Users/temp/CLionProjects/hw_1105/output.txt", "r+");
    rewind(fp);

    for (int j = 0; j < numberOfElements; ++j) {
        struct User* user = extractUserDataFromString(arrayOfUserStrings[j]);

        arrayOfUserStructs[j].name = user->name;
        arrayOfUserStructs[j].year = user->year;
        arrayOfUserStructs[j].jobTitle = user->jobTitle;
        arrayOfUserStructs[j].gender = user->gender;
    }

    sort(arrayOfUserStructs, numberOfElements);

    for (int j = 0; j < numberOfElements; ++j) {
        writeStringToFile(fp, &arrayOfUserStructs[j]);
    }

    free(arrayOfUserStructs);

    fclose(fp);
}

int main() {
    FILE *fp;
    char buff[255];

    fp = fopen("/Users/temp/CLionProjects/hw_1105/input.txt", "r");

    fgets(buff, sizeof(buff), fp);

    parseString(buff);

    return 0;
}
