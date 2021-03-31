// ---- Includes ----
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "Constants.h"
#include "LinkedList.h"

// ---- Functions ----
void help(void);
int add(struct linkedList * LinkedList);
int del(struct linkedList * LinkedList);
int mod(struct linkedList * LinkedList);
int gen(struct linkedList * LinkedList);
void clearScreen(void);
int sort(struct linkedList * LinkedList);
int write(struct linkedList * LinkedList);
int read(struct linkedList * LinkedList);
int encryption(void);
int decryption(void);
int getPassword(char * password);
int changePwd();

int main(void)
{
    struct linkedList * LinkedList = newLinkedList();

    int error;
    char command[MAX_CMD_CHAR];
    char password[PASSWORDLEN] = {0};
    char input[PASSWORDLEN];
    char loop = 1;

    if (getPassword(password)) {return EXIT_FAILURE;}
    while (strcoll(password, input) != 0)
    {
        clearScreen();
        printf("Enter password : ");
        scanf("%"CH_PASSWORDLEN"s", input);
    }

    decryption();
    read(LinkedList);

    clearScreen();
    
    while (loop == 1)
    {
        displayLinkedList(LinkedList);

        printf("\n> ");

        scanf("%"CH_MAX_CMD_CHAR"s", command);

        if (strcoll(command, "/exit") == 0 || strcoll(command, "/save") == 0)
        {
            error = write(LinkedList);
            encryption();
            if (error == 0) {printf("Saved !");}
            loop = 0;
        }
        else if (strcoll(command, "/help") == 0)
        {
            clearScreen();
            help();
            while ((getchar()) != '\n');
        }
        else if (strcoll(command, "/add") == 0)
        {
            add(LinkedList);
            sort(LinkedList);
            while ((getchar()) != '\n');
            clearScreen();
        }
        else if (strcoll(command, "/rm") == 0)
        {
            del(LinkedList);
            while ((getchar()) != '\n');
            clearScreen();
        }
        else if (strcoll(command, "/mod") == 0)
        {
            mod(LinkedList);
            while ((getchar()) != '\n');
            clearScreen();
        }
        else if (strcoll(command, "/gen") == 0)
        {
            gen(LinkedList);
            while ((getchar()) != '\n');
            clearScreen();
        }
        else if (strcoll(command, "/chpwd") == 0)
        {
            error = changePwd();
            while ((getchar()) != '\n');
            clearScreen();
            if (error == 0){printf("Password changed !");}
        }
        else
        {
            clearScreen();
            printf("Command not found");
        }
    }

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-01-28 22:21:08
//  # Description: Display a help section
// **************************************************
void help(void)
{
    printf("\n"
        "******************************************************************************\n"
        " # /add name id pwd                         ==> add an element to the list\n"
        " # /rm line                                 ==> remove an element of the list\n"
        " # /mod line (name, id or pwd) newChange    ==> modify an element of the list\n"
        " # /gen line                                ==> generate a random password\n"
        " # /save or /exit                           ==> save changes and exit\n"
        " # /chpwd newPassword                       ==> change the security password\n"
        "******************************************************************************\n");
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-24 21:10:11
//  # Description: Add a new element to the list
// **************************************************
int add(struct linkedList * LinkedList)
{
    char name[MAX_NAME_CHAR];
    char id[MAX_ID_CHAR];
    char pwd[MAX_PWD_CHAR];

    scanf("%"CH_MAX_NAME_CHAR"s %"CH_MAX_ID_CHAR"s %"CH_MAX_PWD_CHAR"s", name, id, pwd);

    for (int i = 0; i < MAX_NAME_CHAR; i++)
    {
        if (name[i] == BANNEDCHAR1) {printf(ERROR5); return EXIT_FAILURE;}
    }
    for (int i = 0; i < MAX_ID_CHAR; i++)
    {
        if (id[i] == BANNEDCHAR1) {printf(ERROR5); return EXIT_FAILURE;}
    }
    for (int i = 0; i < MAX_PWD_CHAR; i++)
    {
        if (pwd[i] == BANNEDCHAR1) {printf(ERROR5); return EXIT_FAILURE;}
    }

    struct link * tmp = newLink(name, id, pwd);

    addLink(LinkedList, tmp);

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-25 11:50:35
//  # Description: remove an element to the list
// **************************************************
int del(struct linkedList * LinkedList)
{
    int number;

    scanf("%d", &number);

    if (number <= 0 || number > LinkedList->size){printf(ERROR2); return EXIT_FAILURE;}

    struct link * tmp = LinkedList->head;

    for (int i = 1; i < number; i++)
    {
        tmp = tmp->nextLink;
    }

    rmlink(LinkedList, tmp);

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-25 12:12:06
//  # Description: modify an element of the list
// **************************************************
int mod(struct linkedList * LinkedList)
{
    int number;
    scanf("%d", &number);
    if (LinkedList == NULL || number <= 0 || number > LinkedList->size || LinkedList->head == NULL){printf(ERROR2); return EXIT_FAILURE;}

    char parameter[8];
    scanf("%8s", parameter);

    struct link * tmp = LinkedList->head;
    for (int i = 1; i < number; i++)
    {
        tmp = tmp->nextLink;
    }

    if (strcoll(parameter, "name") == 0)
    {
        char change[MAX_NAME_CHAR];
        scanf("%"CH_MAX_NAME_CHAR"s", change);
        strcpy(tmp->name, change);
    }
    else if (strcoll(parameter, "id") == 0)
    {
        char change[MAX_ID_CHAR];
        scanf("%"CH_MAX_ID_CHAR"s", change);
        strcpy(tmp->id, change);
    }
    else if (strcoll(parameter, "pwd") == 0)
    {
        char change[MAX_PWD_CHAR];
        scanf("%"CH_MAX_PWD_CHAR"s", change);
        strcpy(tmp->pwd, change);
    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-25 12:34:50
//  # Description: Generation of a random password
// **************************************************
int gen(struct linkedList * LinkedList)
{
    int number;
    scanf("%d", &number);
    if (LinkedList == NULL || number <= 0 || number > LinkedList->size || LinkedList->head == NULL){printf(ERROR2); return EXIT_FAILURE;}

    struct link * tmp = LinkedList->head;
    for (int i = 1; i < number; i++)
    {
        tmp = tmp->nextLink;
    }

    char str[] = {
    '?','!','.',':',';',',','-','_','=','+','%','@',
    'A','Z','E','R','T','Y','U','I','O','P','Q','S','D','F','G','H','J','K','L','M','W','X','C','V','B','N',
    '0','1','2','3','4','5','6','7','8','9',
    'a','z','e','r','t','y','u','i','o','p','q','s','d','f','g','h','j','k','l','m','w','x','c','v','b','n',
    '?','!','.',':',';',',','-','_','=','+','%','@'
    };

    char password[PWDLENGTH];

    srand(time(0));
    for (int i = 0; i < PWDLENGTH-1; i++)
    {
        password[i] = str[rand()%sizeof(str)];
    }
    password[PWDLENGTH-1] = '\0';

    strcpy(tmp->pwd, password);

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-25 13:55:58
//  # Description: Function to clear the screen
// **************************************************
void clearScreen(void)
{
    #ifdef LINUX
        system("clear");
    #endif

    #ifdef WINDOWS
        system("cls");
    #endif
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-25 14:08:50
//  # Description: Sorting function for names
// **************************************************
int sort(struct linkedList * LinkedList)
{
    if (LinkedList == NULL || LinkedList->head == NULL){printf(ERROR2); return EXIT_FAILURE;}

    struct link * previous = NULL;
    struct link * tmp = LinkedList->head;

    while (tmp->nextLink != NULL)
    {
        previous = tmp;
        tmp = tmp->nextLink;

        for (int i = 0; i < MAX_NAME_CHAR; i++)
        {
            if (toupper(tmp->name[i]) > toupper(previous->name[i]))
            {
                break;
            }
            if (toupper(tmp->name[i]) < toupper(previous->name[i]))
            {
                switchLink(LinkedList, previous, tmp);
                previous = NULL;
                tmp = LinkedList->head;
                i = 0;
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-02-27 15:20:05
//  # Description: Write the list in an uncrypted file
// **************************************************
int write(struct linkedList * LinkedList)
{
    if (LinkedList == NULL || LinkedList->size <= 0 || LinkedList->head == NULL || LinkedList->tail == NULL){printf(ERROR4); return EXIT_FAILURE;}

    FILE * file = fopen(FILENAME, "wb");
    if (file == NULL){printf(ERROR3); return EXIT_FAILURE;}

    struct link * tmp = LinkedList->head;

    while (tmp != NULL)
    {
        fprintf(file, "%s|%s|%s\n", tmp->name, tmp->id, tmp->pwd);
        tmp = tmp->nextLink;
    }

    fclose(file);

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-03-01 11:47:39
//  # Description: Read an uncrypted file
// **************************************************
int read(struct linkedList * LinkedList)
{
    if (LinkedList == NULL || LinkedList->size < 0){printf(ERROR4); return EXIT_FAILURE;}

    FILE * file = fopen(FILENAME, "rb");
    if (file == NULL){printf(ERROR3); return EXIT_FAILURE;}

    char name[MAX_NAME_CHAR] = {0};
    char id[MAX_ID_CHAR] = {0};
    char pwd[MAX_PWD_CHAR] = {0};

    int index = 0;
    int cut = 0;

    char ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '|')
        {
            index = 0;
            cut++;
        }
        else
        {
            if (ch == '\n')
            {
                index = 0;
                cut = 0;
                addLink(LinkedList, newLink(name, id, pwd));

                for (int i = 0; i < MAX_NAME_CHAR; i++)
                {
                    name[i] = 0;
                }
                for (int i = 0; i < MAX_ID_CHAR; i++)
                {
                    id[i] = 0;
                }
                for (int i = 0; i < MAX_PWD_CHAR; i++)
                {
                    pwd[i] = 0;
                }
            }
            else
            {
                if (cut == 0)
                {
                    name[index++] = ch;
                }
                else if (cut == 1)
                {
                    id[index++] = ch;
                }
                else
                {
                    pwd[index++] = ch;
                }
            }
        }
    }

    fclose(file);

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-03-01 11:59:21
//  # Description: Encrypt a file
// **************************************************
int encryption(void)
{
    FILE * file = fopen(FILENAME, "r");
    FILE * encryptFile = fopen(ENCRYPTFILENAME, "w");
    if (file == NULL || encryptFile == NULL){printf(ERROR3); return EXIT_FAILURE;}

    int byte;
    char ch;

    while ((ch = fgetc(file)) != EOF)
    {
        byte = (int) ch;
        byte = (byte^521)-11;
        fprintf(encryptFile, "%c", byte);
    }

    fclose(file);
    fclose(encryptFile);

    #ifdef LINUX
        system("rm "FILENAME);
    #endif

    #ifdef WINDOWS
        system("del "FILENAME);
    #endif

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-03-01 12:20:58
//  # Description: Decrypt a file
// **************************************************
int decryption(void)
{
    FILE * encryptFile = fopen(ENCRYPTFILENAME, "r");
    FILE * file = fopen(FILENAME, "w");
    if (file == NULL || encryptFile == NULL){printf(ERROR3); return EXIT_FAILURE;}

    int byte;
    char ch;

    while ((ch = fgetc(encryptFile)) != EOF)
    {
        byte = (int) ch;
        byte = (byte+11)^521;
        fprintf(file, "%c", byte);
    }

    fclose(file);
    fclose(encryptFile);

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-03-29 18:34:40
//  # Description: Function to get the password for the file
// **************************************************
int getPassword(char * password)
{
    FILE * pwdFile = fopen(PWDFILE, "rb");
    if (pwdFile == NULL) {printf(ERROR3); return EXIT_FAILURE;}

    int byte;
    char ch;
    int index = 0;
    while ((byte = fgetc(pwdFile)) != EOF)
    {
        byte = (byte+11)^521;
        ch = (char) byte;
        *(password + index++) = ch;
    }

    fclose(pwdFile);

    return EXIT_SUCCESS;
}

// **************************************************
//  # Author: Bonnel Maxime
//  # Modified time: 2021-03-29 19:15:02
//  # Description: Function to change connexion password
// **************************************************
int changePwd()
{
    char pwd[PASSWORDLEN];
    int index = 0;
    int byte;
    char ch;

    scanf("%"CH_PASSWORDLEN"s", pwd);

    FILE * pwdFile = fopen(PWDFILE, "wb");
    if (pwdFile == NULL) {printf(ERROR3); return EXIT_FAILURE;}

    while (index < PASSWORDLEN && pwd[index] != '\0')
    {
        ch = pwd[index++];
        byte = (int) ch;
        byte = (byte^521)-11;
        fprintf(pwdFile, "%c", byte);
    }

    fclose(pwdFile);

    return EXIT_SUCCESS;
}
